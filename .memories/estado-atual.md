# Estado atual (2026-08-07) — projeto movido para /run/media/pmateus/Dados/vssource

## ✅ OS 3 SERVIDORES NO AR (2026-08-07, ~19:00) — loginserver 9999, sharedserver 9977, gameserver 9998
- gameserver CONECTA no sharedserver ("connection to sharedserver established",
  trocam GSRequestGuildInfo/SGGuildInfo). 155 zonas carregadas (todas dos grupos ativos).
- LINHA DO TEMPO da correção (tudo por causa do banco/dados errados):
  1. Dump opendarkeden tinha schema ERRADO (EffectItemInfo sem NotEffectClass,
     sem EtheRealInfo) → gameserver morria a cada tabela
  2. 🗄️ BANCO REAL DESCOBERTO: vsserver/sqls/ (tarballs
     DARKEDEN.tar.gz + USERINFO.tar.gz) = arquivos .FRM/.MYD/.MYI REAIS do servidor
     original. Substituiu o dump: DARKEDEN 411 tabelas, USERINFO 5. MySQL 4.1
     leu direto (formato MyISAM compatível). EffectItemInfo com 31 rows reais,
     EtheRealInfo presente. O dump do opendarkeden foi DESCARTADO.
  3. WorldDBInfo do banco real apontava pro MySQL original (192.168.80.2, user
     vsvs/wkddodls123) → UPDATE pra 127.0.0.1/elcastle/elca110 (senha do vsvs
     ainda está no banco, caso precise)
  4. 18 zonas sem arquivos de mapa (menegroth_1f..6f, tiffauges_castle,
     hell_garden, Office_B1, cave_office) — não existem em NENHUMA pasta de data
     → excluídas dos grupos (ZoneGroupID=0). Não há os .smp/.ssi em lugar nenhum
     (nem no client-master)
  5. 🐛 BUG STLPORT (2001): Zone::load tenta abrir o smp com o nome do banco;
     se falha, faz strlwr e tenta de novo — MAS o ifstream fica com estado de
     erro do 1º open e o 2º open() NÃO limpa (strace prova: open() retorna fd,
     mas !SMP continua true) → FileNotExistException sempre que o nome do banco
     não batia EXATO com o disco. No Windows/VC6 funcionava; no Linux/STLport não.
     FIX SEM REBUILD: UPDATE ZoneInfo SET SmpFileName/SsiFileName = nome EXATO
     do arquivo em disco (os arquivos têm caixa MISTA: eslania_NW.smp com NW
     maiúsculo, limbo_lair_ne.smp minúsculo...). Script: /tmp/opencode/fix-names.sql
  6. GameServerInfo do banco real tinha IP 192.168.80.2 (servidor original) →
     UPDATE pra 127.0.0.1 (é o que o cliente recebe pra conectar). Nomes
     DK2TH KOR1/KOR2 mantidos.
- Obs: o retry bugado do strlwr ainda existe no código (Zone.cpp:875-886) — se
  algum dia recompilar, adicionar SMP.clear() antes do 2º open.
- ✅ setup-mysql.sh (raiz) atualizado: MySQL 4.1 (tarballs + patch-compat.sql)


## ✅ SHAREDSERVER NO AR (2026-08-07, ~21:35)
- Sobe limpo com o MySQL 4.1: log/sharedserver.out (48 linhas) — conecta
  DARKEDEN, carrega GameServerInfo(game1@9998), GameWorldInfo(DKv2),
  termina com "---------- Start SharedServer ---------". Porta 9977
  ouvindo, 3 threads (uma ~50% CPU busy-loop, normal).
- loginserver continua de pé (9999) junto.


## ✅ LOGINSERVER NO AR (2026-08-07, ~21:30) — bloqueador MySQL resolvido
- MySQL trocado DEFINITIVO para 4.1: container darkeden-mysql agora é
  `vettadock/mysql-old:4.1` (imagem puxada no mesmo dia). 5.7 abandonado
  (cliente 3.23 estaticamente linkado no loginserver só fala protocolo v9).
  NENHUM rebuild dos servidores foi necessário — só o BANCO mudou.
