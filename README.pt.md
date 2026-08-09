# DarkEden Server (vssource)

> 🌐 **English:** [README.md](README.md) · **Português:** [README.pt.md](README.pt.md)

Código-fonte do servidor de **DarkEden** (~2005). Este repositório contém o **server-master**
completo (`vsserver/`): código-fonte (`src/`), dados do servidor (`data/`), dumps do banco
(`sqls/`) e infraestrutura Docker.

> 🎯 **Fluxo oficial: ambiente WOODY** (Debian 3.0 + gcc-2.95.4 + STLport 4.6.2 + xerces 2.8
> + cppunit 1.8.0) rodando **dentro do Docker**. No host basta Docker. Nada de build no host.

---

## 🚀 GUIA RÁPIDO (para o leigo — usuário novo)

### Pré-requisito
- Linux com internet (só para o Docker baixar as imagens na 1ª vez)

### Passo 1 — Docker no host (1ª vez, pede sudo)

```bash
cd vssource
./install.sh docker
```

- Instala `docker.io` + plugin compose se faltarem
- Adiciona o usuário ao grupo `docker` → **fazer logout/login** se pedir

### Passo 2 — Imagem de build woody (1ª vez, demora ~10-40min)

```bash
./install.sh image
```

- Baixa `debian/eol:woody` + compila dentro da imagem: Lua 4.0.1, STLport 4.6.2 + lib,
  Xerces 2.8, cppunit 1.8.0, patch dos headers (ICE fix). Tudo offline (tarballs em
  `vsserver/docker/thirdparty/`).
- Resultado: imagem `darkeden-woody:test` (436MB)

### Passo 3 — Banco MySQL 4.1 (1ª vez, baixa imagem + importa banco real)

```bash
./install.sh mysql
```

- Baixa `vettadock/mysql-old:4.1`, sobe o container `darkeden-mysql` (porta 3306)
- Na 1ª subida o entrypoint extrai os tarballs `DARKEDEN.tar.gz` + `USERINFO.tar.gz`
  (dados reais FRM/MYD/MYI do servidor) e importa no datadir
- Depois aplica `patch-compat.sql` (IPs locais, nomes de zona, usuário `elcastle`/`elca110`)

### Passo 4 — Compilar o servidor ⚠️ (demora ~35-40min na 1ª vez)

```bash
./build-server.sh        # target all (loginserver, sharedserver, gameserver, ...)
# ou: ./build-server.sh allgameserver / allloginserver / ...  (avançado)
```

- Roda o make dentro do container woody (gcc-2.95.4)
- Binários em `vsserver/bin/`, log completo em `vsserver/build.log`

### Passo 5 — Verificar / gerenciar

```bash
./setup-mysql.sh status   # confere se o banco está de pé + bancos
./wipe-all.sh             # limpeza TOTAL (build + banco + imagens)
./wipe-all.sh code        # só artefatos de build
./wipe-all.sh bd          # só banco/docker/imagens
```

> 💡 **`./install.sh` (sem argumento) prepara TUDO exceto o build**: docker + imagem + banco.
> O build é sempre feito por `./build-server.sh`, para você ter controle de quando compilar.

---

## 📋 Estrutura do repo

```
vssource/
├── install.sh             # prepara o ambiente: docker + imagem + banco (SEM build)
├── build-server.sh        # compila via container woody (rodado de fora do docker)
├── setup-mysql.sh         # prepara o MySQL 4.1 (baixa imagem + importa banco real)
├── wipe-all.sh            # apaga build e/ou banco/docker/imagem
├── vsserver/              # = server-master
│   ├── src/               # código-fonte (Core/ = ativo; OLDCore/ = backup/paralelo)
│   ├── src/conf/          # gameserver.conf, loginserver.conf, sharedserver.conf, updateserver.conf
│   ├── data/              # ⚠️ data ativa do servidor (ver Milestone 2)
│   │   ├── data-ingles/   #   data em inglês (581 arquivos)
│   │   └── data - coreano/#   data em coreano (628 arquivos)
│   ├── sqls/              # banco real do servidor (DARKEDEN.tar.gz, USERINFO.tar.gz) + patch-compat.sql
│   ├── docker/            # Dockerfile.woody + scripts internos + thirdparty/
│   └── (bin/ lib/ log/ temp/ são criados pelo build)
```

