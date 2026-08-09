# Appendix — DarkEden Server (vssource)

> 🌐 **English:** [APPENDIX.md](APPENDIX.md) · **Português:** [APPENDIX.pt.md](APPENDIX.pt.md)
>
> Detailed version of the [README](README.md). Moved here to keep the README concise.
> All content below was cross-checked against the actual scripts.

---

## 1. Complete step-by-step (from scratch)

### Step 0 — Prerequisite: nothing beyond Linux + internet

The only real prerequisite is a Linux with internet access (for Docker to download the images
`debian/eol:woody`, `vettadock/mysql-old:4.1` — only the 1st time). Everything else (gcc-2.95.4,
Lua 4.0.1, STLport, Xerces, cppunit) is **inside the image** or in the tarballs of
`vsserver/docker/thirdparty/` (100% offline).

### Step 1 — Prepare Docker (1st time, asks for sudo 1x)

```bash
cd vssource
./install.sh docker
```

What it does: installs `docker.io` + `docker compose` v2 plugin (if missing), adds your user to
the `docker` group (log out/in if prompted) and validates `docker info` + `docker compose version`.

> If you already have Docker installed, it only validates and changes nothing.

### Step 2 — Build the woody image (1st time, takes a while)

```bash
./install.sh image
```

What it does: downloads `debian/eol:woody` and compiles inside the image: gcc-2.95.4 (already
included), Lua 4.0.1, STLport 4.6.2 + lib, Xerces 2.8, cppunit 1.8.0, headers patch (ICE fix).
Result: image `darkeden-woody:test` — **everything offline** (tarballs in `thirdparty/`).

### Step 3 — Data folder (English — already in place)

```bash
./install.sh            # checks/warns about vsserver/data/ — the English data is already extracted
```

