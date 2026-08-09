# Apêndice — DarkEden Server (vssource)

> 🌐 **English:** [APPENDIX.md](APPENDIX.md) · **Português:** [APPENDIX.pt.md](APPENDIX.pt.md)
>
> Versão detalhada do [README](README.pt.md). Movida para cá para manter o README conciso.
> Todo o conteúdo abaixo foi conferido contra os scripts reais.

---

## 1. Passo a passo completo (do zero)

### Passo 0 — Pré-requisito: nada além do Linux + internet

O único pré-requisito real é um Linux com acesso à internet (para o Docker baixar as imagens
`debian/eol:woody`, `vettadock/mysql-old:4.1` — só na 1ª vez). Todo o resto (gcc-2.95.4,
Lua 4.0.1, STLport, Xerces, cppunit) está **dentro da imagem** ou nos tarballs de
`vsserver/docker/thirdparty/` (100% offline).

### Passo 1 — Preparar o Docker (1ª vez, pede sudo 1x)

```bash
cd vssource
./install.sh docker
```

O que faz: instala `docker.io` + plugin `docker compose` v2 (se faltarem), adiciona seu usuário
ao grupo `docker` (faça logout/login se pedir) e valida `docker info` + `docker compose version`.

> Se já tem Docker instalado, ele só valida e não muda nada.

### Passo 2 — Construir a imagem woody (1ª vez, demora)

```bash
./install.sh image
```

O que faz: baixa `debian/eol:woody` e compila dentro da imagem: gcc-2.95.4 (já vem), Lua 4.0.1,
STLport 4.6.2 + lib, Xerces 2.8, cppunit 1.8.0, patch dos headers (ICE fix). Resultado: imagem
`darkeden-woody:test` — **tudo offline** (tarballs em `thirdparty/`).

### Passo 3 — Pasta de dados (inglês — já no lugar)

```bash
./install.sh            # verifica/avisa sobre vsserver/data/ — a data em inglês já está extraída
```