### Scripts (raiz do projeto)

| Script | O que faz | Quando usar |
|---|---|---|
| `./install.sh` | **prepara o ambiente**: docker + imagem woody + banco (idempotente — pode rodar de novo; **NÃO compila**) | 1ª vez (ou sempre que quiser "garantir o ambiente") |
| `./install.sh docker` | só o Docker no host (pede sudo 1x) | se o Docker faltar |
| `./install.sh image` | só constrói a imagem `darkeden-woody:test` | se a imagem sumir |
| `./install.sh mysql` | só sobe o MySQL 4.1 (baixa imagem + importa banco real) | banco |
| `./install.sh build` | compila o servidor (= `./build-server.sh`) | build |
| `./install.sh wipe` | limpeza total (= `./wipe-all.sh`) | zerar tudo |
| `./build-server.sh` | compila o servidor via container woody (target `all` por padrão) | **sempre que quiser compilar** |
| `./build-server.sh <target>` | compila outro target (`allgameserver`, `allloginserver`, ...) | avançado |
| `./setup-mysql.sh` | baixa imagem vettadock/mysql-old:4.1 + sobe + importa banco real (1ª vez) | banco |
| `./setup-mysql.sh stop/reset/logs/sql` | gerencia o banco | avançado |
| `./wipe-all.sh` | apaga TUDO (build + banco + imagem) | limpeza total |
| `./wipe-all.sh code` | apaga só artefatos de build | rebuild limpo |
| `./wipe-all.sh bd` | apaga só banco/docker/imagem | recriar banco |

### Scripts internos (`vsserver/docker/` — não precisa mexer)

| Script | O que faz |
|---|---|
| `01-docker-setup.sh` | (host, sudo) instala/valida Docker + plugin compose + grupo docker |
| `02-build-image.sh` | (host) constrói `darkeden-woody:test` (100% offline, tarballs em `thirdparty/`) |
| `03-prepare-data.sh` | ⚠️ prepara `data/` — **decisão em aberto** (ver Milestone 2) |
| `build.sh` | (container) make em si, roda dentro do container woody |
| `mysql.sh` | (host) gerencia o MySQL 4.1: start/stop/logs/shell/sql/rm |
| `setup-woody-toolchain.sh` | (container) instala Lua/STLport/Xerces/cppunit na imagem (Dockerfile) |
| `patch-woody-headers.sh` | (container) fix ICE do gcc-2.95.4 (idempotente) |
| `Dockerfile.woody` | imagem woody (Debian 3.0 + gcc-2.95.4 + toolchain da época) |
| `docker-compose.yml` | só o serviço `mysql` (4.1) — o build NÃO é serviço do compose |

### Fluxo de um comando → o que acontece por baixo

| Você roda | O script chama internamente |
|---|---|
| `./install.sh` | `01-docker-setup.sh` → `02-build-image.sh` → `03-prepare-data.sh` → `mysql.sh start` |
| `./build-server.sh` | `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` |
| `./setup-mysql.sh` | `mysql.sh start` (→ `docker compose up -d mysql` + importa banco real: tarballs + patch) |
| `./wipe-all.sh bd` | `docker compose down` + `rm mysql-data` (sudo se preciso) + `docker rmi vettadock/mysql-old:4.1 darkeden-woody:test` |

---

## 📋 PASSO A PASSO COMPLETO (do zero)

Esta seção cobre **TUDO** o que precisa ser feito, usando **somente os scripts do projeto**.
Siga na ordem. (Equivale aos Milestones 1–4, condensados.)

### Passo 0 — Pré-requisito: nada além do Linux + internet

