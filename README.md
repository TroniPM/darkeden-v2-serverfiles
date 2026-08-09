# DarkEden Server (vssource)

> 🌐 **English:** [README.md](README.md) · **Português:** [README.pt.md](README.pt.md)

Source code of the **DarkEden** game server (~2005). This repository contains the complete
**server-master** (`vsserver/`): source code (`src/`), server data (`data/`), database dumps
(`sqls/`) and Docker infrastructure.

> 🎯 **Official workflow: WOODY environment** (Debian 3.0 + gcc-2.95.4 + STLport 4.6.2 + xerces 2.8
> + cppunit 1.8.0) running **inside Docker**. On the host you only need Docker. No builds on the host.

---

## 🚀 QUICK START (for beginners — new users)

### Prerequisite
- Linux with internet access (only needed for Docker to download the images the 1st time)

### Step 1 — Docker on the host (1st time, asks for sudo)

```bash
cd vssource
./install.sh docker
```

- Installs `docker.io` + compose plugin if missing
- Adds the user to the `docker` group → **log out/in** if prompted

### Step 2 — Woody build image (1st time, takes ~10-40min)

```bash
./install.sh image
```

- Downloads `debian/eol:woody` and compiles inside the image: Lua 4.0.1, STLport 4.6.2 + lib,
  Xerces 2.8, cppunit 1.8.0, headers patch (ICE fix). Everything offline (tarballs in
  `vsserver/docker/thirdparty/`).
- Result: image `darkeden-woody:test` (436MB)

### Step 3 — MySQL 4.1 database (1st time, downloads image + imports real database)

```bash
./install.sh mysql
```

- Downloads `vettadock/mysql-old:4.1`, starts the `darkeden-mysql` container (port 3306)
- On the 1st startup the entrypoint extracts the `DARKEDEN.tar.gz` + `USERINFO.tar.gz` tarballs
  (real server FRM/MYD/MYI data) and imports them into the datadir
- Then applies `patch-compat.sql` (local IPs, zone names, user `elcastle`/`elca110`)

### Step 4 — Compile the server ⚠️ (takes ~35-40min the 1st time)

```bash
./build-server.sh        # target all (loginserver, sharedserver, gameserver, ...)
# or: ./build-server.sh allgameserver / allloginserver / ...  (advanced)
```

- Runs make inside the woody container (gcc-2.95.4)
- Binaries in `vsserver/bin/`, full log in `vsserver/build.log`

### Step 5 — Verify / manage

```bash
./setup-mysql.sh status   # checks if the database is up + databases
./wipe-all.sh             # TOTAL cleanup (build + database + images)
./wipe-all.sh code        # only build artifacts
./wipe-all.sh bd          # only database/docker/images
```

> 💡 **`./install.sh` (no argument) prepares EVERYTHING except the build**: docker + image + database.
> The build is always done by `./build-server.sh`, so you have control over when to compile.

---

## 📋 Repository structure

```
vssource/
├── install.sh             # prepares the environment: docker + image + database (NO build)
├── build-server.sh        # compiles via woody container (run from outside docker)
├── setup-mysql.sh         # prepares MySQL 4.1 (downloads image + imports real database)
├── wipe-all.sh            # removes build and/or database/docker/image
├── vsserver/              # = server-master
│   ├── src/               # source code (Core/ = active; OLDCore/ = backup/parallel)
│   ├── src/conf/          # gameserver.conf, loginserver.conf, sharedserver.conf, updateserver.conf
│   ├── data/              # ⚠️ active server data (see Milestone 2)
│   │   ├── data-ingles/   #   English data (581 files)
│   │   └── data - coreano/#   Korean data (628 files)
│   ├── sqls/              # real server database (DARKEDEN.tar.gz, USERINFO.tar.gz) + patch-compat.sql
│   ├── docker/            # Dockerfile.woody + internal scripts + thirdparty/
│   └── (bin/ lib/ log/ temp/ are created by the build)
```

### Scripts (project root)