> A data ativa é a variante **inglês** (extraída de `vsserver/zips/data-ingles.zip` para
> `vsserver/data/`). Ver [Milestone 2](#milestone-2--pasta-de-dados-inglês).

### Passo 4 — Subir o MySQL 4.1 (1ª vez, baixa imagem + importa banco real)

```bash
./install.sh mysql      # ou ./setup-mysql.sh (faz o mesmo)
```

Baixa `vettadock/mysql-old:4.1`, sobe o container `darkeden-mysql`. Na 1ª subida o entrypoint
extrai os tarballs `DARKEDEN.tar.gz`/`USERINFO.tar.gz` (dados reais FRM/MYD/MYI) e importa no
datadir, depois aplica `patch-compat.sql` (IPs locais, nomes de zona, usuário `elcastle`/`elca110`).
Valida os bancos no final.

### Passo 5 — Compilar o servidor (target `all`)

```bash
./build-server.sh
```

Sobe um container da imagem woody montando `vsserver/` em `/src` e roda o make lá dentro.
Binários em `vsserver/bin/` (loginserver, sharedserver, gameserver, ...). Log em
`vsserver/build.log`. **Você não precisa saber nada de docker** — o script faz tudo.

### Passo 6 — (opcional) Rodar de novo / limpar

```bash
./build-server.sh        # recompila (continua de onde parou)
./setup-mysql.sh status  # confere banco
./wipe-all.sh            # limpeza TOTAL (build + banco + imagens)
./wipe-all.sh code       # só artefatos de build
./wipe-all.sh bd         # só banco/docker/imagens
```

---

## 2. Fluxo de um comando → o que acontece por baixo

| Você roda | O script chama internamente |
|---|---|
| `./install.sh` | `01-docker-setup.sh` (se docker faltar) → `02-build-image.sh` (se imagem faltar) → **inline** checagem da `data/` (só aviso) → `mysql.sh start` |
| `./install.sh build` | `./build-server.sh all` |
| `./install.sh wipe` | `./wipe-all.sh` |
| `./build-server.sh` | `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` (target `all`) |
| `./setup-mysql.sh` | `mysql.sh start` (→ `docker compose up -d mysql` + importa banco real: tarballs + patch) |
| `./wipe-all.sh bd` | `docker compose down` + `rm mysql-data` (sudo se preciso) + `docker rmi vettadock/mysql-old:4.1 darkeden-woody:test` |

> ℹ️ O `03-prepare-data.sh` é um helper **manual** — ele só verifica/avisa sobre `data/`. Ele
> **não** é chamado pelo `install.sh` (a checagem lá é inline). Não é necessário hoje:
> `vsserver/data/` já tem a data em inglês. Se um dia quiser (re)extrair um zip de data para
> `vsserver/data/`, faça manualmente (`unzip` + `cp`) — o passo de copiar é propositalmente não automatizado.

---

## 3. Referência rápida de scripts (completa)

### Scripts da raiz (`vssource/`)

| Script | Comando | O que faz | Quando usar |
|---|---|---|---|
| **install.sh** | `./install.sh` | prepara o ambiente: docker → imagem → data → banco (**SEM build** — idempotente) | 1ª vez / garantir ambiente |
| | `./install.sh docker` | só Docker no host (pede sudo 1x) | se o Docker faltar |
| | `./install.sh image` | só constrói `darkeden-woody:test` | se a imagem sumir |
| | `./install.sh mysql` | só sobe o MySQL (baixa + importa) | banco |
| | `./install.sh build` | compila o servidor (= `./build-server.sh all`) | build |
| | `./install.sh wipe` | limpeza total (= `./wipe-all.sh`) | zerar tudo |
| **build-server.sh** | `./build-server.sh` | compila via container woody (target `all`) | sempre que quiser compilar |
| | `./build-server.sh <target>` | compila outro target (`allgameserver`, `allloginserver`, `allsharedserver`, `alltheoneserver`) | avançado |
| **setup-mysql.sh** | `./setup-mysql.sh` | sobe MySQL 4.1 + importa banco real (1ª vez) | banco |
| | `./setup-mysql.sh start` | idem (alias; também `preparar`/`setup`) | banco |
| | `./setup-mysql.sh stop` | para o MySQL | banco |
| | `./setup-mysql.sh status` | mostra se está de pé + bancos | conferir |
| | `./setup-mysql.sh reset` | apaga dados e reimporta do zero (pede sudo) | recriar banco |
| | `./setup-mysql.sh logs` | logs do MySQL | debug |
| | `./setup-mysql.sh sql` | abre o cliente mysql (root sem senha) | consultas |
| **start-servers.sh** | `./start-servers.sh` | sobe loginserver → sharedserver → gameserver em background; verifica MySQL + binários + confs; PIDs em `.server-pids`; logs em `vsserver/log/*.out` | rodar o jogo |
| | `./start-servers.sh -v` | verboso (mostra o log de cada servidor após subir) | debug |
| **stop-servers.sh** | `./stop-servers.sh` | encerra os servidores via `.server-pids` (SIGTERM) | parar |
| | `./stop-servers.sh -9` | força SIGKILL se não saírem | processos travados |
| **wipe-all.sh** | `./wipe-all.sh` | apaga TUDO (build + banco + imagens) | limpeza total |
| | `./wipe-all.sh code` | só artefatos de build (também mata servidores rodando) | rebuild limpo |
| | `./wipe-all.sh bd` | só banco/docker/imagens (pede sudo se preciso) | recriar banco |

### Scripts internos (`vsserver/docker/` — não precisa mexer)

| Script | O que faz |
|---|---|
| `01-docker-setup.sh` | (host, sudo) instala/valida Docker + compose v2 + grupo docker |
| `02-build-image.sh` | (host) constrói `darkeden-woody:test` (100% offline, tarballs em `thirdparty/`) |
| `03-prepare-data.sh` | (helper manual) verifica/avisa sobre `data/` — não é chamado pelo `install.sh`; a data já está no lugar (inglês) |
| `build.sh` | (container) o make em si: symlink mysql + checagem de dependências + patch dos headers + `make -O1` |
| `mysql.sh` | (host) gerencia o MySQL 4.1: start/stop/logs/shell/sql/rm |
| `mysql41-entrypoint.sh` | (container) entrypoint custom do MySQL — extrai os tarballs do banco real + aplica `patch-compat.sql` na 1ª criação do volume |
| `setup-woody-toolchain.sh` | (container) instala Lua/STLport/Xerces/cppunit na imagem (chamado pelo Dockerfile) |
| `patch-woody-headers.sh` | (container) fix ICE do gcc-2.95.4 (idempotente) |
| `Dockerfile.woody` | imagem woody (Debian 3.0 + gcc-2.95.4 + toolchain da época) |
| `docker-compose.yml` | **somente** o serviço `mysql` (4.1) — o build NÃO é serviço do compose |
| `.dockerignore` | exclui `mysql-data/` + logs do contexto do build da imagem |

---

## 4. Milestones

### Milestone 1 — Pré-requisitos do host

Todo o build acontece **dentro do Docker** (imagem `darkeden-woody:test`). No host basta o
**Docker** + plugin **docker compose** (para o MySQL 4.1).

| Componente | Versão | Para quê | Onde fica |
|---|---|---|---|
| Docker | qualquer recente | roda build + MySQL 4.1 | host |
| plugin `docker compose` | 2.x | orquestra o MySQL | host |
| gcc-2.95.4 | Debian woody | compilar código de 2005 | **dentro da imagem** |
| Lua 4.0.1 | da fonte | API Lua 4 (`lua_open(size)`) | **dentro da imagem** |
| STLport 4.6.2 | da fonte | `<hash_map>`, `<slist>`, iostreams | **dentro da imagem** |
| Xerces 2.8 | da fonte | XML de config (`SXml.cpp`) | **dentro da imagem** |
| cppunit 1.8.0 | da fonte | testes (`CppUnit::TextUi::TestRunner`) | **dentro da imagem** |

Setup do Docker no host:

```bash
./install.sh docker      # pede sudo 1x; instala/valida docker + compose + grupo docker
```

O script instala `docker.io` e o plugin `docker-compose-v2` (se faltarem), adiciona seu usuário
ao grupo `docker` (logout/login para valer) e valida `docker info` + `docker compose version`.

### Milestone 2 — Pasta de dados (inglês)

O servidor lê os dados de `data/` relativo ao `HomePath` dos confs (que é `.`). O repo traz
**dois zips** com as duas variantes de data (em `vsserver/zips/`):

| Arquivo | Conteúdo | Observação |
|---|---|---|
| `data-ingles.zip` (585 arquivos) | bins de NPCs **em inglês**, mapas `.smp/.ssi`, `EventGQuest.xml`, `lua/` | **Usada** (bate com o `EName` do banco) |
| `data-coreano.zip` (629 arquivos) | bins de NPCs com nome **coreano** EUC-KR | Alternativa — só os nomes dos `.bin` mudam |

**Decidido:** `vsserver/data/` contém a variante **inglês** extraída (581 arquivos, **gitignorada**).
O zip coreano fica em `vsserver/zips/` como alternativa, caso um dia precise.

> ℹ️ **Treasure/drops:** com data em inglês + `EName`s em inglês no banco, nenhum `cannot load` /
> treasure vazio foi observado nos logs. Se uma configuração futura mostrar drops vazios para
> muitos monstros (`HName` coreano montando um bin que não existe), o fallback é um fix
> `HName → EName` em `MonsterInfo.cpp` — **preferência: não mexer no código salvo necessidade**.

### Milestone 3 — Compilar o servidor (build via Docker — PRINCIPAL)

O build roda **dentro de um container** (imagem `darkeden-woody:test`, base Debian 3.0 com
gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0). O código-fonte é
**montado** (bind mount) de `vsserver/` para `/src` — nada é instalado no host. Os binários
saem em `vsserver/bin/`.

```bash
# 1. (uma vez) constrói a imagem woody — baixa debian/eol:woody + compila a toolchain
./install.sh image

# 2. compila o servidor (target all por padrão — todos os binários)
./build-server.sh
./build-server.sh allgameserver      # só o gameserver (avançado)
```

Log completo em `vsserver/build.log`. Binários em `vsserver/bin/`.
O build usa `-O1` (necessário: sem ele o ICE do gcc-2.95.4 no STLport volta) e aplica
`patch-woody-headers.sh` automaticamente.

### Milestone 4 — Subir o MySQL 4.1 (Docker) e importar o banco real

```bash
./setup-mysql.sh            # baixa vettadock/mysql-old:4.1 + sobe + importa (1ª vez)
```

- Container: `darkeden-mysql` (imagem `vettadock/mysql-old:4.1`)
- Porta **3306 exposta** no host (os servidores rodam no host e conectam em `127.0.0.1:3306`)
- Dados persistidos em `vsserver/docker/mysql-data/`

O compose monta `vsserver/sqls/` em `/docker-entrypoint-initdb.d` — na **primeira** inicialização
do volume, o entrypoint custom (`mysql41-entrypoint.sh`) importa o banco REAL do servidor.
**NÃO são dumps .sql** — os dumps do opendarkeden têm schema diferente; a fonte é sempre os
tarballs:

1. Extrai `DARKEDEN.tar.gz` → banco `DARKEDEN` (dados MyISAM FRM/MYD/MYI, 400+ tabelas)
2. Extrai `USERINFO.tar.gz` → banco `USERINFO`
3. Aplica `patch-compat.sql` → IPs locais (127.0.0.1), nomes de zona exatos, usuário
   `elcastle`/`elca110` (senha formato OLD_PASSWORD, exigido pelo cliente 3.23 dos servidores)

> ⚠️ A importação **só roda na 1ª vez** que o volume `mysql-data/` for criado. Para reimportar
> do zero: `./setup-mysql.sh reset` (apaga container + `mysql-data/` e sobe de novo).

Verificação:

```bash
./setup-mysql.sh status     # mostra se está de pé + bancos
./setup-mysql.sh sql        # abre o cliente mysql (root sem senha)
# dentro do mysql:
SHOW DATABASES;             # DARKEDEN e USERINFO
USE DARKEDEN; SHOW TABLES;  # 400+ tabelas (dados reais do servidor)
SELECT COUNT(*) FROM WorldDBInfo;  # deve ter linha com Host=127.0.0.1
```

> **Credenciais dos servidores (conf)**: `elcastle` / `elca110` nos bancos `DARKEDEN` e
> `USERINFO` — criadas pelo entrypoint (GRANT + senha OLD_PASSWORD).
> O conf do loginserver também tem `DB_VERSION : 4`, que faz o handler de login validar a senha
> com `OLD_PASSWORD()` (16 hex) em vez de `PASSWORD()` (41 chars).

### Milestone 5 — Configurar os confs

Todos os confs ficam em `vsserver/src/conf/`. ⚠️ Os servidores são executados **da raiz do
vsserver** (`HomePath: .`), então os confs são referenciados como `-f src/conf/xxx.conf`. Abaixo
estão as **configurações-chave** de cada um (os arquivos têm mais opções — IDs de servidor,
billing, logs, etc.).

#### `gameserver.conf` (porta 9998)

```ini
User : excel96
HomePath : .              # relativo à raiz do vsserver
TCPPort : 9998
LoginServerIP: 127.0.0.1
LoginServerUDPPort : 9996
GameServerUDPPort : 9997
SharedServerIP : 127.0.0.1
SharedServerPort : 9977
ServerID : 0              # ⚠️ NÃO é o ServerID da tabela — é o GroupID (0 = grupo padrão)
IsNetMarble : 0
DB_HOST : 127.0.0.1       # MySQL docker no host
DB_PORT : 3306
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
UI_DB_HOST : 127.0.0.1
UI_DB_PORT : 3306
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
```

#### `loginserver.conf` (porta 9999)

```ini
User : excel96
HomePath : .
LoginServerPort : 9999
LoginServerUDPPort : 9996
LoginServerBasePort : 9900
LoginServerBaseUDPPort : 9800
GameServerUDPPort : 9997
DB_HOST : 127.0.0.1
DB_PORT : 3306
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
DB_VERSION : 4           # validação de login com OLD_PASSWORD() (necessário para logar)
UI_DB_HOST : 127.0.0.1
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
DIST_DB_HOST : 127.0.0.1
DIST_DB_DB : DARKEDEN
DIST_DB_USER : elcastle
DIST_DB_PASSWORD : elca110
LoginServerID : 0
IsNetMarble : 0
```

#### `sharedserver.conf` (porta 9977)

```ini
User : excel96
HomePath : .
TCPPort : 9977
DB_HOST : 127.0.0.1
DB_PORT : 3306
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
UI_DB_HOST : 127.0.0.1
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
DIST_DB_HOST : 127.0.0.1
DIST_DB_DB : DARKEDEN
DIST_DB_USER : elcastle
DIST_DB_PASSWORD : elca110
```

#### `updateserver.conf` ⚠️ (porta 3000)

> ℹ️ **Não usado neste projeto.** O updateserver não é necessário para jogar (loginserver/
> sharedserver/gameserver bastam). Ele só serve o **auto-update do cliente** (`PatchDir`,
> `INFOURL`, `GUILDURL`). **Não** é iniciado pelo `start-servers.sh`. Abaixo está o conf original,
> só para referência — se um dia for ativado, ajustar:

```ini
HomeDir : /darkeden       # → deve apontar para a raiz do vsserver (ex.: .)
PatchDir : data/patch     # → verificar se existe vsserver/data/patch (ou criar)
Port : 3000
KeyFile : key357.dat      # → verificar existência (o cliente de update usa)
KeyVersion : 3000
```

### Milestone 6 — Subir os servidores

Ordem e portas:

| Servidor | Binário | Conf | Porta TCP | Depende de |
|---|---|---|---|---|
| loginserver | `vsserver/bin/loginserver` | `src/conf/loginserver.conf` | 9999 | MySQL |
| sharedserver | `vsserver/bin/sharedserver` | `src/conf/sharedserver.conf` | 9977 | MySQL |
| gameserver | `vsserver/bin/gameserver` | `src/conf/gameserver.conf` | 9998 | MySQL + sharedserver + `data/` |

Subir com os scripts fornecidos (da raiz do projeto):

```bash
./start-servers.sh          # verifica MySQL + binários + confs, sobe os 3 em background
./start-servers.sh -v       # verboso
./stop-servers.sh           # encerra (SIGTERM)
./stop-servers.sh -9        # força (SIGKILL)
```

- PIDs salvos em `.server-pids`
- Logs em `vsserver/log/loginserver.out`, `.../sharedserver.out`, `.../gameserver.out`
- `start-servers.sh` mata instâncias antigas primeiro (evita "address already in use")

Ou subir manualmente (para debug), cada um em seu terminal, **da raiz do vsserver**:

```bash
cd vsserver   # raiz do server (HomePath = .)

# 1º: MySQL precisa estar de pé (Milestone 4)
docker ps | grep darkeden-mysql

# 2º: subir cada servidor em seu terminal
./bin/loginserver  -f src/conf/loginserver.conf
./bin/sharedserver -f src/conf/sharedserver.conf
./bin/gameserver   -f src/conf/gameserver.conf
```

Sinais de sucesso:
- loginserver: registra o servidor no banco e fica em loop
- gameserver: `>>> ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY.` + `connection to sharedserver established`

### Milestone 7 — updateserver/update (opcional, NÃO usado)

Os binários `vsserver/bin/updateserver` e `vsserver/bin/update` são compilados como parte do
`./build-server.sh all`, mas o updateserver **não é usado neste projeto** (não é iniciado pelo
`start-servers.sh`, confs ficam no valor original). Ele não é necessário para o servidor de jogo
funcionar — apenas para distribuir auto-updates ao cliente. Tratar como extra/não usado.

### Milestone 8 — Conexão do cliente

O cliente (Windows/DirectX) deve apontar para o IP da máquina do servidor:

| Serviço | Porta |
|---|---|
| loginserver (TCP) | 9999 |
| gameserver (UDP/TCP) | 9998/9997 |
| sharedserver | 9977 |
| updateserver | 3000 |

> ⚠️ Se o cliente estiver em outra máquina, o IP do gameserver no **banco** deve ser o IP da LAN,
> não 127.0.0.1:
> ```sql
> UPDATE DARKEDEN.GameServerInfo SET IP='<IP-da-LAN>';  -- ver: ip -4 addr | grep inet
> ```
> `WorldDBInfo.Host` continua 127.0.0.1 (uso interno servidor→MySQL). Os detalhes dependem do
> pacote de dados do cliente (IPs, versão do patch).

---

## 5. Manutenção e troubleshooting

### Comandos úteis

```bash
./install.sh                # garante o ambiente (docker + imagem + banco — SEM build)
./build-server.sh           # compila (target all)
./setup-mysql.sh            # banco
./start-servers.sh          # sobe os servidores em background
./stop-servers.sh           # encerra os servidores
./wipe-all.sh               # limpeza total (build + banco + imagem)
./wipe-all.sh code          # só artefatos de build
./wipe-all.sh bd            # só banco/docker
```

### Problemas comuns

| Sintoma | Causa provável / Solução |
|---|---|
| `docker: command not found` | Docker ausente — rode `./install.sh docker` (pede sudo 1x) |
| `ERRO: imagem darkeden-woody:test não existe` | rode `./install.sh image` (constrói a imagem woody) |
| `Permission denied` ao apagar `bin/`/`lib/` | pastas criadas por root no container — `./wipe-all.sh code` apaga e o build recria com seu usuário |
| ICE do gcc-2.95.4 no STLport (`_threads.h:579`) | o build já aplica `patch-woody-headers.sh` + `-O1` automaticamente (não é problema seu) |
| `cannot find -lnsl` | ✅ já corrigido — `-lnsl` removido dos Makefiles |
| Servidor morre ao subir | ver `vsserver/log/*.out`; causas comuns: MySQL parado, `data/` incompleto, conf com IP errado |
| `invalid packet id(422)` | loginserver sem `GMServerInfo` (✅ já ok neste repo — revalidar após build) |
| `cannot load` / treasure vazio no boot | ⚠️ questão do `HName` coreano vs bins em inglês — ver [Milestone 2](#milestone-2--pasta-de-dados-inglês) |
| MySQL não reimporta banco | importação só na 1ª criação do volume: `./setup-mysql.sh reset` |

### Ordem de limpeza total

```bash
./wipe-all.sh        # apaga tudo (build + banco + imagem)
./install.sh         # recomeça o ambiente (docker + imagem + banco)
./build-server.sh    # compila de novo
```

---

## 6. Status atual

| Item | Status |
|---|---|
| Imagem `darkeden-woody:test` (Debian 3.0 + gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0) | ✅ construída (436MB) |
| Toolchain woody 100% offline (tarballs em `vsserver/docker/thirdparty/`) | ✅ presentes |
| Pipeline: `install.sh` + `build-server.sh` + `setup-mysql.sh` + `wipe-all.sh` | ✅ criados |
| Código-fonte compilando (target `all`) | ✅ compilado — todos os binários em `vsserver/bin/` (gameserver, loginserver, sharedserver, updateserver, update) |
| `start-servers.sh` / `stop-servers.sh` | ✅ criados na raiz do projeto |
| MySQL 4.1 com banco real | ✅ `DARKEDEN` / `USERINFO` importados (tarballs + patch) |
| Pasta de dados | ✅ variante inglês extraída (581 arquivos, gitignorada) |
| Servidores rodando | ✅ loginserver (9999), sharedserver (9977), gameserver (9998) — 157 zonas carregadas |
| updateserver | ⏸️ não usado (opcional; não é iniciado pelo `start-servers.sh`) |

---

## 7. Como subir tudo (cola)

```bash
./install.sh            # ambiente: docker + imagem + data + banco (SEM build)
./build-server.sh       # compila uma vez (ou sempre que mudar o código)
./setup-mysql.sh status # confirma os bancos
./start-servers.sh      # loginserver → sharedserver → gameserver
./stop-servers.sh       # encerra
./wipe-all.sh           # limpeza total (build + banco + imagens)
```

*Sugestões e correções são bem-vindas — abra uma issue ou um PR. Veja o [README](README.pt.md).*