- 🐛 ACHADO E CORRIGIDO: container estava em CRASH LOOP (83 restarts):
  USERINFO.sql (dump 5.7) usava utf8mb4 em 4 pontos (linhas 231/237/255/269)
  → MySQL 4.1 não conhece → import falhava → entrypoint com set -e morria →
  restart:unless-stopped reiniciava → e cada restart re-rodava 00-setup.sql,
  que resetava a senha do elcastle pro formato NOVO → loginserver falhava
  com "Client does not support authentication protocol requested by server".
- FIXES APLICADOS:
  1. `vsserver/docker/../sqls/USERINFO.sql`: utf8mb4 → latin1 (sed)
  2. `vsserver/docker/mysql41-entrypoint.sh`: imports com --force e log
     separado (não matam mais o container; flag só marca se tudo OK);
     fix de senha OLD_PASSWORD + DELETE de usuários anônimos movido pra
     FORA do if (roda SEMPRE — anônimo ''@localhost sombreia elcastle
     em conexões via localhost/127.0.0.1 e daria Access denied)
- Estado validado do banco: elcastle senha 16 bytes (OLD_PASSWORD),
  anônimos removidos, DARKEDEN com 374 tabelas, USERINFO ok.
- ✅ loginserver SOBE: porta 9999 ouvindo, 3 threads vivas. Log
  (log/loginserver.out, 226 linhas): conecta DARKEDEN/USERINFO, query
  WorldDBInfo, DBs WorldID 0 e 1, GameServerInfo(ServerID:1, Nickname:game1,
  TCPPort:9998, UDPPort:9997), ~160 zonas, mundo DKv2. Main thread em
  busy-loop ~60% CPU (comportamento normal desses servidores antigos).
- ✅ setup-mysql.sh (raiz) atualizado: MySQL 4.1 (tarballs + patch)


## Movimentação do projeto
- Repo movido de /home/pmateus/Downloads/vssource → /run/media/pmateus/Dados/vssource
- NADA quebrou: scripts usam REPO_DIR relativo (install.sh/build-server.sh/setup-mysql.sh/wipe-all.sh ok)
- Git íntegro: branch main, HEAD 528964e "ajuste scripts"; mudanças staged (não commitadas):
  libcpsso.cpp+Makefile, MonsterInfo.cpp (fix read char*), gameguard/CSAuth.cpp stub,
  gameserver Makefile (removeu -lsicuuc/-lsicudata, adicionou libCSAuth), loginserver Makefile
  (dependência libLoginServerBilling.a → billing allloginserver)