| Script | What it does | When to use |
|---|---|---|
| `./install.sh` | **prepares the environment**: docker + woody image + database (idempotent — can be run again; **does NOT compile**) | 1st time (or whenever you want to "ensure the environment") |
| `./install.sh docker` | only Docker on the host (asks for sudo 1x) | if Docker is missing |
| `./install.sh image` | only builds the `darkeden-woody:test` image | if the image disappears |
| `./install.sh mysql` | only starts MySQL 4.1 (downloads image + imports real database) | database |
| `./install.sh build` | compiles the server (= `./build-server.sh`) | build |
| `./install.sh wipe` | total cleanup (= `./wipe-all.sh`) | reset everything |
| `./build-server.sh` | compiles the server via woody container (target `all` by default) | **whenever you want to compile** |
| `./build-server.sh <target>` | compiles another target (`allgameserver`, `allloginserver`, ...) | advanced |
| `./setup-mysql.sh` | downloads image vettadock/mysql-old:4.1 + starts + imports real database (1st time) | database |
| `./setup-mysql.sh stop/reset/logs/sql` | manages the database | advanced |
| `./wipe-all.sh` | removes EVERYTHING (build + database + image) | total cleanup |
| `./wipe-all.sh code` | removes only build artifacts | clean rebuild |
| `./wipe-all.sh bd` | removes only database/docker/image | recreate database |

### Internal scripts (`vsserver/docker/` — no need to touch)

| Script | What it does |
|---|---|
| `01-docker-setup.sh` | (host, sudo) installs/validates Docker + compose plugin + docker group |
| `02-build-image.sh` | (host) builds `darkeden-woody:test` (100% offline, tarballs in `thirdparty/`) |
| `03-prepare-data.sh` | ⚠️ prepares `data/` — **open decision** (see Milestone 2) |
| `build.sh` | (container) the make itself, runs inside the woody container |
| `mysql.sh` | (host) manages MySQL 4.1: start/stop/logs/shell/sql/rm |
| `setup-woody-toolchain.sh` | (container) installs Lua/STLport/Xerces/cppunit in the image (Dockerfile) |
| `patch-woody-headers.sh` | (container) gcc-2.95.4 ICE fix (idempotent) |
| `Dockerfile.woody` | woody image (Debian 3.0 + gcc-2.95.4 + toolchain of the era) |
| `docker-compose.yml` | only the `mysql` service (4.1) — the build is NOT a compose service |

### Command flow → what happens under the hood

| You run | The script calls internally |
|---|---|
| `./install.sh` | `01-docker-setup.sh` → `02-build-image.sh` → `03-prepare-data.sh` → `mysql.sh start` |
| `./build-server.sh` | `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` |
| `./setup-mysql.sh` | `mysql.sh start` (→ `docker compose up -d mysql` + imports real database: tarballs + patch) |
| `./wipe-all.sh bd` | `docker compose down` + `rm mysql-data` (sudo if needed) + `docker rmi vettadock/mysql-old:4.1 darkeden-woody:test` |

---

## 📋 COMPLETE STEP-BY-STEP (from scratch)

This section covers **EVERYTHING** that needs to be done, using **only the project scripts**.
Follow in order. (Equivalent to Milestones 1–4, condensed.)

### Step 0 — Prerequisite: nothing beyond Linux + internet

The only real prerequisite is a Linux with internet access (for Docker to download the images
`debian/eol:woody`, `vettadock/mysql-old:4.1` — only the 1st time). Everything else (gcc-2.95.4 compiler, Lua
4.0.1, STLport, Xerces, cppunit) is **inside the image** or in the tarballs of
`vsserver/docker/thirdparty/` (100% offline).

### Step 1 — Prepare Docker (1st time, asks for sudo 1x)

```bash
cd vssource
./install.sh docker
```

What it does: installs `docker.io` + `docker compose` plugin (if missing), adds your user to the
`docker` group (log out/in if prompted) and validates `docker info`.

> If you already have Docker installed, it only validates and changes nothing.

### Step 2 — Build the woody build image (1st time, takes a while)

```bash
./install.sh image
```

What it does: downloads `debian/eol:woody` and compiles inside the image: gcc-2.95.4 (already included), Lua 4.0.1,
STLport 4.6.2 + lib, Xerces 2.8, cppunit 1.8.0, headers patch (ICE fix). Result: image
`darkeden-woody:test` — **everything offline** (tarballs in `thirdparty/`).

### Step 3 — Prepare the data folder (⚠️ open)

```bash
./install.sh            # step 3/5 checks/warns about vsserver/data/
```

