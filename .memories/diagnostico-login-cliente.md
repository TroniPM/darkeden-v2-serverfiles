# Diagnóstico: login pelo cliente (2026-08-08, atualizado 2026-08-09 ~23h)

**STATUS: RESOLVIDO — login + criação de personagem funcionando!**
O usuário logou com sucesso (test123/test456) e criou o personagem
**TroniPM** (Slayer). O próximo problema (entrar no servidor) está em
`diagnostico-entrar-no-servidor.md`.

Situação original: cliente DarkEden (binário `fengshen.bin` de
3.207.168 B, compilado 11/fev/2014) no PC fora da VM fechava imediatamente
ao tentar logar. RESOLVIDO com UPDATE na tabela ClientVersion (ver abaixo).


## Estado do servidor (verificado)

- 3 servidores no ar: loginserver (9999), sharedserver (9977), gameserver
  (9998). Gameserver: 157 zonas, "ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY".
- Porta 9999 escutando em 0.0.0.0, acessível via nc localmente e no IP da VM
  (192.168.50.14).
- `GameServerInfo.IP` = 192.168.50.14 (2 linhas) — cliente conecta no gameserver por esse IP.
- Conta de teste criada: `test123` / `test456` → senha gravada com
  `OLD_PASSWORD('test456')` = `3f02140166481991` na tabela `DARKEDEN.Player`.
  (Formato confirmado: kanarea/korad2 usam OLD_PASSWORD('123456')).
- `DB_VERSION : 4` adicionado ao `vsserver/src/conf/loginserver.conf` — SEM
  ele, o CLLoginHandler usa `PASSWORD()` (41 chars) e nenhuma conta loga
  (senhas estão em OLD_PASSWORD, 16 hex).

## Sintoma observado

- `loginserver.out`: 0x "NEW CONNECTION" — nenhuma conexão do cliente chegou.
- `loginfail.txt`: vazio.
- Conclusão: o cliente fecha ANTES de chegar ao loginserver. O problema é do
  cliente/configuração, não do servidor (falta prova por simulação).

## Hipóteses para o cliente fechar na hora

1. **Launcher do DarkEden original consulta o updateserver (porta 3000)
   primeiro** — o updateserver NÃO está rodando (não é iniciado pelo
   start-servers.sh). Se o launcher não acha, pode fechar imediatamente.
   Pendente: subir `vsserver/bin/updateserver` (conf `src/conf/updateserver.conf`,
   porta 3000) e testar.
2. IP/porta errados configurados no launcher do cliente (deve ser
   192.168.50.14:9999 para o loginserver).
3. Se o cliente for o client-master SDL: a rede está comentada no código
   (`//strcpy(g_ServerIP, SERVER_IP)`, `LoginServerAddress` comentado) — a
   migração SDL não tem conexão implementada.

## Protocolo mapeado (para simular login via script)

- Header (7 bytes, little-endian): `packetID` (ushort, 2B) + `packetSize`
  (uint, 4B) + sequence (1B, '0').
- Pacote de login `CLLogin` = **PACKET_CL_LOGIN = 145** (ATENÇÃO: valor do
  enum ATIVO no Packet.h — ordinal. O valor 153 comentado no Packet.h é do
  enum ANTIGO desativado, não é usado).
- Body: `szID`(1) + ID + `szPassword`(1) + senha + MAC(6) + `loginMode`(1).
  Body size = 1+len(ID)+1+len(PW)+6+1 (ex.: 23 p/ test123/test456).
- Respostas: `PACKET_LC_LOGIN_OK` = 438, `PACKET_LC_LOGIN_ERROR` = 437
  (mesmo header) — ordinais do enum ativo.
- Criptografia de stream: **comentada** no código (`Player::setKey` em bloco
  `/* */`) — tráfego em texto puro, simulação simples.
- Validador: no estado LPS_BEGIN_SESSION, aceita CL_LOGIN (145),
  CL_RECONNECT_LOGIN (149), CL_VERSION_CHECK (154), CG_ENCODE_KEY (15).

## SIMULAÇÃO CONFIRMADA (2026-08-09): login 100% funcional

