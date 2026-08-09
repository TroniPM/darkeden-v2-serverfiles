# vssource (DarkEden) - estado da investigação 2026-08-06

## Estrutura
- Raiz: /home/pmateus/Downloads/vssource (git repo). build-local.sh + wipe-all.sh na raiz (copiados do outro projeto, precisam ser refeitos/ajustados).
- vsserver/ = server-master deste projeto (src/, conf/, data/, sqls/, docker/).
- data/: "data - coreano"/data (628 arq, bins com nome coreano EUC-KR) e data-ingles/data (581 arq, bins em inglês + lua/). Ambos têm .smp/.ssi (mapas), EventGQuest.xml, TravelWay.xml. Decisão do usuário: copiar data-ingles/data para vsserver/data (data ativa).
- sqls/: a-setup.sql (cria DARKEDEN+USERINFO, user elcastle/elca110), DARKEDEN.sql (dump 5.7.35, 4.2MB, 374 tabelas — WorldDBInfo já com 127.0.0.1, sem odk-mysql), USERINFO.sql (7 tabelas). files/ tem DARKEDEN.tar.gz + USERINFO.tar.gz = dados binários MyISAM (NÃO usar, manter como backup).
- docker/: Dockerfile (Ubuntu 22.04 + deps), docker-compose.yml (mysql:5.7 container darkeden-mysql, porta 3306 EXPOSTA, volume ./mysql-data, monta ../sqls em /docker-entrypoint-initdb.d; serviço build), build.sh, build-server.sh, g++-compat, mysql.sh.
- src/: Core/ e OLDCore/ (quase idênticos; Core tem a mais: CGLoadingGearReady, CGLoadingReady, CGRequestWebMarket + Makefile com dependências extras). Core = ativo (Makefile raiz chama Core/, não OLDCore).
- conf/: gameserver.conf (TCPPort 9998, DB 127.0.0.1:3306 elcastle/elca110, ServerID:0, HomePath:.), loginserver.conf (9999), sharedserver.conf (9977), updateserver.conf (HomeDir:/darkeden, Port 3000 — precisa ajustar). Git mostra deletados: excel96-*.conf + backup/ (usuário já limpou).
- src/Makefile targets: all, allgameserver, allloginserver, allsharedserver, alltheoneserver, clean*.
- gameserver Makefile: SYSLIBS tem -lnsl (11 ocorrências no total — REMOVER), sem libstdc++.so.6, sem regra $(DEPDIR)/%.d (0 Makefiles com ela — bug make 4.4). 64 Makefiles no total.
- 2256 ocorrências de throw() em destrutores (~2342 no outro projeto — precisa remover).
- Handlers perdidos do outro projeto: TODOS EXISTEM aqui (CGDisplayItemHandler, CGDonationMoneyHandler, CGTakeOutGoodHandler, GCSubInventoryInfoHandler).
- PacketFactoryManager.cpp linha 1011: addFactory(new GMServerInfoFactory()) já presente no bloco __LOGIN_SERVER__.
- Backticks Rank/Condition/Master: 74 ocorrências sem backtick ainda (outro projeto corrigiu ~40).
- TreasureList/fallback HName→EName: NÃO aplicado aqui (usuário quer evitar mexer no código — avaliar no momento de subir; decisão: data-ingles em data/, se faltar bin para alguns monstros com HName coreano no banco, aí sim aplicar fix).

## Decisões do usuário (2026-08-06)
1. Build: LOCAL no host (igual outro projeto) — g++-11 + wrapper /tmp/darkeden-gcc. Docker SÓ para MySQL 5.7.
2. data ativa: copiar data-ingles/data → vsserver/data (HomePath=.).
3. Tarballs myd/myi/frm: ignorar/arquivar (usar dumps SQL).
4. updateserver/update: compilar e documentar (mas foco nos 3 servidores).
5. Evitar mexer no código-fonte salvo necessidade estrita (avaliar treasure HName no momento de subir).

## Host (Ubuntu 26.04) já tem instalado
- g++-11 (11.5.0) e g++ 15.2.0; Docker 29.1.3 + Compose 2.40.3.
- Lua 4.0.1 em /usr/local (lua.h, liblua.a); compat_stl shims em /usr/local/include/compat_stl; symlink /usr/local/include/mysql → /usr/include/mysql; libmysqlclient-dev (mysql.h em /usr/include/mysql); xercesc (PlatformUtils.hpp OK).
- OU SEJA: install-local.sh provavelmente NÃO precisa rodar de novo (deps já no lugar). build-local.sh só precisa recriar wrapper /tmp/darkeden-gcc.