> ⚠️ **Open decision**: which data to use (English vs Korean). Until we decide, the
> `install.sh` only warns — see [Milestone 2](#milestone-2--prepare-the-data-folder-%EF%B8%8F-open).

### Step 4 — Start the MySQL 4.1 database (1st time, downloads image + imports real database)

```bash
./install.sh mysql      # or ./setup-mysql.sh (does the same)
```

What it does: downloads `vettadock/mysql-old:4.1`, starts the `darkeden-mysql` container. On the 1st startup the
entrypoint extracts the `DARKEDEN.tar.gz`/`USERINFO.tar.gz` tarballs (real FRM/MYD/MYI database) and
imports them into the datadir, then applies `patch-compat.sql` (local IPs, zone names, user
elcastle). Validates the databases at the end.

### Step 5 — Compile the server (target `all`)

```bash
./build-server.sh
```

What it does: starts a container from the woody image mounting `vsserver/` at `/src` and runs make
inside. Binaries in `vsserver/bin/` (loginserver, sharedserver, gameserver, ...). Log in
`vsserver/build.log`. **You don't need to know anything about docker** — the script does everything.

### Step 6 — (optional) Run again / clean up

```bash
./build-server.sh       # recompiles (continues where it left off)
./setup-mysql.sh status # checks database
./wipe-all.sh           # TOTAL cleanup (build + database + images)
./wipe-all.sh code      # only build artifacts
./wipe-all.sh bd        # only database/docker/images
```

---

## 📊 Quick reference of scripts and commands

### Root scripts (`vssource/`)

| Script | Command | What it does | When to use |
|---|---|---|---|
| **install.sh** | `./install.sh` | prepares the environment: docker → image → data → database (**NO build** — idempotent) | 1st time / ensure environment |
| | `./install.sh docker` | only Docker on the host (asks for sudo 1x) | if Docker is missing |
| | `./install.sh image` | only builds `darkeden-woody:test` | if the image disappears |
| | `./install.sh mysql` | only starts MySQL (downloads + imports) | database |
| | `./install.sh build` | compiles the server (= `./build-server.sh`) | build |
| | `./install.sh wipe` | total cleanup (= `./wipe-all.sh`) | reset everything |
| **build-server.sh** | `./build-server.sh` | compiles via woody container (target `all`) | whenever you want to compile |
| | `./build-server.sh <target>` | compiles another target (`allgameserver`, `allloginserver`, ...) | advanced |
| **setup-mysql.sh** | `./setup-mysql.sh` | starts MySQL 4.1 + imports real database (1st time) | database |
| | `./setup-mysql.sh start` | same (alias) | database |
| | `./setup-mysql.sh stop` | stops MySQL | database |
| | `./setup-mysql.sh status` | shows if it's up + databases | check |
| | `./setup-mysql.sh reset` | wipes data and reimports from scratch (asks for sudo) | recreate database |
| | `./setup-mysql.sh logs` | MySQL logs | debug |
| | `./setup-mysql.sh sql` | opens the mysql client (root without password) | queries |
| **wipe-all.sh** | `./wipe-all.sh` | removes EVERYTHING (build + database + images) | total cleanup |
| | `./wipe-all.sh code` | only build artifacts | clean rebuild |
| | `./wipe-all.sh bd` | only database/docker/images (asks for sudo if needed) | recreate database |

### Internal scripts (`vsserver/docker/` — no need to touch)

| Script | What it does |
|---|---|
| `01-docker-setup.sh` | (host, sudo) installs/validates Docker + compose + docker group |
| `02-build-image.sh` | (host) builds `darkeden-woody:test` (offline) |
| `03-prepare-data.sh` | ⚠️ prepares `data/` — open |
| `build.sh` | (container) the make itself (mysql symlink + headers patch + make -O1) |
| `mysql.sh` | (host) start/stop/logs/shell/sql/rm of MySQL 4.1 |
| `setup-woody-toolchain.sh` | (container) installs Lua/STLport/Xerces/cppunit in the image |
| `patch-woody-headers.sh` | (container) gcc-2.95.4 ICE fix |
| `Dockerfile.woody` | woody image (Debian 3.0 + gcc-2.95.4 + toolchain) |
| `docker-compose.yml` | `mysql` (4.1) + `build` (woody) services |

### Command flow → what happens under the hood

| You run | The script calls internally |
|---|---|
| `./install.sh` | `01-docker-setup.sh` → `02-build-image.sh` → `03-prepare-data.sh` → `mysql.sh start` |
| `./install.sh build` | `./build-server.sh` → `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` |
| `./build-server.sh` | `docker run -v vsserver:/src darkeden-woody:test bash /src/docker/build.sh` |
| `./setup-mysql.sh` | `mysql.sh start` (→ `docker compose up -d mysql` + imports real database: tarballs + patch) |
| `./wipe-all.sh bd` | `docker compose down` + `rm mysql-data` (sudo if needed) + `docker rmi vettadock/mysql-old:4.1 darkeden-woody:test` |

---

## Milestone 1 — Host prerequisites

### 1.1. What is needed (ON THE HOST — no builds on the host!)

All the build happens **inside Docker** (image `darkeden-woody:test`). On the host you only need
**Docker** + **docker compose** plugin (for MySQL 4.1).

| Component | Version | Purpose | Where it lives |
|---|---|---|---|
| Docker | any recent | runs build + MySQL 4.1 | host |
| `docker compose` plugin | 2.x | orchestrates MySQL | host |
| gcc-2.95.4 | Debian woody | compiles 2005 code | **inside the image** |
| Lua 4.0.1 | from source | Lua 4 API (`lua_open(size)`) | **inside the image** |
| STLport 4.6.2 | from source | `<hash_map>`, `<slist>`, `iostreams` | **inside the image** |
| Xerces 2.8 | from source | config XML (`SXml.cpp`) | **inside the image** |
| cppunit 1.8.0 | from source | tests (`CppUnit::TextUi::TestRunner`) | **inside the image** |

### 1.2. Docker setup (host)

```bash
./install.sh docker      # asks for sudo 1x; installs/validates docker + compose + docker group
```

The script: installs `docker.io` and the `docker-compose-v2` plugin (if missing), adds your user
to the `docker` group (log out/in for it to take effect) and validates `docker info` + `docker compose version`.

---

## Milestone 2 — Prepare the `data/` folder ⚠️ (OPEN)

The server reads data from `data/` relative to the `HomePath` of the confs (which will be `.`). There are two
versions of data in the repo:

| Folder | Content | Note |
|---|---|---|
| `data/data-ingles/data/` | 581 files (NPC bins **in English**, maps `.smp/.ssi`, `EventGQuest.xml`, `lua/`) | **Recommended** (matches the `EName` of the database) |
| `data/data - coreano/data/` | 628 files (NPC bins with **Korean** EUC-KR names) | Only the names of the `.bin` change (267 more bins) |

> ⚠️ **OPEN DECISION (2026-08-07):** which data to use (English vs Korean) and when/how to copy
> to `vsserver/data/`. Until we decide, `03-prepare-data.sh` only checks and warns.
> **We'll decide when we get to that part** — see [Open decisions](#-open-decisions--points-to-evaluate-when-starting-up).

> ⚠️ **Treasure/drops (open decision):** in the other project some monsters had a Korean `HName`
> in the database and the server built the treasure file name from it — with English data this
> generated "not found" bins (zeroed drops). There, a fix was applied in the code
> (`HName → EName` fallback in `MonsterInfo.cpp`). **Here the preference is NOT to touch the code**
> — evaluate at startup: if the log shows `cannot load`/empty treasure for many monsters, apply the
> same fallback (or copy the missing Korean bins).

---

## Milestone 3 — Compile the server (build via Docker — MAIN)

### 3.1. How it works

The build runs **inside a container** (image `darkeden-woody:test`, base Debian 3.0 with
gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0). The source code is
**mounted** (bind mount) from `vsserver/src` to `/src` — nothing is installed on the host. The binaries
come out in `vsserver/bin/`.

### 3.2. Steps

```bash
# 1. (once) builds the woody image — downloads debian/eol:woody + compiles the toolchain
./install.sh image

# 2. compiles the server (target all by default — all binaries)
./build-server.sh
./build-server.sh allgameserver      # only the gameserver (advanced)
```

Full log in `vsserver/build.log`. Binaries in `vsserver/bin/`.

---

## Milestone 4 — Start MySQL 4.1 (Docker) and import the real database

### 4.1. Start

```bash
./setup-mysql.sh            # downloads the image vettadock/mysql-old:4.1 + starts + imports real database (1st time)
```

- Container: `darkeden-mysql` (image `vettadock/mysql-old:4.1`)
- Port **3306 exposed** on the host (the servers run on the host and connect to `127.0.0.1:3306`)
- Data persisted in `vsserver/docker/mysql-data/`

### 4.2. Real database import (1st startup)

The compose mounts `vsserver/sqls/` at `/docker-entrypoint-initdb.d` — on the **first**
initialization of the volume, the custom entrypoint (`mysql41-entrypoint.sh`) imports the REAL
server database. **These are NOT .sql dumps** — the opendarkeden dumps have a different schema than this
code; the source is always the tarballs:

1. Extracts `DARKEDEN.tar.gz` → database `DARKEDEN` (MyISAM FRM/MYD/MYI data)
2. Extracts `USERINFO.tar.gz` → database `USERINFO`
3. Applies `patch-compat.sql` → local IPs (127.0.0.1), exact zone names, user
   `elcastle`/`elca110` (OLD_PASSWORD format password, required by the 3.23 client of the servers)

> ⚠️ The import **only runs the 1st time** the `mysql-data/` volume is created. To reimport
> from scratch: `./setup-mysql.sh reset` (removes container + `mysql-data/` and starts again).

### 4.3. Verification

```bash
./setup-mysql.sh status     # shows if it's up + databases
./setup-mysql.sh sql        # opens the mysql client (root without password)
# inside mysql:
SHOW DATABASES;             # DARKEDEN and USERINFO
USE DARKEDEN; SHOW TABLES;  # 411 tables (real server data)
SELECT COUNT(*) FROM WorldDBInfo;  # must have a row with Host=127.0.0.1
```

> **Server credentials (conf)**: `elcastle` / `elca110` in the `DARKEDEN` and
> `USERINFO` databases — created by the entrypoint (GRANT + OLD_PASSWORD password).

### 4.4. ⚠️ `sqls/DARKEDEN.tar.gz` and `sqls/USERINFO.tar.gz`

These files contain the **real MyISAM binary data** (`.frm`, `.MYD`, `.MYI`) of the original
server (from a MySQL 5.7 installation, format compatible with 4.1) — they are the **official
database source**, extracted and imported by the entrypoint on the 1st startup (see 4.2). They are
not SQL dumps.

---

## Milestone 5 — Configure the confs

All confs live in `vsserver/src/conf/` (⚠️ note: the servers are run **from the root of
the vsserver** — `HomePath: .` — so confs are referenced as `-f src/conf/xxx.conf` or
copied; see Milestone 6).

### 5.1. `gameserver.conf` (port 9998)

```ini
User : excel96
HomePath : .              # relative to the vsserver root
TCPPort : 9998
LoginServerIP: 127.0.0.1
SharedServerIP : 127.0.0.1
ServerID : 0              # ⚠️ NOT the ServerID of the table — it's the GroupID (0 = default group)
IsNetMarble : 0
DB_HOST : 127.0.0.1       # MySQL docker on the host
DB_PORT : 3306
DB_DB : DARKEDEN
DB_USER : elcastle
DB_PASSWORD : elca110
UI_DB_HOST : 127.0.0.1
UI_DB_DB : USERINFO
UI_DB_USER : elcastle
UI_DB_PASSWORD : elca110
```

### 5.2. `loginserver.conf` (port 9999)

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

### 5.3. `sharedserver.conf` (port 9977)

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

### 5.4. `updateserver.conf` ⚠️ (port 3000)

```ini
# ⚠️ Adjust for this project:
HomeDir : /darkeden       # → should point to the vsserver root (e.g.: .)
PatchDir : data/patch     # → check if vsserver/data/patch exists (or create it)
Port : 3000
KeyFile : key357.dat      # → check existence (the update client uses it)
KeyVersion : 3000
```

> ⚠️ The updateserver is not needed to play (loginserver/sharedserver/gameserver are enough).
> It only serves the **client auto-update** (`PatchDir`, `INFOURL`, `GUILDURL`). Adjust in
> Milestone 7 if you'll use it.

---

## Milestone 6 — Start the servers

### 6.1. Order and ports

| Server | Binary | Conf | TCP Port | Depends on |
|---|---|---|---|---|
| loginserver | `vsserver/bin/loginserver` | `src/conf/loginserver.conf` | 9999 | MySQL |
| sharedserver | `vsserver/bin/sharedserver` | `src/conf/sharedserver.conf` | 9977 | MySQL |
| gameserver | `vsserver/bin/gameserver` | `src/conf/gameserver.conf` | 9998 | MySQL + sharedserver + `data/` |

### 6.2. Start manually (for debug)

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

### 6.3. ⚠️ Start/stop script (to be created)

`start-servers.sh` / `stop-servers.sh` (vsserver root) will be created and will:
- check if `darkeden-mysql` is running;
- start the 3 in background (`nohup ... > log/xxx.out 2>&1 &`), save PIDs in `.server-pids`;
- `stop-servers.sh` reads the PIDs and terminates them (SIGTERM; `-9` forces).

---

## Milestone 7 — updateserver/update (optional)

Compile (part of `./build-server.sh all`): `vsserver/bin/updateserver` and `vsserver/bin/update`.

To run the updateserver:
1. Create `vsserver/data/patch/` (client patches folder);
2. Adjust `src/conf/updateserver.conf` (HomeDir, PatchDir, KeyFile, download URLs);
3. Start with `./bin/updateserver -f src/conf/updateserver.conf`.

> It is not needed for the game server to work — only to distribute updates to the client. Treat as extra.

---

## Milestone 8 — Client connection

The client (Windows/DirectX) must point to the IP of the server machine:

| Service | Port |
|---|---|
| loginserver (TCP) | 9999 |
| gameserver (UDP/TCP) | 9998/9997 |
| sharedserver | 9977 |
| updateserver | 3000 |

> ⚠️ Depends on the client data package (IPs, patch version). Details will be defined
> when the server is up.

---

## Maintenance and troubleshooting

### Useful commands

```bash
./install.sh                # ensures the environment (docker + image + database — NO build)
./build-server.sh           # compiles (target all)
./setup-mysql.sh            # database
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
| Server dies on startup | check `log/*.out`; common causes: MySQL down, `data/` incomplete, conf with wrong IP |
| `invalid packet id(422)` | loginserver without `GMServerInfo` (✅ already OK in this repo — revalidate after build) |
| `cannot load` / empty treasure on boot | ⚠️ Korean `HName` vs English bins issue — see decisions section |
| MySQL doesn't reimport database | import only happens on 1st volume creation: `./setup-mysql.sh reset` |

### Total cleanup order

```bash
./wipe-all.sh        # removes everything (build + database + image)
./install.sh         # restarts the environment (docker + image + database)
./build-server.sh    # compiles again
```

---

## ✅ Current status (tested on 2026-08-07)

| Item | Status |
|---|---|
| Image `darkeden-woody:test` (Debian 3.0 + gcc-2.95.4 + Lua 4.0.1 + STLport 4.6.2 + Xerces 2.8 + cppunit 1.8.0) | ✅ built |
| 100% offline woody toolchain (tarballs in `vsserver/docker/thirdparty/`) | ✅ present |
| Pipeline: `install.sh` + `build-server.sh` + `setup-mysql.sh` + `wipe-all.sh` | ✅ created |
| Source code compiling 100% (target `all`) | ⚠️ in progress — see next steps |

### Next steps

1. Run `./install.sh` (or step by step) until the environment is ready;
2. Run `./build-server.sh` and fix the compilation errors (a CODE problem, not a pipeline problem);
3. Decide the `data/` question (Milestone 2 — open);
4. Start the servers and validate (Milestone 6).

---

## ⚠️ Open decisions — points to evaluate when starting up

1. **`data/` (English vs Korean)**: which to use and when to copy to `vsserver/data/` — decision
   postponed until we get to that part (Milestone 2).
2. **Treasure/drops (Korean `HName` vs English bins)**: evaluate at boot — if `cannot load`/
   empty treasure for many monsters, apply the `HName → EName` fallback in `MonsterInfo.cpp`
   (or copy the Korean bins). Preference: NOT to touch the code if not needed.
3. **updateserver**: needed? Adjust confs (HomeDir/PatchDir/KeyFile) if you'll use it.
