# Diagnóstico: entrar no servidor (2026-08-10 ~16h, EM ANÁLISE — ver "ÚLTIMOS ACHADOS")

**STATUS: O SERVIDOR (loginserver+gameserver reais) FUNCIONA 100% via script
com seq correta. O CLIENTE REAL (fengshen.bin fev/2014) NÃO conecta no
gameserver após receber o LCReconnect — com o servidor real E com fakes.
Causa ainda não determinada (em análise).**

Situação: login OK (test123/test456) e personagem criado (TroniPM, Slayer).
Ao selecionar o personagem e clicar em conectar, o cliente mostra mensagem de
erro (coreana) e volta à tela inicial, SEM nunca conectar no gameserver TCP.

## ÚLTIMOS ACHADOS (2026-08-10 ~15h-16h)

### Testes com FAKE SERVER (servidor real parado; fake roda na VM)

- fake_server.py (porta 9999 fake LS + 19998 fake GS captura): responde o
  fluxo completo e o LCReconnect. O cliente real:
  - Completa todo o fluxo até CLSelectPC (154,145,144,153,152,151 — seq 0..5)
  - Recebe o LCReconnect (443) e mostra ERRO + volta ao menu
  - **NUNCA conecta no fake GS (19998)** — nem no gameserver real (9998)
  - Formato A (port antes da key): falhou. Formato B (key antes da port): falhou.
- A "demora de ~8s" nas telas do fake = timeouts longos do read_pkts do fake
  (4-6s por etapa), NÃO do cliente.

### Formato do LCReconnect CONFIRMADO no binário fev/2014 (desmontagem)

- read() do LCReconnect em 0x5101a3: lê `szIP(BYTE, checa 0 e >15)` + `IP
  (string, len=szIP)` + **port (4 bytes, this+0x14)** + **key (4 bytes,
  this+0x18)** — via SocketInputStream::read(void*,len) = 0x53277d.
- **O formato do servidor (A) ESTÁ CORRETO** — o parse não é o problema.
- O read() TEM o check do IP local: `if (m_GameServerIP == "127.0.0.1") →
  QUIT (g_bNeedUpdate=1, MODE_QUIT)` e loop gethostname/gethostbyname
  comparando com TODOS os IPs do PC → se igual → QUIT (0x510331).
  O operador== de string está em 0x444311 (padrão neg/sbb/inc).
- Handler LCReconnect ATIVO no binário: strings "Reconnecting to %s:%d"
  (0x6ed220, refs 0x4e801a e 0x510503) e "Sending CGConnect with Key(%ld)"
  (0x6ed1f8) presentes → o cliente TENTA reconectar.

### IPs do PC (host Windows) — informados pelo usuário (ipconfig)

- 192.168.56.1 (VirtualBox Host-Only), 192.168.50.14 (rede principal),
  172.19.240.1 (outro adaptador)
- **NENHUM 192.168.50.19** → o check do IP local NÃO deveria disparar para
  o IP da VM (.19)... e o teste com 8.8.8.8 (fake C) deu o MESMO erro →
  o check do IP local provavelmente NÃO é a causa.

### Binários do cliente em /media/sf_Client-exe/

- fengshen.original.bin = 3.207.168 B (09/08 20:48) — o analisado (família A)
- fengshen.1.bin = idêntico ao original (mesmo MD5 80debb04...)
- fengshen.2.bin = 3.203.072 B (MD5 46783512...) — DIFERENTE (variação)
- O usuário testou com um deles (provável o 1 = original). fengshen.2.bin
  AINDA NÃO FOI TESTADO — pode ser uma variação útil!

### Próximos passos planejados (PARA CONTINUAR DEPOIS DO OK)

1. Desmontar as funções do handler de reconnect no binário fev/2014:
   - 0x53277d (já visto = SocketInputStream::read(void*,len) — usado no parse)
   - 0x5328aa (read(string,len) — o IP)
   - O Socket::reconnect em si (procurar) e as chamadas no handler 0x4e7f00:
     0x6461c7, 0x476d4c, 0x5326ad, 0x53264d, 0x41489e, 0x52f20d (destrutor?)
   - Verificar para QUAL IP/porta o reconnect é chamado e se algo falha antes
     (ex.: o check do IP, o estado da socket, um membro NULL).