## Fixes pendentes antes do build (do outro projeto — SERVER_DECISIONS.md)
1. Remover throw(...) de destrutores (~2256) — 3 passadas sed/perl.
2. Remover -lnsl dos SYSLIBS (11 Makefiles).
3. Adicionar regra $(DEPDIR)/%.d: %.cpp | $(DEPDIR) em todos os Makefiles (bug make 4.4, 64 Makefiles).
4. Adicionar -L/usr/lib/x86_64-linux-gnu -l:libstdc++.so.6 ao SYSLIBS (gameserver, loginserver, sharedserver).
5. Backticks Rank/Condition/Master (74 ocorrências).
6. Avaliar no runtime: treasure HName→EName (data-ingles pode já resolver), nomes >20 bytes, Mutex self-deadlock, packet 422 (já ok aqui).
7. updateserver.conf: HomeDir:/darkeden → ajustar (data/patch), Port 3000.
8. WorldDBInfo já ok (127.0.0.1, sem odk-mysql).

## PLANO DE INSTALL (2026-08-06, 2ª parte)
- Usuário quer install-local.sh TESTADO do zero (pessoa nova consiga replicar).
- Investigação STLport NESTE repo concluída:
  - USO REAL: hash_map (115 includes; chaves = typedefs numéricos: ObjectID_t=DWORD, ZoneID_t=WORD, GuildID_t=WORD, QuestID_t=DWORD, SkillType_t=WORD, int, string, etc — TODAS hasháveis por std::hash no C++11, sem custom hasher), slist (36 includes; métodos usados: begin/end/empty/front/push_front/pop_front/size/clear + erase_after/insert_after (Tile.cpp) — forward_list cobre tudo EXCETO size(); GuildInfo2.cpp/h, GCActiveGuildList/GCWaitGuildList/GCGuildMemberList/GCShowWaitGuildInfo usam .size() (90 usos) → shim slist PRECISA de size() extra (forward_list não tem) ou trocar por std::list), algo.h (12), fstream.h (10), iostream.h (4).
  - Sector.cpp m_Objects é hash_map (não slist) — .erase(itr) OK.
  - CONCLUSAO: shims SIM são necessários (hash_map, slist, algo.h, fstream.h, iostream.h), mas são "shims de compatibilidade" (não stubs vazios) — hash_map→unordered_map, slist→forward_list+size() (implementar size() manual ou usar std::list), algo.h→algorithm, iostream.h→iostream+using, fstream.h→fstream+using. NÃO é stub de arquivo; é typedef/alias de STL real do g++.
  - Alternativa sem shims: editar os ~177 includes nos fontes (não recomendado).
- install-local.sh precisa: apt (build-essential, g++-11, libmysqlclient-dev, libxerces-c-dev, zlib1g-dev), Lua 4.0.1 da fonte, shims compat_stl, symlink /usr/local/include/mysql. E TESTAR do zero (desinstalar/simular máquina limpa) para validar replicabilidade.

## MUDANÇA DE ROTA (2026-08-06): BUILD NO DOCKER (usuário mudou de ideia)
- Usuário NÃO quer mais build no host (medo de quebrar o PC). Quer TUDO no Docker. Confirmou: Ubuntu 22.04 (não Alpine).
- Criados em vsserver/docker/:
  - setup-docker.sh (host): instala docker.io + docker-compose-v2 + grupo docker + validação
  - build-image.sh (host): docker build -f Dockerfile.build -t darkeden-build:latest
  - Dockerfile.build: Ubuntu 22.04 + build-essential + g++-11 + libmysqlclient-dev + libxerces-c-dev + Lua 4.0.1 da fonte (make all gera liblualib.a REAL) + shims de docker/compat_stl/ + symlink mysql + g++-compat
  - test-compile.sh (host): roda teste de compilação DENTRO do container (GameTime, SXml, GuildInfo2, Tile)
  - compat_stl/ (5 arquivos versionados no repo): hash_map (unordered_map), slist (WRAPPER de std::list com size/insert_after/erase_after — validado), algo.h, iostream.h, fstream.h