- .memory-outro-projeto/* deletado (working tree), .memories/ novo (não rastreado)

## Ambiente Docker (persistiu a mudança)
- Imagem darkeden-woody:test presente (436MB) + debian/eol:woody base
- Container darkeden-mysql (mysql:5.7) UP, porta 3306 — banco DARKEDEN/USERINFO
  (setup-mysql validou com retry)

## 🗄️ BANCO RECONFIGURADO (2026-08-07, após mover o projeto)
- Problema: container antigo tinha bind mount ÓRFÃO apontando para o caminho ANTIGO
  (/home/pmateus/Downloads/vssource/.../mysql-data) que não existe mais — a pasta
  mysql-data tinha sido removida ao mover. Container "up" mas dados inacessíveis.
- Solução: docker compose rm -sf mysql (apagou container com mount quebrado) +
  ./setup-mysql.sh (recriou do zero no caminho NOVO).
- ✅ VALIDADO:
  - Mount novo: /run/media/pmateus/Dados/vssource/vsserver/docker/mysql-data → /var/lib/mysql
  - mysql-data/ recriada (DARKEDEN, USERINFO, auto.cnf, certs...)
  - Bancos: DARKEDEN (374 tabelas) + USERINFO (7 tabelas) importados dos SQLs
  - Usuário elcastle/% criado (senha elca110)
  - container darkeden-mysql Up, porta 3306 exposta
- Lição: ao mover o projeto, SEMPRE conferir mounts do compose (docker inspect)
  — o compose usa caminho relativo, mas container antigo guarda o mount absoluto.

## Estado do build (vsserver/build.log, 411 linhas)
- Core COMPLETO (Lpackets/Gpackets/Cpackets/Upackets/Spackets "Nothing to be done")
- server/database OK, gameserver/libs (skill, item, quest, war, couple, mission, ctf, mofus, test)
  todas compiladas — 29 libs .a em vsserver/lib/ (root dono, criadas hoje 12:05)
- libcpsso.a GERADA ✓ (stub real GetCPCookieValue — resolvido)
- bin/ VAZIO — nenhum servidor linkado ainda
- libstlport_gcc.a NÃO está em vsserver/lib (fica dentro da imagem em /usr/local/lib — normal)

## 🐛 BLOQUEADOR ATUAL: link do gameserver falha com 2 erros
1. **GCAttackArmsOK1Handler::execute undefined** — GCAttackArmsOK1.cpp:100 chama o handler,
   mas GCAttackArmsOK1Handler.cpp está em Core/Gpackets/GS/ e compila com -D__GAME_SERVER__
   com corpo vazio (#if __TEST_CLIENT__ / __WINDOWS__ ambos falsos no Linux). A lib
   libGameServerPackets.a TEM GCAttackArmsOK1Handler.o (está no OBJS), então o handler
   deveria estar lá. POR QUE undefined? Investigar: checar se GCAttackArmsOK1Handler.o está
   REALMENTE dentro do .a (ar t) e se a assinatura no .cpp bate com a declaração no .h
   (throw(Error) no .cpp vs .h?). Possível causa: exceção declarada diferente no .h
   (nomes mangled diferentes) OU o .o não foi incluído no .a (ar com caminho relativo).
2. **cppunit com ABI errada**: libGameServerTest.a (testes) linka CppUnit::SourceLine/
   Asserter/TestSuite/TestCase/TextUi::TestRunner com _STL::basic_string (STLport),
   mas o libcppunit.a foi compilado com libstdc++ do gcc-2.95 (std::string nativa).
   configure do cppunit não usa STLport → símbolos incompatíveis.
   ❌ cppunit NÃO é usado em runtime pelo gameserver (só libGameServerTest.a de testes).
   Opções: (a) recompilar cppunit com -I/usr/include/STL (STLport) — pode não compilar;
   (b) não linkar libGameServerTest.a no gameserver (testes não são runtime);
   (c) remover libGameServerTest do LIBS do gameserver Makefile.

## ~~🚨 BLOQUEADOR CRÍTICO (2026-08-07): handshake MySQL 3.23 vs 5.7~~ ✅ RESOLVIDO
- ~~CAUSA RAIZ: imagem woody tem libmysqlclient 3.23.49 (protocolo handshake v9, 2001);
  MySQL 5.7 usa v10 e REJEITA clientes pré-4.1 (mesmo com latin1)~~
- ~~SOLUÇÃO VIÁVEL: compilar libmysqlclient 5.0.x na imagem woody (protocolo v10,
  API C igual; source disponível: mysql-5.0.96.tar.gz HTTP 200) e religar os servidores~~
- ✅ SOLUÇÃO REALMENTE ADOTADA (2026-08-07 ~21:00): trocar o SERVIDOR de banco
  para MySQL 4.1 (vettadock/mysql-old:4.1) — aceita clientes 3.23 com senha
  OLD_PASSWORD (16 bytes). Zero rebuild de servidores. Detalhes no topo do arquivo.

## Próximos passos (milestones)
0. ✅ loginserver UP (9999) — MySQL 4.1 com banco REAL do servidor
1. ✅ sharedserver UP (9977)
2. ✅ gameserver UP (9998) — 155 zonas, conectado no sharedserver
3. Testar login no jogo (cliente) com os 3 de pé — conferir o client-master
   em /home/pmateus/Downloads e o conf do cliente (IP 127.0.0.1)
4. ✅ setup-mysql.sh (raiz) atualizado para o fluxo MySQL 4.1
5. Avaliar treasure HName→EName no runtime se faltar bin

## Lições
- Sempre conferir `wc -c` depois de editar scripts (replace pode truncar para 0 bytes)
- gcc-2.95 build completo ~35-40min; container darkeden-build descartável (--rm + trap)
- Imagem woody = caixa de ferramentas (1x); container = descartável; bins no host via mount