- `/tmp/opencode/simulate_login_145.py` (usa CL_LOGIN=145):
  - senha correta (test123/test456) → **packetID=438 (LCLoginOK)** ✓
  - senha errada → **packetID=437 (LCLoginError)** ✓
  - usuário inexistente → **packetID=437** ✓
- DBG do servidor confirmam: `isValidPacketID OK`, `CLLoginHandler rows=1`,
  `LOGIN OK -> enviando LCLoginOK`.
- CONCLUSÃO: servidor está FUNCIONAL. O valor 153 (do enum comentado) é
  RED HERRING — se o cliente real mandar 153, ele será rejeitado com
  "invalid packet order". Precisamos descobrir qual valor o cliente real usa.

## INCOMPATIBILIDADE DE PROTOCOLO (ponto crítico)

- `vssource/src/Core/Packet.h` tem DOIS enums:
  - 1º (linhas 70-559): **comentado** `/* */` → PACKET_CL_LOGIN=153.
  - 2º (linhas 561-1056): **ativo**, valores ORDINAIS → PACKET_CL_LOGIN=145.
- `opendarkeden - server-master/src/Core/Packet.h`: enum ÚNICO → CL_LOGIN=**153**.
- `opendarkeden - client-master/Client/Packet/Packet.h`: enum ÚNICO → CL_LOGIN=**153**.
- Consequência: se o cliente real do PC envia CL_LOGIN=153 (protocolo
  opendarkeden/original), o servidor vssource (que espera 145) rejeita com
  "invalid packet order" e fecha a conexão SEM resposta → sintoma do cliente
  fechando.
- A simulação com 145 prova que o SERVIDOR está correto conforme o vssource;
  resta saber qual protocolo o cliente real do usuário usa (145 ou 153).

## Como descobrir o packetID do cliente real

1. Subir loginserver com DBG (`cerr`) ativos e pedir ao usuário para tentar
   logar com o cliente real no PC.
2. Olhar o log (`vsserver/log/loginserver.out` ou `/tmp/opencode/ls_dbg*.out`):
   - `DBG processCommand: packetID=153` → cliente usa protocolo
     antigo/opendarkeden → ajustar o servidor (ou o enum) para aceitar 153.
   - `packetID=145` → cliente já é compatível e o problema era outro
     (updateserver etc).

## TESTE REAL DO CLIENTE (2026-08-09) — novo dado decisivo

- **Simulador 145 NA MÁQUINA HOST** (PC fora da VM), apontando para
  `192.168.50.14`: a conexão CHEGA e o servidor responde de forma idêntica
  à simulação local (login OK / erro conforme credencial). ✓
  → PROVA: rede bridge, porta 9999, firewall e servidor estão 100% OK para
  tráfego vindo do host. Não há problema de alcance de rede.
- **Cliente do jogo REAL no mesmo PC**: **NÃO aparece NADA nos logs do
  loginserver** — nem `acceptNewConnection`, nem `processCommand`, nem
  "NEW CONNECTION". O cliente real NÃO chega a conectar no loginserver.
- CONCLUSÃO REVISADA: o problema NÃO é protocolo (145 vs 153) — o cliente
  real nem sequer abre conexão TCP com a porta 9999. Ele fecha ANTES, em
  etapa anterior. Causas mais prováveis:
  1. **Launcher/loader do DarkEden original consulta o updateserver
     (porta 3000) ANTES de qualquer coisa** — se não há resposta, o
     cliente fecha na hora. O updateserver NÃO roda (não está no
     start-servers.sh). Próximo teste: subir updateserver.
  2. Cliente configurado com IP/porta de loginserver errados no launcher
     (deve ser 192.168.50.14:9999).
  3. Se for o client-master SDL: rede comentada no código (migração SDL não
     implementa conexão).

## Próximos passos

1. ~~Rodar simulação de login~~ (FEITO: login funcional com CL_LOGIN=145,
   inclusive DO HOST via 192.168.50.14)
2. **Subir updateserver (porta 3000)** e testar o launcher do cliente real no
   PC — provável causa do cliente fechar antes de conectar.
3. Se ainda fechar: capturar tráfego no host (tcpdump/wireshark em
   192.168.50.14:9999 e :3000) para ver para onde o cliente real tenta
   conectar de fato.