2. Testar o fengshen.2.bin (variação diferente) no fake server.
3. Testar o fs_Debug.exe (mar/2014, família B — ver qual packetID envia).
4. Considerar capturar o tráfego do PC (Wireshark no Windows) para ver se o
   cliente emite SYN para algum endereço ao clicar em conectar.

## FATOS VERIFICADOS (2026-08-09 ~22h-23h) — servidor funcional via script

## Arquitetura do fluxo (após CLSelectPC)

1. Cliente envia `CLSelectPC` (151, body: szPCName+Name+pcType) ao loginserver.
2. Loginserver (`CLSelectPCHandler.cpp`): consulta DB, faz UPDATEs
   (CurrentWorldID/CurrentServerGroupID/LastSlot), e envia `LGIncomingConnection`
   via **UDP** ao gameserver (IP=LocalHost do login player, porta=GameServerInfo.UDPPort=9997).
3. Gameserver (`LoginServerManager::run` loop UDP + `LGIncomingConnectionHandler`):
   cria `ConnectionInfo` (chave = ClientIP do pacote), envia `GLIncomingConnectionOK`
   (UDP) ao loginserver com PlayerID + TCPPort + authKey.
4. Loginserver (`GLIncomingConnectionOKHandler` LS): envia `LCReconnect` (443) ao
   cliente com ip=origem UDP do gameserver, port=TCPPort(9998), key; depois
   `disconnect_nolog` do login player.
5. Cliente conecta no gameserver TCP 9998 e envia `CGConnect` (key + pcType +
   pcName + MAC). Gameserver: `acceptNewConnection` → `getConnectionInfo(IP do
   cliente)` (senão → "ILLEGAL ACCESS" → fecha SEM responder) → `CGConnectHandler`
   (key/pcName/expire checks → consultas DB → carrega Slayer).

## ⚠️ DESCOBERTA CRÍTICA (2026-08-10 ~15h): VALIDAÇÃO DE SEQUÊNCIA NO GAMESERVER

- O gameserver VALIDA o byte de sequência do header em `GamePlayer::processCommand`
  (GamePlayer.cpp ~linha 420): `if (packetSequence != m_Sequence) throw
  DisconnectException("sequence error")` — `m_Sequence` começa em 0 e incrementa.
- O log de erro é ENGANAOSO: grava em SequenceError.txt com a mensagem
  "Timeout Disconnect1. Name[NULL],Host[..." (copy-paste do código original) —
  é um erro de SEQUÊNCIA, não timeout!
- Meus scripts mandavam seq='0' (0x30) → gameserver desconectava silenciosamente
  (sem resposta). Com **seq=0x00 no primeiro pacote** (e incrementando), o
  CGConnect passa e o gameserver responde TUDO: GCConnectOK + objetos + load
  do inventário (6079 bytes de resposta!).
- O loginserver NÃO valida sequência (por isso os scripts funcionavam lá).

## LOGS DE CONEXÃO DO GAMESERVER (ATIVADOS 2026-08-10)

- Flag: tabela DARKEDEN.AttrInfo, attrID=31 (LOG_INCOMING_CONNECTION), attr1=1
  (era 0). `UPDATE AttrInfo SET attr1=1 WHERE attrID=31;` + restart do gameserver.
  Confirmado no startup: "IncomingConnection 사용할 Log: ON".
- Arquivos (no cwd do gameserver = vsserver/):
  - connectionInfo.log: "Add [id:pc] ip (key)" e "Login [id:pc] ip (key)" (após
    os checks do CGConnectHandler) e "Expire [...]" (cleanup periódico 30s).
  - acceptNewConnection.log: "Accept FD : N (MinFD:..,MaxFD:..) ip".
  - connectionError.log: erros do CGConnectHandler (NoSuchConnectionInfo,
    Wrong Key, Wrong PCName, Expired).
  - ICMPI*.log: exceções no IncomingPlayerManager (ProtocolExcpt, SocketErr,
    ConectionErr). anc*.log: erros no acceptNewConnection.
- Com os logs ON, o teste com seq errado mostrou: Add → Expire (nunca processou).
  Com seq correto: Add → Login (processou!) → resposta de 6079 bytes.

## Scripts em /tmp/opencode/ (recriados em 10/08 — /tmp foi limpo)

- gs_live.py / gs_seq.py: fluxo completo (login→world→server→pc list→select pc
  →LCReconnect→CGConnect com seq=0). gs_seq.py usa seq correto e FUNCIONA.

