# DarkEden Server (vssource)

> 🌐 **English:** [README.md](README.md) · **Português:** [README.pt.md](README.pt.md)

Source code of the **DarkEden** game server (~2005). This repository contains the complete
**server-master** (`vsserver/`): source code (`src/`), server data (`data/`), the **real**
database (`sqls/`) and the Docker infrastructure.

> 🎯 **Official workflow: WOODY environment** (Debian 3.0 + gcc-2.95.4 + STLport 4.6.2
> + xerces 2.8 + cppunit 1.8.0) running **inside Docker**. On the host you only need
> Docker + the compose plugin. **No builds on the host.**

---

## 🚀 Quick start (from zero)

| Step | Command | What it does | Time (1st time) |
|---|---|---|---|
| 1. Docker | `./install.sh docker` | installs `docker.io` + compose plugin, adds your user to the `docker` group (asks for sudo 1x) | ~1min |
| 2. Build image | `./install.sh image` | builds `darkeden-woody:test` with the era toolchain — **100% offline** (tarballs in `vsserver/docker/thirdparty/`) | ~10–40min |
| 3. Database | `./install.sh mysql` | downloads `vettadock/mysql-old:4.1`, starts `darkeden-mysql` and imports the **real** database (tarballs + patch) | ~2–5min |
| 4. Compile | `./build-server.sh` | runs make inside the woody container (target `all`) → binaries in `vsserver/bin/` | ~35–40min |
| 5. Manage | see [Scripts](#scripts) | check the database, rebuild, run/stop servers, wipe | — |

> 💡 `./install.sh` (no argument) prepares **everything except the build** (docker + image +
> data + database — idempotent). `./build-server.sh` compiles whenever you want.

---

## Scripts

All scripts are at the project root. They are idempotent (safe to re-run).

| Script | What it does |
|---|---|
| `./install.sh` | prepares the whole environment (docker → image → data → database). Sub-commands: `docker` · `image` · `mysql` · `build` (= `./build-server.sh`) · `wipe` (= `./wipe-all.sh`) |
| `./build-server.sh [target]` | compiles via the woody container (`all` by default; e.g. `allgameserver`) |
| `./setup-mysql.sh [start\|stop\|status\|reset\|logs\|sql]` | manages MySQL 4.1 |
| `./start-servers.sh [-v]` | starts loginserver → sharedserver → gameserver in background (PIDs in `.server-pids`, logs in `vsserver/log/`) |
| `./stop-servers.sh [-9]` | stops them (SIGTERM; `-9` forces) |
| `./wipe-all.sh [code\|bd]` | total cleanup; `code` = build artifacts only, `bd` = database/docker/images only |

---

## Repository structure

```
vssource/
├── install.sh / build-server.sh / setup-mysql.sh / wipe-all.sh
├── start-servers.sh / stop-servers.sh
├── vsserver/                # = server-master
│   ├── src/                 # source code (Core/ = active; OLDCore/ = backup/parallel)
│   ├── src/conf/            # gameserver / loginserver / sharedserver / updateserver .conf
│   ├── data/                # ⚠️ active server data (currently English, 581 files) — gitignored
│   ├── zips/                # data-ingles.zip · data-coreano.zip (source of `data/`)
│   ├── sqls/                # real database: DARKEDEN.tar.gz + USERINFO.tar.gz + patch-compat.sql
│   ├── docker/              # Dockerfile.woody + internal scripts + thirdparty/
│   └── (bin/ lib/ log/ temp/ are created by the build)
```

> ℹ️ `vsserver/data/` is **gitignored** and holds the English data (extracted from
> `vsserver/zips/data-ingles.zip`) — see [Milestone 2](APPENDIX.md#milestone-2--data-folder-english).

---

## System dependencies

**Host (only these):**
- **Linux — Debian/Ubuntu-based recommended** (the Docker auto-install uses `apt-get`)
- **Docker** + the **`docker compose` v2 plugin** (installed/validated by `./install.sh docker`)
- **Internet** on the first run (to download `debian/eol:woody` and `vettadock/mysql-old:4.1`)
- `bash`, `sudo`, and your user in the `docker` group

**Everything else is inside the image — nothing to install on the host:**
gcc-2.95.4, Lua 4.0.1, STLport 4.6.2 (+ `libstlport_gcc.a`), Xerces 2.8, cppunit 1.8.0
and the gcc-2.95.4 headers patch (ICE fix).

---

## Third-party (vendored)

`vsserver/docker/thirdparty/` ships the **exact upstream sources** used to build the toolchain
inside the image, making the image build **100% offline**:

| Tarball | Purpose |
|---|---|
| `lua-4.0.1.tar.gz` | Lua 4 API (`lua_open(size)`) used by the scripts |
| `STLport-4.6.2.tar.gz` | `<hash_map>`, `<slist>`, iostreams (`libstlport_gcc.a`) |
| `xerces-c-src_2_8_0.tar.gz` | config XML parsing (`SXml.cpp`) |
| `cppunit-1.8.0.tar.gz` | unit tests (`CppUnit::TextUi::TestRunner`) |

They are compiled by `setup-woody-toolchain.sh` at image build time (see `Dockerfile.woody`).

---

## Current status

- ✅ Build image `darkeden-woody:test` (436MB) — toolchain 100% offline
- ✅ All binaries compiled: `loginserver`, `sharedserver`, `gameserver`, `updateserver`, `update`
- ✅ MySQL 4.1 with the real `DARKEDEN` / `USERINFO` database import pipeline
- ✅ Servers run: loginserver (9999), sharedserver (9977), gameserver (9998) — 157 zones
- ℹ️ updateserver: compiled but **not used** (optional)
- ℹ️ Data: English variant in use (see [Appendix](APPENDIX.md))

---

## Feedback / suggestions

Suggestions, corrections and improvements are very welcome — open an **issue** or a **pull
request**. If you find anything wrong, outdated or missing in this documentation (scripts,
dependencies, third-party), please report it so we can keep it accurate.

---

## Appendix

The detailed step-by-step, milestones, confs and troubleshooting were moved to
**[APPENDIX.md](APPENDIX.md)** (Portuguese: **[APPENDIX.pt.md](APPENDIX.pt.md)**) to keep this
README concise.