4. Identificar a versão/origem do cliente usado no PC (pendente).
5. Questão do packetID (145 vs 153) fica em PAUSA — só importa depois que o
   cliente real conseguir chegar ao loginserver.

## AVANÇO REAL DO CLIENTE (2026-08-09, noite) — CLIENTE CHEGA AO LOGINSERVER!

- O cliente real (`fengshen.bin` de 3.207.168 B, compilado 11/fev/2014, da
  pasta `/media/sf_Client-exe` = "Game(800)" — NÃO é o fs_Debug.exe, nem o
  fengshen.bin do zip da fonte) agora CONECTA no loginserver (VM agora tem IP
  **192.168.50.17**; `ServerInfo.inf` do cliente aponta para .17:9999 ✓) e
  envia: `CLVersionCheck(154)` + `CLLogin(145)` — mas CRASHA (Access
  Violation 0xc0000005, dentro de `strlen` @ 0x00645860) ao receber a
  resposta do servidor.
- CrashReport2.log (cliente): AV em strlen com ponteiro inválido.
- Protocolo do binário (família A): CL_LOGIN=145, CL_VERSION_CHECK=154,
  CL_RECONNECT_LOGIN=149, CG_ENCODE_KEY=15 — CONFIRMADO por captura e pelo
  binário rodando (extração via símbolos ELF).

## POR QUE CRASHAVA — CAUSA RAIZ ENCONTRADA (2026-08-09 noite)

- O loginserver RODANDO (`vsserver/bin/loginserver`, build 16:48, família A)
  NÃO corresponde à fonte atual do Packet.h (família B: CL_LOGIN=144,
  LC_LOGIN_OK=389; LC region difere em ~49 entradas). A fonte família A foi
  perdida — NÃO rebuildar do zero sem recriar a família A!
- IDs reais do servidor rodando (extraídos dos símbolos ELF):
  LC_LOGIN_OK=**438**, LC_LOGIN_ERROR=**437**, LC_VERSION_CHECK_OK=**449**,
  LC_VERSION_CHECK_ERROR=**448**, LC_WORLD_LIST=**450**, LC_SERVER_LIST=**447**.
  O cliente espera exatamente esses (mesma família A) ✓.
- **CAUSA DO CRASH**: a tabela `DARKEDEN.ClientVersion` tinha (889861, 958891)
  (valores da fonte Mar/2014), mas o binário fev/2014 envia Version=**78786544**
  e ServerVersion=**4455444** (constantes extraídas do binário). O servidor
  comparava e enviava **LCVersionCheckError (448)** → handler do cliente de
  "versão errada" → crash (strlen em string inválida da tabela de mensagens).
- CORREÇÃO APLICADA (2026-08-09 22h, SEM rebuild): 
  `UPDATE ClientVersion SET Version=78786544, ServerVersion=4455444;`
  → teste com script (mesmos valores do cliente) agora devolve
  **packetID=449 (LCVersionCheckOK)** + **438 (LCLoginOK, body 5B)** ✓.
- PENDENTE: usuário testar o cliente real no PC. Próximo passo esperado:
  cliente envia CLGetWorldList → servidor responde LCWorldList (450) → ...
  Observar loginserver.out.

## Fonte do cliente (zip /media/sf_Client-source/Game(800)vs.zip)

- `designed/project/Client/...` = código-fonte do cliente (Mar/2014, família B
  — NÃO corresponde ao binário fev/2014; usar só p/ estrutura/handlers).
- Login flow: `UIMessageManager.cpp` (~linha 1900, Execute_UI_LOGIN): envia
  CLVersionCheck (versão de `g_pUserInformation->GameVersion/ServerVersion`)
  + CLLogin, seta CPS_AFTER_SENDING_CL_LOGIN, MODE_WAIT_LOGINOK.
- Handler LCLoginOK: envia CLGetWorldList e espera LCWorldList.
- Handler LCVersionCheckError: mostra dialog de versão errada (suspeito do crash).
- Criptografia de stream desativada nos DOIS lados (setKey comentado).
- Header pacotes: packetID(2) + packetSize(4) + seq(1) = 7 bytes. ✓