- ⚠️ Contexto de build é docker/ (build-image.sh roda de docker/) — COPY usa paths relativos a docker/ (compat_stl/, g++-compat), NÃO docker/xxx.
- ✅ IMAGEM darkeden-build:latest CONSTRUÍDA com sucesso.
- ✅ test-compile.sh: GameTime OK, SXml OK (hash_map), GuildInfo2 OK (slist size), Tile só falha por throw() em destrutores (ajuste de código pendente, não shim).
- install-local.sh (raiz) NÃO é mais o caminho principal — manter como alternativa documentada (usuário pediu p/ deixar documentado se precisar depois).

## FIXES DE CÓDIGO JÁ APLICADOS (durante teste, valem no src/ montado no docker)
1. SystemTypes.h: BUILD_INFO quebrado em 1 linha; DWORD = unsigned int (não unsigned long — 64-bit!); ulonglong no Linux OK.
2. SXml.h/cpp: overloads AddAttribute/GetAttribute(DWORD) comentadas (DWORD==unsigned int agora colide); fechou comentário; file==NULL → !file (ofstream).
3. Zone.h:298: transportItem tinha parâmetro duplicado 'y' → 'cy'.
4. Utility.h e SocketInputStream.h: adicionado #include <cstring>.

## PRÓXIMOS PASSOS (documentar e depois buildar)
- README: atualizar para fluxo Docker (setup-docker → build-image → test-compile → build-server → mysql).
- build.sh dentro do container: precisa do fix .deps (make 4.4), -lnsl remover, libstdc++ link, throw() remover, backticks MySQL.

## FLUXO DE COMPILAÇÃO POR SERVIDOR (descoberta 2026-08-06) — respondendo usuário
- O código é um ÚNICO source-tree compilado 4x com defines diferentes por servidor:
  - Core/Cpackets/GS/Makefile → DEFS = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
  - Core/Cpackets/LS/Makefile → DEFS = -D__LINUX__ -D_REENTRANT -D__LOGIN_SERVER__
  - Core/Cpackets/SS/Makefile → DEFS = -D__LINUX__ -D_REENTRANT -D__SHARED_SERVER__
  - (também existe US = __UPDATE_SERVER__ e raiz Cpackets compila com __GAME_SERVER__)
- POR ISSO existe #ifdef __GAME_SERVER__: o MESMO arquivo .cpp (ex: CGSayHandler.cpp)
  é compilado 3-4x, cada vez com um define diferente, gerando objetos diferentes
  (CGSayHandler.o no GS, CGSayHandler.o no LS, etc). Os métodos que só existem no
  gameserver ficam dentro de #ifdef __GAME_SERVER__ para NÃO existirem no LS/SS.
- CONSEQUÊNCIA: declarar opcommand FORA do #ifdef (como fiz) é correto e NECESSÁRIO
  porque o PKZoneInfoManager.h (incluído por Cpackets SS/LS/raiz sem __GAME_SERVER__)
  declara friend CGSayHandler::opcommand — precisa existir em TODOS os contextos.
- ⚠️ Já validado: COM __GAME_SERVER__ e SEM __GAME_SERVER__ compilam OK (sem duplicação).
- Makefile raiz: src/Core/Makefile delega para Cpackets (all → GS+LS+SS; allgameserver → GS).

## AJUSTE #4 NÃO NECESSÁRIO (2026-08-06) - libstdc++ link
- No container (Ubuntu 22.04): g++-11 e libstdc++ do sistema = GLIBCXX 3.4.30;
  libmysqlclient exige 3.4.29, libxerces/icuuc 3.4.11 → SEM conflito.
- Teste de link real (g++-11 + mysqlclient + xerces) dentro do container: exit 0, roda.
- ❌ NÃO adicionar -L/usr/lib/x86_64-linux-gnu -l:libstdc++.so.6 (desnecessário no Docker).
- ⚠️ Só seria necessário no HOST (Ubuntu 26.04, libmysqlclient 8.4 exige 3.4.30-32).

## AJUSTE #3 NÃO NECESSÁRIO (2026-08-06) - make 4.4 .deps bug
- O build roda no DOCKER (Ubuntu 22.04) que tem make 4.3 — o bug do .deps do make 4.4
  NÃO existe no 4.3 (testado dentro do container: build com .deps vazio funciona).
- ❌ NÃO aplicar o fix-makefile-deps (64 Makefiles) — desnecessário para o fluxo Docker.
- ⚠️ SÓ seria necessário se o build fosse no HOST (Ubuntu 26.04, make 4.4.1).