O único pré-requisito real é um Linux com acesso à internet (para o Docker baixar as imagens
`debian/eol:woody`, `vettadock/mysql-old:4.1` — só na 1ª vez). Todo o resto (compilador gcc-2.95.4, Lua
4.0.1, STLport, Xerces, cppunit) está **dentro da imagem** ou nos tarballs de
`vsserver/docker/thirdparty/` (100% offline).

### Passo 1 — Preparar o Docker (1ª vez, pede sudo 1x)

```bash
cd vssource
./install.sh docker
```

O que faz: instala `docker.io` + plugin `docker compose` (se faltarem), adiciona seu usuário ao
grupo `docker` (faça logout/login se pedir) e valida `docker info`.

> Se já tem Docker instalado, ele só valida e não muda nada.

### Passo 2 — Construir a imagem de build woody (1ª vez, demora)

```bash
./install.sh image
```

O que faz: baixa `debian/eol:woody` e compila dentro da imagem: gcc-2.95.4 (já vem), Lua 4.0.1,
STLport 4.6.2 + lib, Xerces 2.8, cppunit 1.8.0, patch dos headers (ICE fix). Resultado: imagem
`darkeden-woody:test` — **tudo offline** (tarballs em `thirdparty/`).

### Passo 3 — Preparar a pasta de dados (⚠️ em aberto)

```bash
./install.sh            # a etapa 3/5 verifica/avisa sobre vsserver/data/
```

