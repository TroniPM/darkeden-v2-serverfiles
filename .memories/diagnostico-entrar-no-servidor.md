# Diagnóstico: entrar no servidor (2026-08-09 ~23h, em andamento)

Situação: login OK (test123/test456) e personagem criado (TroniPM, Slayer).
Ao selecionar o personagem e clicar no servidor, o cliente é **deslogado e
volta para a tela inicial do jogo**. O cliente nunca chega ao gameserver.

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

- VM (Debian): IP **192.168.50.17** (mudou — antes .14). Cliente no PC:
  192.168.50.16 (ServerInfo.inf do cliente aponta para .17:9999 ✓).
- Servidores rodam em /run/media/pmateus/Dados/vssource/vsserver (NÃO é a
  pasta compartilhada /media/sf_Server-source, embora sejam cópias parecidas).
- Logs: vsserver/log/loginserver.out, gameserver.out, sharedserver.out.
  Gameserver demora ~40s para inicializar (1604 zonas) — testar só depois de
  "ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY".
- gameserver: `log()` está TODO comentado (LogClient.cpp) → nenhum log de
  conexão aparece. FILELOG_INCOMING_CONNECTION está OFF ("IncomingConnection
  사용할 Log: OFF" no startup) — habilitar para diagnóstico definitivo.
- MySQL 4.1 no container darkeden-mysql. Query log ATIVO via /etc/my.cnf
  (log=/tmp/mysql_query.log) — restart do container derruba as conexões dos
  servidores → é preciso ./stop-servers.sh && ./start-servers.sh depois.
- tcpdump SEM permissão na VM (sem CAP_NET_RAW) — usar ss/python/socat.
- Scripts úteis em /tmp/opencode/: capture_resp.py, full_flow.py,
  gs_connect_test.py, gs_test2.py (fluxo completo + CGConnect).

## Próximos passos (hipóteses a testar)

1. Habilitar FILELOG_INCOMING_CONNECTION no gameserver (achar a flag no
   gameserver.conf / LogDef.h) e reiniciar → ver connectionError.log:
   "NoSuchConnectionInfo" vs "Wrong Key" vs "Wrong PCName" vs "Expired".
2. Se NoSuchConnectionInfo: investigar parse do datagrama UDP
   (Datagram::write pkt no loginserver vs Datagram::read no gameserver —
   alinhamento do byte de seq) e o clientIP registrado vs o IP da conexão TCP.
3. Verificar CGConnectHandler do gameserver: o que mais pode falhar antes da
   query (checks de key/pcName/expire). Confirmar formato do GCConnectOK.
4. Depois de entrar: conferir ZoneID/ServerGroupID do personagem (TroniPM:
   ZoneID? — se for zona de login, o ZoneGroupInfo/GameServerInfo precisa
   existir; loginserver mostra GameWorldInfo Size:0 e group "ä�θ� - 1ä��"
   (nome coreano garbled — encoding)).