## AJUSTE #2 APLICADO (2026-08-06) - -lnsl removido
- ✅ Removido -lnsl dos 10 Makefiles (gameserver, loginserver, sharedserver, updateserver,
  theoneserver, chinabilling, billing, mofus, mofus/testserver, quest/Squest).
- Comprovado: código NÃO usa funções da libnsl (grep yp_*/gethostbyname = 0); libnsl.so.1
  existe mas libnsl.so (dev) NÃO existe no Ubuntu 26.04 → -lnsl falhava o link.
- SYSLIBS agora: gameserver = -lpthread -lutil -ldl -lmysqlclient -llua -llualib -lz -lcppunit
  (sem -static em updateserver que só tem -lpthread).
- Faltam ajustes: #3 .deps (64 Makefiles, bug make 4.4), #4 libstdc++ link, #5 backticks MySQL (~74).
- ✅ fix-throw-destructors.sh criado na raiz: remove throw(...) SOMENTE de destrutores
  (métodos comuns NÃO são tocados — decisão do usuário de manter exceptions).
- ✅ Aplicado: 1765 arquivos alterados, 2250 throw() de destrutores removidos (Core+server).
- ✅ VALIDAÇÃO COMPLETA: GameTime OK, SXml OK, GuildInfo2 OK, PlayerCreature OK (erase_after),
  Tile OK (insert_after/erase_after) — shim slist 100% validado.
- ⚠️ FIX ESTRUTURAL opcommand: CGSay.h (4 cópias) agora declara opcommand TAMBÉM fora do
  #ifdef __GAME_SERVER__ (senão friend do PKZoneInfoManager.h falha em SS/LS/raiz que não
  definem __GAME_SERVER__). PKZoneInfoManager.h friend ganhou throw(ProtocolException, Error).
- ⚠️ Os .cpp de opcommand JÁ TINHAM throw (linha seguinte) — não havia mismatch .h/.cpp ali;
  o problema era só o #ifdef.
- Restam ajustes: #2 -lnsl (11 Makefiles), #3 .deps (64 Makefiles), #4 libstdc++ link,
  #5 backticks MySQL (~74). Depois: build completo via docker.
- ✅ Imagem darkeden-build:latest construída (674MB) — test-compile.sh valida: GameTime OK, SXml OK (hash_map), GuildInfo2 OK (slist size). Tile só falta throw().
- ✅ Scripts criados e com sintaxe OK: setup-docker.sh, build-image.sh, Dockerfile.build, test-compile.sh, compat_stl/ (5 shims versionados).
- ✅ README atualizado: Docker é o caminho PRINCIPAL; install-local.sh/build-local.sh ficam como ALTERNATIVA documentada (não recomendada).
- ⚠️ Contexto de build = docker/ (build-image.sh roda de docker/) → COPY de compat_stl/ e g++-compat (paths relativos, sem prefixo docker/).
- ⚠️ build-server.sh (compose) ainda usa o Dockerfile antigo (não o Dockerfile.build) — para o build completo via compose talvez precise apontar para Dockerfile.build ou ajustar o serviço build do compose. Verificar na próxima etapa.
- ⚠️ docker-compose.yml serviço "build" usa Dockerfile (antigo) + build.sh (container). Para o build completo falta: ajustar o serviço build para usar a imagem darkeden-build OU o Dockerfile.build, e aplicar ajustes 1-5 (throw(), -lnsl, .deps, libstdc++, backticks).
- Não esquecer: restaurar /usr/local no host? Não — usuário não quer build no host; o que instalei no host (Lua, shims, symlink) pode ficar (não quebra nada) ou ser removido depois. Backup em /root/vssource-install-backup/.
- ✅ README.md criado na raiz de /home/pmateus/Downloads/vssource com 8 milestones + decisões em aberto + troubleshooting. Baseado nas decisões do usuário (build local, data-ingles, dumps SQL, updateserver compilar+documentar, evitar mexer no código).

## Planos (próximos passos)
- Criar scripts: install-local.sh (se faltar deps), fix-makefile-deps.sh, rebuild-gameserver.sh, start-servers.sh, stop-servers.sh.
- Aplicar ajustes 1-5 (throw(), -lnsl, .deps, libstdc++, backticks) quando for buildar.
- Scripts a refazer/ajustar: build-local.sh (raiz, já existe), instalar deps (novo install-local.sh?), start-servers.sh/stop-servers.sh (novos, no vsserver/), fix-makefile-deps.sh, rebuild-gameserver.sh, mysql.sh (docker/ já existe OK), wipe-all.sh (raiz já existe).