> ⚠️ **Decisão em aberto**: qual data usar (inglês vs coreano). Enquanto não decidimos, o
> `install.sh` apenas avisa — ver [Milestone 2](#milestone-2--preparar-a-pasta-data--em-aberto).

### Passo 4 — Subir o banco MySQL 4.1 (1ª vez, baixa imagem + importa banco real)

```bash
./install.sh mysql      # ou ./setup-mysql.sh (faz o mesmo)
```

O que faz: baixa `vettadock/mysql-old:4.1`, sobe o container `darkeden-mysql`. Na 1ª subida o
entrypoint extrai os tarballs `DARKEDEN.tar.gz`/`USERINFO.tar.gz` (banco real FRM/MYD/MYI) e
importa no datadir, depois aplica `patch-compat.sql` (IPs locais, nomes de zona, usuário
elcastle). Valida os bancos no final.

### Passo 5 — Compilar o servidor (target `all`)

```bash
./build-server.sh
```

O que faz: sobe um container da imagem woody montando `vsserver/` em `/src` e roda o make lá
dentro. Binários em `vsserver/bin/` (loginserver, sharedserver, gameserver, ...). Log em
`vsserver/build.log`. **Você não precisa saber nada de docker** — o script faz tudo.

### Passo 6 — (opcional) Rodar de novo / limpar

```bash
./build-server.sh       # recompila (continua de onde parou)
./setup-mysql.sh status # confere banco
./wipe-all.sh           # limpeza TOTAL (build + banco + imagens)
./wipe-all.sh code      # só artefatos de build
./wipe-all.sh bd        # só banco/docker/imagens
```

---

## 📊 Referência rápida de scripts e comandos

### Scripts da raiz (`vssource/`)

| Script | Comando | O que faz | Quando usar |
|---|---|---|---|
| **install.sh** | `./install.sh` | prepara o ambiente: docker → imagem → data → banco (**SEM build** — idempotente) | 1ª vez / garantir ambiente |
| | `./install.sh docker` | só Docker no host (pede sudo 1x) | se o Docker faltar |
| | `./install.sh image` | só constrói `darkeden-woody:test` | se a imagem sumir |
| | `./install.sh mysql` | só sobe o MySQL (baixa + importa) | banco |
| | `./install.sh build` | compila o servidor (= `./build-server.sh`) | build |
| | `./install.sh wipe` | limpeza total (= `./wipe-all.sh`) | zerar tudo |
| **build-server.sh** | `./build-server.sh` | compila via container woody (target `all`) | sempre que quiser compilar |
| | `./build-server.sh <target>` | compila outro target (`allgameserver`, `allloginserver`, ...) | avançado |
| **setup-mysql.sh** | `./setup-mysql.sh` | sobe MySQL 4.1 + importa banco real (1ª vez) | banco |
| | `./setup-mysql.sh start` | idem (alias) | banco |
| | `./setup-mysql.sh stop` | para o MySQL | banco |
| | `./setup-mysql.sh status` | mostra se está de pé + bancos | conferir |
| | `./setup-mysql.sh reset` | apaga dados e reimporta do zero (pede sudo) | recriar banco |
| | `./setup-mysql.sh logs` | logs do MySQL | debug |
| | `./setup-mysql.sh sql` | abre o cliente mysql (root sem senha) | consultas |
| **wipe-all.sh** | `./wipe-all.sh` | apaga TUDO (build + banco + imagens) | limpeza total |
| | `./wipe-all.sh code` | só artefatos de build | rebuild limpo |
| | `./wipe-all.sh bd` | só banco/docker/imagens (pede sudo se preciso) | recriar banco |

### Scripts internos (`vsserver/docker/` — não precisa mexer)

| Script | O que faz |
|---|---|
| `01-docker-setup.sh` | (host, sudo) instala/valida Docker + compose + grupo docker |
| `02-build-image.sh` | (host) constrói `darkeden-woody:test` (offline) |
| `03-prepare-data.sh` | ⚠️ prepara `data/` — em aberto |
| `build.sh` | (container) make em si (symlink mysql + patch headers + make -O1) |
| `mysql.sh` | (host) start/stop/logs/shell/sql/rm do MySQL 4.1 |
| `setup-woody-toolchain.sh` | (container) instala Lua/STLport/Xerces/cppunit na imagem |
| `patch-woody-headers.sh` | (container) fix ICE do gcc-2.95.4 |
| `Dockerfile.woody` | imagem woody (Debian 3.0 + gcc-2.95.4 + toolchain) |
| `docker-compose.yml` | serviços `mysql` (4.1) + `build` (woody) |

### Fluxo de um comando → o que acontece por baixo

| Você roda | O script chama internamente |
|---|---|
| `./install.sh` | `01-docker-setup.sh` → `02-build-image.sh` → `03-prepare-data.sh` → `mysql.sh start` |
| `./install.sh build` | `./build-server.sh` → `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` |
| `./build-server.sh` | `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` |
| `./setup-mysql.sh` | `mysql.sh start` (→ `docker compose up -d mysql` + importa banco real: tarballs + patch) |
| `./wipe-all.sh bd` | `docker compose down` + `rm mysql-data` (sudo se preciso) + `docker rmi vettadock/mysql-old:4.1 darkeden-woody:test` |

---

## Milestone 1 — Pré-requisitos do host

### 1.1. O que é necessário (NO HOST — nada de build no host!)

Todo o build acontece **dentro do Docker** (imagem `darkeden-woody:test`). No host basta ter o
**Docker** + plugin **docker compose** (para o MySQL 4.1).

| Componente | Versão | Para quê | Onde fica |
|---|---|---|---|
| Docker | qualquer recente | roda build + MySQL 4.1 | host |
| plugin `docker compose` | 2.x | orquestra o MySQL | host |
| gcc-2.95.4 | Debian woody | compilar código de 2005 | **dentro da imagem** |
| Lua 4.0.1 | da fonte | API Lua 4 (`lua_open(size)`) | **dentro da imagem** |
| STLport 4.6.2 | da fonte | `<hash_map>`, `<slist>`, `iostreams` | **dentro da imagem** |
| Xerces 2.8 | da fonte | XML de config (`SXml.cpp`) | **dentro da imagem** |
| cppunit 1.8.0 | da fonte | testes (`CppUnit::TextUi::TestRunner`) | **dentro da imagem** |

### 1.2. Setup do Docker (host)

```bash
./install.sh docker      # pede sudo 1x; instala/valida docker + compose + grupo docker
```

O script: instala `docker.io` e o plugin `docker-compose-v2` (se faltarem), adiciona seu usuário
ao grupo `docker` (logout/login para valer) e valida `docker info` + `docker compose version`.

---

## Milestone 2 — Preparar a pasta `data/` ⚠️ (EM ABERTO)

O servidor lê os dados de `data/` relativo ao `HomePath` dos confs (que será `.`). Existem duas
versões de data no repo:

| Pasta | Conteúdo | Observação |
|---|---|---|
| `data/data-ingles/data/` | 581 arquivos (bins de NPCs **em inglês**, mapas `.smp/.ssi`, `EventGQuest.xml`, `lua/`) | **Recomendada** (bate com o `EName` do banco) |
| `data/data - coreano/data/` | 628 arquivos (bins de NPCs com nome **coreano** EUC-KR) | Só os nomes dos `.bin` mudam (267 bins a mais) |

> ⚠️ **DECISÃO EM ABERTO (2026-08-07):** qual data usar (inglês vs coreano) e quando/como copiar
> para `vsserver/data/`. Enquanto não decidirmos, o `03-prepare-data.sh` apenas verifica e avisa.
> **Decidimos quando chegarmos nessa parte** — ver seção [Decisões em aberto](#-decisões-em-aberto--pontos-a-avaliar-na-hora-de-subir).

> ⚠️ **Treasure/drops (decisão em aberto):** no outro projeto alguns monstros tinham `HName`
> coreano no banco e o servidor montava o nome do arquivo de treasure por ele — com data em
> inglês isso gerava bins "não encontrados" (drop zerado). Lá foi aplicado um fix no código
> (fallback `HName → EName` em `MonsterInfo.cpp`). **Aqui a preferência é NÃO mexer no código**
> — avaliar no momento de subir: se o log mostrar `cannot load`/treasure vazio para muitos
> monstros, aplicar o mesmo fallback (ou copiar os bins coreanos que faltam).

---

## Milestone 3 — Compilar o servidor (build via Docker — PRINCIPAL)

### 3.1. Como funciona

O build roda **dentro de um container** (imagem `darkeden-woody:test`, base Debian 3.0 com
gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0). O código-fonte é
**montado** (bind mount) de `vsserver/src` para `/src` — nada é instalado no host. Os binários
saem em `vsserver/bin/`.

### 3.2. Passos

```bash
# 1. (uma vez) constrói a imagem woody — baixa debian/eol:woody + compila a toolchain
./install.sh image

# 2. compila o servidor (target all por padrão — todos os binários)
./build-server.sh
./build-server.sh allgameserver      # só o gameserver (avançado)
```

Log completo em `vsserver/build.log`. Binários em `vsserver/bin/`.

---

## Milestone 4 — Subir o MySQL 4.1 (Docker) e importar o banco real

### 4.1. Subir

```bash
./setup-mysql.sh            # baixa a imagem vettadock/mysql-old:4.1 + sobe + importa banco real (1ª vez)
```

- Container: `darkeden-mysql` (image `vettadock/mysql-old:4.1`)
- Porta **3306 exposta** no host (os servidores rodam no host e conectam em `127.0.0.1:3306`)
- Dados persistidos em `vsserver/docker/mysql-data/`

### 4.2. Importação do banco real (1ª subida)

O compose monta `vsserver/sqls/` em `/docker-entrypoint-initdb.d` — na **primeira**
inicialização do volume, o entrypoint custom (`mysql41-entrypoint.sh`) importa o banco REAL
do servidor. **NÃO são dumps .sql** — os dumps do opendarkeden têm schema diferente deste
código; a fonte é sempre os tarballs:

1. Extrai `DARKEDEN.tar.gz` → banco `DARKEDEN` (dados MyISAM FRM/MYD/MYI)
2. Extrai `USERINFO.tar.gz` → banco `USERINFO`
3. Aplica `patch-compat.sql` → IPs locais (127.0.0.1), nomes de zona exatos, usuário
   `elcastle`/`elca110` (senha formato OLD_PASSWORD, exigido pelo cliente 3.23 dos servidores)

> ⚠️ A importação **só roda na 1ª vez** que o volume `mysql-data/` for criado. Para reimportar
> do zero: `./setup-mysql.sh reset` (apaga container + `mysql-data/` e sobe de novo).

### 4.3. Verificação

```bash
./setup-mysql.sh status     # mostra se está de pé + bancos
./setup-mysql.sh sql        # abre o cliente mysql (root sem senha)
# dentro do mysql:
SHOW DATABASES;             # DARKEDEN e USERINFO
USE DARKEDEN; SHOW TABLES;  # 411 tabelas (dados reais do servidor)
SELECT COUNT(*) FROM WorldDBInfo;  # deve ter linha com Host=127.0.0.1
```

> **Credenciais dos servidores (conf)**: `elcastle` / `elca110` nos bancos `DARKEDEN` e
> `USERINFO` — criadas pelo entrypoint (GRANT + senha OLD_PASSWORD).

### 4.4. ⚠️ `sqls/DARKEDEN.tar.gz` e `sqls/USERINFO.tar.gz`

Estes arquivos contêm os **dados binários MyISAM** (`.frm`, `.MYD`, `.MYI`) reais do servidor
original (vindos de uma instalação MySQL 5.7, formato compatível com o 4.1) — são a **fonte
oficial do banco**, extraídos e importados pelo entrypoint na 1ª subida (ver 4.2). Não são
dumps SQL.

---

## Milestone 5 — Configurar os confs

Todos os confs ficam em `vsserver/src/conf/` (⚠️ atenção: os servidores são executados **da raiz
do vsserver** — `HomePath: .` — então confs são referenciados como `-f src/conf/xxx.conf` ou
copiados; ver Milestone 6).

### 5.1. `gameserver.conf` (porta 9998)

```ini
User : excel96
HomePath : .              # relativo à raiz do vsserver
TCPPort : 9998
LoginServerIP: 127.0.0.1
SharedServerIP : 127.0.0.1
ServerID : 0              # ⚠️ NÃO é o ServerID da tabela — é o GroupID (0 = grupo padrão)
IsNetMarble : 0
DB_HOST : 127.0.0.1       # MySQL docker no host
DB_PORT : 3306
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
UI_DB_HOST : 127.0.0.1
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
```

### 5.2. `loginserver.conf` (porta 9999)

```ini
User : excel96
HomePath : .
LoginServerPort : 9999
LoginServerUDPPort : 9996
DB_HOST : 127.0.0.1
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
UI_DB_HOST : 127.0.0.1
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
```

### 5.3. `sharedserver.conf` (porta 9977)

```ini
User : excel96
HomePath : .
TCPPort : 9977
DB_HOST : 127.0.0.1
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
UI_DB_HOST : 127.0.0.1
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
```

### 5.4. `updateserver.conf` ⚠️ (porta 3000)

```ini
# ⚠️ Ajustar para este projeto:
HomeDir : /darkeden       # → deve apontar para a raiz do vsserver (ex.: .)
PatchDir : data/patch     # → verificar se existe vsserver/data/patch (ou criar)
Port : 3000
KeyFile : key357.dat      # → verificar existência (o cliente de update usa)
KeyVersion : 3000
```

> ⚠️ O updateserver não é necessário para jogar (loginserver/sharedserver/gameserver bastam).
> Ele só serve para o **auto-update do cliente** (`PatchDir`, `INFOURL`, `GUILDURL`). Ajustar na
> Milestone 7 se for usá-lo.

---

## Milestone 6 — Subir os servidores

### 6.1. Ordem e portas

| Servidor | Binário | Conf | Porta TCP | Depende de |
|---|---|---|---|---|
| loginserver | `vsserver/bin/loginserver` | `src/conf/loginserver.conf` | 9999 | MySQL |
| sharedserver | `vsserver/bin/sharedserver` | `src/conf/sharedserver.conf` | 9977 | MySQL |
| gameserver | `vsserver/bin/gameserver` | `src/conf/gameserver.conf` | 9998 | MySQL + sharedserver + `data/` |

### 6.2. Subir manualmente (para debug)

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

### 6.3. ⚠️ Script de start/stop (a criar)

Serão criados `start-servers.sh` / `stop-servers.sh` (raiz do vsserver) que:
- verificam se `darkeden-mysql` está rodando;
- sobem os 3 em background (`nohup ... > log/xxx.out 2>&1 &`), salvam PIDs em `.server-pids`;
- `stop-servers.sh` lê os PIDs e encerra (SIGTERM; `-9` força).

---

## Milestone 7 — updateserver/update (opcional)

Compilar (parte do `./build-server.sh all`): `vsserver/bin/updateserver` e `vsserver/bin/update`.

Para rodar o updateserver:
1. Criar `vsserver/data/patch/` (pasta de patches do cliente);
2. Ajustar `src/conf/updateserver.conf` (HomeDir, PatchDir, KeyFile, URLs de download);
3. Subir com `./bin/updateserver -f src/conf/updateserver.conf`.

> Não é necessário para o servidor de jogo funcionar — apenas para distribuir atualizações ao
> cliente. Tratar como extra.

---

## Milestone 8 — Conexão do cliente

O cliente (Windows/DirectX) deve apontar para o IP da máquina do servidor:

| Serviço | Porta |
|---|---|
| loginserver (TCP) | 9999 |
| gameserver (UDP/TCP) | 9998/9997 |
| sharedserver | 9977 |
| updateserver | 3000 |

> ⚠️ Depende do pacote de dados do cliente (IPs, versão do patch). Detalhes serão definidos
> quando o servidor estiver no ar.

---

## Manutenção e troubleshooting

### Comandos úteis

```bash
./install.sh                # garante o ambiente (docker + imagem + banco — SEM build)
./build-server.sh           # compila (target all)
./setup-mysql.sh            # banco
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
| Servidor morre ao subir | ver `log/*.out`; causas comuns: MySQL parado, `data/` incompleto, conf com IP errado |
| `invalid packet id(422)` | loginserver sem `GMServerInfo` (✅ já ok neste repo — revalidar após build) |
| `cannot load` / treasure vazio no boot | ⚠️ questão do `HName` coreano vs bins em inglês — ver seção de decisões |
| MySQL não reimporta banco | importação só na 1ª criação do volume: `./setup-mysql.sh reset` |

### Ordem de limpeza total

```bash
./wipe-all.sh        # apaga tudo (build + banco + imagem)
./install.sh         # recomeça o ambiente (docker + imagem + banco)
./build-server.sh    # compila de novo
```

---

## ✅ Status atual (testado em 2026-08-07)

| Item | Status |
|---|---|
| Imagem `darkeden-woody:test` (Debian 3.0 + gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0) | ✅ construída |
| Toolchain woody 100% offline (tarballs em `vsserver/docker/thirdparty/`) | ✅ presentes |
| Pipeline: `install.sh` + `build-server.sh` + `setup-mysql.sh` + `wipe-all.sh` | ✅ criados |
| Código-fonte compilando 100% (target `all`) | ⚠️ em andamento — ver próximos passos |

### Próximos passos

1. Rodar `./install.sh` (ou etapa por etapa) até o ambiente estar pronto;
2. Rodar `./build-server.sh` e resolver os erros de compilação (problema de CÓDIGO, não de pipeline);
3. Decidir a questão da `data/` (Milestone 2 — em aberto);
4. Subir servidores e validar (Milestone 6).

---

## ⚠️ Decisões em aberto — pontos a avaliar na hora de subir

1. **`data/` (inglês vs coreano)**: qual usar e quando copiar para `vsserver/data/` — decisão
   adiada até chegarmos nessa parte (Milestone 2).
2. **Treasure/drops (`HName` coreano vs bins em inglês)**: avaliar no boot — se `cannot load`/
   treasure vazio para muitos monstros, aplicar fallback `HName → EName` em `MonsterInfo.cpp`
   (ou copiar bins coreanos). Preferência: NÃO mexer no código se não for preciso.
3. **updateserver**: necessário? Ajustar confs (HomeDir/PatchDir/KeyFile) se for usar.