> The active data is the **English** variant (extracted from `vsserver/zips/data-ingles.zip` into
> `vsserver/data/`). See [Milestone 2](#milestone-2--data-folder-english).

### Step 4 — Start MySQL 4.1 (1st time, downloads image + imports the real database)

```bash
./install.sh mysql      # or ./setup-mysql.sh (does the same)
```

Downloads `vettadock/mysql-old:4.1`, starts the `darkeden-mysql` container. On the 1st startup
the entrypoint extracts the `DARKEDEN.tar.gz`/`USERINFO.tar.gz` tarballs (real FRM/MYD/MYI data)
and imports them into the datadir, then applies `patch-compat.sql` (local IPs, zone names, user
`elcastle`/`elca110`). Validates the databases at the end.

### Step 5 — Compile the server (target `all`)

```bash
./build-server.sh
```

Starts a container from the woody image mounting `vsserver/` at `/src` and runs make inside.
Binaries in `vsserver/bin/` (loginserver, sharedserver, gameserver, ...). Log in
`vsserver/build.log`. **You don't need to know anything about docker** — the script does
everything.

### Step 6 — (optional) Re-run / clean up

```bash
./build-server.sh        # recompiles (continues where it left off)
./setup-mysql.sh status  # checks the database
./wipe-all.sh            # TOTAL cleanup (build + database + images)
./wipe-all.sh code       # only build artifacts
./wipe-all.sh bd         # only database/docker/images
```

---

## 2. Command flow → what happens under the hood

| You run | The script calls internally |
|---|---|
| `./install.sh` | `01-docker-setup.sh` (if docker missing) → `02-build-image.sh` (if image missing) → **inline** data check (warn only) → `mysql.sh start` |
| `./install.sh build` | `./build-server.sh all` |
| `./install.sh wipe` | `./wipe-all.sh` |
| `./build-server.sh` | `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` (target `all`) |
| `./setup-mysql.sh` | `mysql.sh start` (→ `docker compose up -d mysql` + imports real database: tarballs + patch) |
| `./wipe-all.sh bd` | `docker compose down` + `rm mysql-data` (sudo if needed) + `docker rmi vettadock/mysql-old:4.1 darkeden-woody:test` |

> ℹ️ `03-prepare-data.sh` is a **manual** helper — it only checks/warns about `data/`. It is **not**
> called by `install.sh` (the check there is done inline). Not needed today: `vsserver/data/`
> already holds the English data. If you ever want to (re)extract a data zip into `vsserver/data/`,
> do it manually (`unzip` + `cp`) — the copy step is intentionally not automated.

---

## 3. Scripts quick reference (full)

### Root scripts (`vssource/`)

| Script | Command | What it does | When to use |
|---|---|---|---|
| **install.sh** | `./install.sh` | prepares the environment: docker → image → data → database (**NO build** — idempotent) | 1st time / ensure environment |
| | `./install.sh docker` | only Docker on the host (asks for sudo 1x) | if Docker is missing |
| | `./install.sh image` | only builds `darkeden-woody:test` | if the image disappears |
| | `./install.sh mysql` | only starts MySQL (downloads + imports) | database |
| | `./install.sh build` | compiles the server (= `./build-server.sh all`) | build |
| | `./install.sh wipe` | total cleanup (= `./wipe-all.sh`) | reset everything |
| **build-server.sh** | `./build-server.sh` | compiles via woody container (target `all`) | whenever you want to compile |
| | `./build-server.sh <target>` | compiles another target (`allgameserver`, `allloginserver`, `allsharedserver`, `alltheoneserver`) | advanced |
| **setup-mysql.sh** | `./setup-mysql.sh` | starts MySQL 4.1 + imports the real database (1st time) | database |
| | `./setup-mysql.sh start` | same (alias; also `preparar`/`setup`) | database |
| | `./setup-mysql.sh stop` | stops MySQL | database |
| | `./setup-mysql.sh status` | shows if it's up + databases | check |
| | `./setup-mysql.sh reset` | wipes data and reimports from scratch (asks for sudo) | recreate database |
| | `./setup-mysql.sh logs` | MySQL logs | debug |
| | `./setup-mysql.sh sql` | opens the mysql client (root without password) | queries |
| **start-servers.sh** | `./start-servers.sh` | starts loginserver → sharedserver → gameserver in background; checks MySQL + binaries + confs; PIDs in `.server-pids`; logs in `vsserver/log/*.out` | run the game servers |
| | `./start-servers.sh -v` | verbose (tails each server log after start) | debug |
| **stop-servers.sh** | `./stop-servers.sh` | stops the servers via `.server-pids` (SIGTERM) | stop |
| | `./stop-servers.sh -9` | forces SIGKILL if they don't exit | stuck processes |
| **wipe-all.sh** | `./wipe-all.sh` | removes EVERYTHING (build + database + images) | total cleanup |
| | `./wipe-all.sh code` | only build artifacts (also kills running servers) | clean rebuild |
| | `./wipe-all.sh bd` | only database/docker/images (asks for sudo if needed) | recreate database |

### Internal scripts (`vsserver/docker/` — no need to touch)

| Script | What it does |
|---|---|
| `01-docker-setup.sh` | (host, sudo) installs/validates Docker + compose v2 + docker group |
| `02-build-image.sh` | (host) builds `darkeden-woody:test` (100% offline, tarballs in `thirdparty/`) |
| `03-prepare-data.sh` | (manual helper) checks/warns about `data/` — not called by `install.sh`; data is already in place (English) |
| `build.sh` | (container) the make itself: mysql symlink + dependency check + headers patch + `make -O1` |
| `mysql.sh` | (host) manages MySQL 4.1: start/stop/logs/shell/sql/rm |
| `mysql41-entrypoint.sh` | (container) custom MySQL entrypoint — extracts the real DB tarballs + applies `patch-compat.sql` on 1st volume creation |
| `setup-woody-toolchain.sh` | (container) installs Lua/STLport/Xerces/cppunit in the image (called by the Dockerfile) |
| `patch-woody-headers.sh` | (container) gcc-2.95.4 ICE fix (idempotent) |
| `Dockerfile.woody` | woody image (Debian 3.0 + gcc-2.95.4 + toolchain of the era) |
| `docker-compose.yml` | **only** the `mysql` service (4.1) — the build is NOT a compose service |
| `.dockerignore` | excludes `mysql-data/` + logs from the image build context |

---

## 4. Milestones

### Milestone 1 — Host prerequisites

All the build happens **inside Docker** (image `darkeden-woody:test`). On the host you only
need **Docker** + the **docker compose** plugin (for MySQL 4.1).

| Component | Version | Purpose | Where it lives |
|---|---|---|---|
| Docker | any recent | runs build + MySQL 4.1 | host |
| `docker compose` plugin | 2.x | orchestrates MySQL | host |
| gcc-2.95.4 | Debian woody | compiles 2005 code | **inside the image** |
| Lua 4.0.1 | from source | Lua 4 API (`lua_open(size)`) | **inside the image** |
| STLport 4.6.2 | from source | `<hash_map>`, `<slist>`, iostreams | **inside the image** |
| Xerces 2.8 | from source | config XML (`SXml.cpp`) | **inside the image** |
| cppunit 1.8.0 | from source | tests (`CppUnit::TextUi::TestRunner`) | **inside the image** |

Docker setup on the host:

```bash
./install.sh docker      # asks for sudo 1x; installs/validates docker + compose + docker group
```

The script installs `docker.io` and the `docker-compose-v2` plugin (if missing), adds your user
to the `docker` group (log out/in for it to take effect) and validates `docker info` + `docker compose version`.

### Milestone 2 — Data folder (English)

The server reads data from `data/` relative to the `HomePath` of the confs (which is `.`).
The repo ships **two zips** with the two data variants (in `vsserver/zips/`):

| File | Content | Note |
|---|---|---|
| `data-ingles.zip` (585 files) | NPC bins **in English**, maps `.smp/.ssi`, `EventGQuest.xml`, `lua/` | **Used** (matches the `EName` of the database) |
| `data-coreano.zip` (629 files) | NPC bins with **Korean** EUC-KR names | Alternative — only the names of the `.bin` change |

**Decided:** `vsserver/data/` holds the **English** variant extracted (581 files, **gitignored**).
The Korean zip stays in `vsserver/zips/` as an alternative if ever needed.

> ℹ️ **Treasure/drops:** with English data + English `EName`s in the database, no `cannot load` /
> empty-treasure problems were observed in the logs. If a future setup ever shows empty drops for
> many monsters (Korean `HName` building a bin name that doesn't exist), the fallback is a
> `HName → EName` fix in `MonsterInfo.cpp` — **preference: don't touch the code unless needed**.

### Milestone 3 — Compile the server (build via Docker — MAIN)

The build runs **inside a container** (image `darkeden-woody:test`, base Debian 3.0 with
gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0). The source code is
**mounted** (bind mount) from `vsserver/` to `/src` — nothing is installed on the host. The
binaries come out in `vsserver/bin/`.

```bash
# 1. (once) builds the woody image — downloads debian/eol:woody + compiles the toolchain
./install.sh image

# 2. compiles the server (target all by default — all binaries)
./build-server.sh
./build-server.sh allgameserver      # only the gameserver (advanced)
```

Full log in `vsserver/build.log`. Binaries in `vsserver/bin/`.
The build uses `-O1` (required: without it the gcc-2.95.4 ICE in STLport returns) and applies
`patch-woody-headers.sh` automatically.

### Milestone 4 — Start MySQL 4.1 (Docker) and import the real database

```bash
./setup-mysql.sh            # downloads vettadock/mysql-old:4.1 + starts + imports (1st time)
```

- Container: `darkeden-mysql` (image `vettadock/mysql-old:4.1`)
- Port **3306 exposed** on the host (the servers run on the host and connect to `127.0.0.1:3306`)
- Data persisted in `vsserver/docker/mysql-data/`

The compose mounts `vsserver/sqls/` at `/docker-entrypoint-initdb.d` — on the **first**
initialization of the volume, the custom entrypoint (`mysql41-entrypoint.sh`) imports the REAL
server database. **These are NOT .sql dumps** — the opendarkeden dumps have a different schema;
the source is always the tarballs:

1. Extracts `DARKEDEN.tar.gz` → database `DARKEDEN` (MyISAM FRM/MYD/MYI, 400+ tables)
2. Extracts `USERINFO.tar.gz` → database `USERINFO`
3. Applies `patch-compat.sql` → local IPs (127.0.0.1), exact zone names, user
   `elcastle`/`elca110` (OLD_PASSWORD format password, required by the 3.23 client of the servers)

> ⚠️ The import **only runs the 1st time** the `mysql-data/` volume is created. To reimport
> from scratch: `./setup-mysql.sh reset` (removes container + `mysql-data/` and starts again).

Verification:

```bash
./setup-mysql.sh status     # shows if it's up + databases
./setup-mysql.sh sql        # opens the mysql client (root without password)
# inside mysql:
SHOW DATABASES;             # DARKEDEN and USERINFO
USE DARKEDEN; SHOW TABLES;  # 400+ tables (real server data)
SELECT COUNT(*) FROM WorldDBInfo;  # must have a row with Host=127.0.0.1
```

> **Server credentials (conf)**: `elcastle` / `elca110` in the `DARKEDEN` and `USERINFO`
> databases — created by the entrypoint (GRANT + OLD_PASSWORD password).
> The loginserver conf also has `DB_VERSION : 4`, which makes the login handler validate
> passwords with `OLD_PASSWORD()` (16 hex) instead of `PASSWORD()` (41 chars).

### Milestone 5 — Configs (confs)

All confs live in `vsserver/src/conf/`. ⚠️ The servers are run **from the root of vsserver**
(`HomePath: .`), so confs are referenced as `-f src/conf/xxx.conf`. Below are the **key
settings** of each (the files contain more options — server IDs, billing, logs, etc.).

#### `gameserver.conf` (port 9998)

```ini
User : excel96
HomePath : .              # relative to the vsserver root
TCPPort : 9998
LoginServerIP: 127.0.0.1
LoginServerUDPPort : 9996
GameServerUDPPort : 9997
SharedServerIP : 127.0.0.1
SharedServerPort : 9977
ServerID : 0              # ⚠️ NOT the ServerID of the table — it's the GroupID (0 = default group)
IsNetMarble : 0
DB_HOST : 127.0.0.1       # MySQL docker on the host
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

#### `loginserver.conf` (port 9999)

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
DB_VERSION : 4           # OLD_PASSWORD() login validation (required for accounts to log in)
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

#### `sharedserver.conf` (port 9977)

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

#### `updateserver.conf` ⚠️ (port 3000)

> ℹ️ **Not used in this project.** The updateserver is not needed to play (loginserver/
> sharedserver/gameserver are enough). It only serves the **client auto-update** (`PatchDir`,
> `INFOURL`, `GUILDURL`). It is **not** started by `start-servers.sh`. Below is the stock conf for
> reference — if you ever enable it, adjust:

```ini
HomeDir : /darkeden       # → should point to the vsserver root (e.g.: .)
PatchDir : data/patch     # → check if vsserver/data/patch exists (or create it)
Port : 3000
KeyFile : key357.dat      # → check existence (the update client uses it)
KeyVersion : 3000
```

### Milestone 6 — Start the servers

Order and ports:

| Server | Binary | Conf | TCP Port | Depends on |
|---|---|---|---|---|
| loginserver | `vsserver/bin/loginserver` | `src/conf/loginserver.conf` | 9999 | MySQL |
| sharedserver | `vsserver/bin/sharedserver` | `src/conf/sharedserver.conf` | 9977 | MySQL |
| gameserver | `vsserver/bin/gameserver` | `src/conf/gameserver.conf` | 9998 | MySQL + sharedserver + `data/` |

Start with the provided scripts (from the project root):

```bash
./start-servers.sh          # checks MySQL + binaries + confs, then starts the 3 in background
./start-servers.sh -v       # verbose
./stop-servers.sh           # stops them (SIGTERM)
./stop-servers.sh -9        # force (SIGKILL)
```

- PIDs are saved in `.server-pids`
- Logs in `vsserver/log/loginserver.out`, `.../sharedserver.out`, `.../gameserver.out`
- `start-servers.sh` kills stale instances first (avoids "address already in use")

Or start manually (for debug), each in its own terminal, **from the vsserver root**:

```bash
cd vsserver   # server root (HomePath = .)

# 1st: MySQL needs to be up (Milestone 4)
docker ps | grep darkeden-mysql

# 2nd: start each server in its own terminal
./bin/loginserver  -f src/conf/loginserver.conf
./bin/sharedserver -f src/conf/sharedserver.conf
./bin/gameserver   -f src/conf/gameserver.conf
```

Signs of success:
- loginserver: registers the server in the database and stays in a loop
- gameserver: `>>> ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY.` + `connection to sharedserver established`

### Milestone 7 — updateserver/update (optional, NOT used)

The binaries `vsserver/bin/updateserver` and `vsserver/bin/update` are compiled as part of
`./build-server.sh all`, but the updateserver is **not used in this project** (not started by
`start-servers.sh`, confs left at stock values). It is not needed for the game server to work —
only to distribute client auto-updates. Treat as extra/unused.

### Milestone 8 — Client connection

The client (Windows/DirectX) must point to the IP of the server machine:

| Service | Port |
|---|---|
| loginserver (TCP) | 9999 |
| gameserver (UDP/TCP) | 9998/9997 |
| sharedserver | 9977 |
| updateserver | 3000 |

> ⚠️ If the client is on another machine, the gameserver IP in the **database** must be the LAN
> IP, not 127.0.0.1:
> ```sql
> UPDATE DARKEDEN.GameServerInfo SET IP='<LAN-IP>';  -- check: ip -4 addr | grep inet
> ```
> `WorldDBInfo.Host` stays 127.0.0.1 (internal server→MySQL). Details depend on the client data
> package (IPs, patch version).

---

## 5. Maintenance and troubleshooting

### Useful commands

```bash
./install.sh                # ensures the environment (docker + image + database — NO build)
./build-server.sh           # compiles (target all)
./setup-mysql.sh            # database
./start-servers.sh          # runs the servers in background
./stop-servers.sh           # stops them
./wipe-all.sh               # total cleanup (build + database + image)
./wipe-all.sh code          # only build artifacts
./wipe-all.sh bd            # only database/docker
```

### Common problems

| Symptom | Likely cause / Solution |
|---|---|
| `docker: command not found` | Docker missing — run `./install.sh docker` (asks for sudo 1x) |
| `ERROR: image darkeden-woody:test does not exist` | run `./install.sh image` (builds the woody image) |
| `Permission denied` when deleting `bin/`/`lib/` | folders created by root in the container — `./wipe-all.sh code` removes them and the build recreates them with your user |
| gcc-2.95.4 ICE on STLport (`_threads.h:579`) | the build already applies `patch-woody-headers.sh` + `-O1` automatically (not your problem) |
| `cannot find -lnsl` | ✅ already fixed — `-lnsl` removed from the Makefiles |
| Server dies on startup | check `vsserver/log/*.out`; common causes: MySQL down, `data/` incomplete, conf with wrong IP |
| `invalid packet id(422)` | loginserver without `GMServerInfo` (✅ already OK in this repo — revalidate after build) |
| `cannot load` / empty treasure on boot | ⚠️ Korean `HName` vs English bins — see [Milestone 2](#milestone-2--data-folder-english) |
| MySQL doesn't reimport database | import only happens on 1st volume creation: `./setup-mysql.sh reset` |

### Total cleanup order

```bash
./wipe-all.sh        # removes everything (build + database + image)
./install.sh         # restarts the environment (docker + image + database)
./build-server.sh    # compiles again
```

---

## 6. Current status

| Item | Status |
|---|---|
| Image `darkeden-woody:test` (Debian 3.0 + gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0) | ✅ built (436MB) |
| 100% offline woody toolchain (tarballs in `vsserver/docker/thirdparty/`) | ✅ present |
| Pipeline: `install.sh` + `build-server.sh` + `setup-mysql.sh` + `wipe-all.sh` | ✅ created |
| Source code compiling (target `all`) | ✅ compiled — all binaries in `vsserver/bin/` (gameserver, loginserver, sharedserver, updateserver, update) |
| `start-servers.sh` / `stop-servers.sh` | ✅ created at the project root |
| MySQL 4.1 with the real database | ✅ `DARKEDEN` / `USERINFO` imported (tarballs + patch) |
| Data folder | ✅ English variant extracted (581 files, gitignored) |
| Servers running | ✅ loginserver (9999), sharedserver (9977), gameserver (9998) — 157 zones loaded |
| updateserver | ⏸️ not used (optional; not started by `start-servers.sh`) |

---

## 7. How to start everything (cheat sheet)

```bash
./install.sh            # environment: docker + image + data + database (NO build)
./build-server.sh       # compile once (or whenever you change the code)
./setup-mysql.sh status # confirm the databases
./start-servers.sh      # loginserver → sharedserver → gameserver
./stop-servers.sh       # stop them
./wipe-all.sh           # total cleanup (build + database + images)
```

*Suggestions and corrections are welcome — open an issue or a PR. See the [README](README.md).*