## FATOS VERIFICADOS (2026-08-09 ~22h-23h)

- **O fluxo TCP/UDP do servidor FUNCIONA via script** (`/tmp/opencode/full_flow.py`
  e `gs_test2.py`): login → LCWorldList(450) → LCServerList(447) → LCPCList(439)
  → LCReconnect(443) com `ip=192.168.50.17 port=9998 key=...` ✓
  (isso PROVA que o gameserver processa o LGIncomingConnection via UDP e
  responde GLIncomingConnectionOK).
- **Bloqueio**: ao conectar no gameserver TCP 9998 e enviar CGConnect(475), o
  gameserver **aceita e fecha a conexão SEM nenhuma resposta** e SEM executar
  NENHUMA query no MySQL (confirmado via query log do MySQL:
  `/tmp/mysql_query.log` no container — só aparecem queries do loginserver).
- Causa mais provável: `getConnectionInfo(clientIP)` falha (NoSuchElement →
  "ILLEGAL ACCESS", close silencioso) OU key/PCName errados no CGConnectHandler
  (→ GCDisconnect buffered, não flushado → close silencioso). Os dois caminhos
  produzem o MESMO sintoma. Precisamos distinguir (próximo passo: habilitar
  FILELOG_INCOMING_CONNECTION do gameserver, hoje OFF — ver "IncomingConnection
  사용할 Log: OFF" no startup).

## IDs reais (família A) extraídos dos binários (símbolos ELF getPacketID__CXxxFactory)

Loginserver (vsserver/bin/loginserver) e Gameserver (vsserver/bin/gameserver):
- CL_LOGIN=145, CL_VERSION_CHECK=154, CL_RECONNECT_LOGIN=149, CG_ENCODE_KEY=15
- CL_GET_WORLD_LIST=144, CL_SELECT_WORLD=153, CL_SELECT_SERVER=152,
  CL_GET_SERVER_LIST=143, CL_GET_PC_LIST=142, CL_SELECT_PC=151,
  CL_CREATE_PC=140, CL_DELETE_PC=141, CL_QUERY_PLAYER_ID=148,
  CL_QUERY_CHARACTER_NAME=147
- LC_LOGIN_OK=438, LC_LOGIN_ERROR=437, LC_VERSION_CHECK_OK=449,
  LC_VERSION_CHECK_ERROR=448, LC_WORLD_LIST=450, LC_SERVER_LIST=447,
  LC_PC_LIST=439, LC_RECONNECT=443
- Gameserver: CGConnect=475, CGReady=62, CGLoadingReady=490, CGPortCheck=56,
  LGIncomingConnection=451, GLIncomingConnectionOK=420

## ⚠️ CRÍTICO — NÃO REBUILDAR SEM RECRIAR A FAMÍLIA A!

- Os binários RODANDO (loginserver 16:48, gameserver 17:20, sharedserver 17:21
  do dia 09/08) NÃO correspondem à fonte atual (`vsserver/src`).
- Fonte atual (Packet.h) = família B: CL_LOGIN=144, LC_LOGIN_OK=389.
  Binários rodando = família A: CL_LOGIN=145, LC_LOGIN_OK=438.
  Diferenças: região CL +1, regiões CG/LC +49 (~48 entradas extras entre o
  bloco CL e o bloco CG no enum). A fonte família A foi perdida (não está no
  git — nenhum commit/branch, nem no OLDCore [CL_LOGIN=143], nem na pasta
  compartilhada /media/sf_Server-source, nem no zip do cliente).
- Se rebuildar com a fonte atual, o servidor vai REJEITAR os pacotes do cliente
  (144/145 etc.) com "invalid packet order". Só rebuildar depois de descobrir
  as 48 entradas que faltam (comparar com o enum do binário via símbolos, ou
  recuperar a fonte família A).
- Cliente fengshen.bin (fev/2014) = família A (envia 145/154 — confirmado no
  log). Cliente fs_Debug.exe (mar/2014) = provavelmente família B.
- Fonte do cliente no zip (/media/sf_Client-source/Game(800)vs.zip,
  designed/project/Client) = família B também (CL_LOGIN=144). Usar só para
  estrutura/handlers, NÃO para IDs.

## Formatos de pacote confirmados

- Header TCP: packetID(2B LE) + packetSize(4B LE) + seq(1B) = 7 bytes.
- CLVersionCheck: body = Version(DWORD) + ServerVersion(DWORD) = 8B.
- CLLogin: szID(1)+ID+szPassword(1)+PW+MAC(6)+loginMode(1).
- LCReconnect(443): szIP(1)+IP+port(uint 4B)+key(DWORD 4B) — ex.:
  0d "192.168.50.17" 0e270000 0040bde1.
- LGIncomingConnection (UDP, id=451 no gameserver): body = szPlayerID(1)+ID+
  szPCName(1)+PCName+szClientIP(1)+IP. Header do datagrama: a conferir —
  Datagram::read consome ID(2)+size(4) e valida m_Length >= szPacketHeader(7)+
  packetSize; ver Datagram::write(const DatagramPacket*) no loginserver
  (linha ~243 do Datagram.cpp) para saber se o seq vai no datagrama.
- CGConnect (gameserver, 475): key(DWORD)+pcType(1)+szPCName(1)+Name+MAC(6).

## Descobertas / mudanças que fizeram o login funcionar

- Binário do cliente tem compilado: GameVersion=78786544 (0x04B22FF0) e
  ServerVersion=4455444 (0x43FC14) — extraído de fengshen.bin
  (mov [obj+0xD4],0x04B22FF0 / mov [obj+0xD8],0x0043FC14).
- DB estava com ClientVersion=(889861,958891) (valores da fonte mar/2014) →
  mismatch → servidor enviava LCVersionCheckError(448) → cliente crashava
  (AV em strlen) no handler de "versão errada".
- CORREÇÃO APLICADA: `UPDATE ClientVersion SET Version=78786544,
  ServerVersion=4455444;` → servidor responde LCVersionCheckOK(449). Funcionou
  (sem rebuild).

## Ambiente / ferramentas

- VM (Debian): IP **192.168.50.19** (DHCP — já foi .14 e .17! Sempre conferir
  `ip -4 addr show enp0s3`; o usuário atualizou ServerInfo.inf do cliente para
  .19). Cliente no PC: 192.168.50.16.
- ⚠️ IP dinâmico: se a VM reiniciar, o IP pode mudar → atualizar
  ServerInfo.inf no cliente (Data/Info/ServerInfo.inf) e GameServerInfo no DB.
- Servidores rodam em /run/media/pmateus/Dados/vssource/vsserver (NÃO é a
  pasta compartilhada /media/sf_Server-source, embora sejam cópias parecidas).
- Logs: vsserver/log/loginserver.out, gameserver.out, sharedserver.out.
  Gameserver demora ~40-120s para inicializar (1604 zonas) — testar só depois
  de "ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY".
- ⚠️ O loginserver pode demorar MUITO para subir (6+ min observado) — esperar
  a porta 9999 responder (ss -tln | grep 9999) antes de testar.
- gameserver: `log()` está TODO comentado (LogClient.cpp) → nenhum log de
  conexão aparece. FILELOG_INCOMING_CONNECTION agora está ON (AttrInfo 31).
- MySQL 4.1 no container darkeden-mysql. Query log ATIVO via /etc/my.cnf
  (log=/tmp/mysql_query.log) — restart do container derruba as conexões dos
  servidores → é preciso ./stop-servers.sh && ./start-servers.sh depois.
- tcpdump SEM permissão na VM (sem CAP_NET_RAW) — usar ss/python/socat.
- strace SEM permissão também (ptrace).

## Próximos passos (histórico — itens 1-3 já superados; ver "ÚLTIMOS ACHADOS")

1. ~~Testar o cliente REAL de novo~~ (FEITO: não conecta no gameserver — ver
   "ÚLTIMOS ACHADOS"; logs ON confirmaram: Add do CI, sem Accept).
2. ~~Erro de sequência no cliente real~~ (descartado — o cliente nem chega a
   conectar no gameserver; a seq do cliente é 0,1,2... correta).
3. ~~Handler LCReconnect no-op~~ (descartado — o binário TEM o handler ativo
   com as strings "Reconnecting to"/"Sending CGConnect").
4. Depois de entrar: conferir ZoneID/ServerGroupID do personagem (TroniPM:
   ZoneID? — loginserver mostra GameWorldInfo Size:0 e group "ä�θ� - 1ä��"
   (nome coreano garbled — encoding).
