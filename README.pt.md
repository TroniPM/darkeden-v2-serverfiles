# DarkEden Server (vssource)

> 🌐 **English:** [README.md](README.md) · **Português:** [README.pt.md](README.pt.md)

Código-fonte do servidor de **DarkEden** (~2005). Este repositório contém o **server-master**
completo (`vsserver/`): código-fonte (`src/`), dados do servidor (`data/`), o banco **real**
(`sqls/`) e a infraestrutura Docker.

> 🎯 **Fluxo oficial: ambiente WOODY** (Debian 3.0 + gcc-2.95.4 + STLport 4.6.2 + xerces 2.8
> + cppunit 1.8.0) rodando **dentro do Docker**. No host basta Docker + o plugin compose.
> **Nada de build no host.**

---

## 🚀 Guia rápido (do zero)

| Passo | Comando | O que faz | Tempo (1ª vez) |
|---|---|---|---|
| 1. Docker | `./install.sh docker` | instala `docker.io` + plugin compose, adiciona seu usuário ao grupo `docker` (pede sudo 1x) | ~1min |
| 2. Imagem | `./install.sh image` | constrói `darkeden-woody:test` com a toolchain da época — **100% offline** (tarballs em `vsserver/docker/thirdparty/`) | ~10–40min |
| 3. Banco | `./install.sh mysql` | baixa `vettadock/mysql-old:4.1`, sobe `darkeden-mysql` e importa o banco **real** (tarballs + patch) | ~2–5min |
| 4. Compilar | `./build-server.sh` | roda o make dentro do container woody (target `all`) → binários em `vsserver/bin/` | ~35–40min |
| 5. Gerenciar | veja [Scripts](#scripts) | conferir o banco, recompilar, subir/parar servidores, limpar | — |

> 💡 `./install.sh` (sem argumento) prepara **TUDO exceto o build** (docker + imagem + data +
> banco — idempotente). `./build-server.sh` compila quando você quiser.

---

## Scripts

Todos os scripts ficam na raiz do projeto. São idempotentes (seguros de rodar de novo).

| Script | O que faz |
|---|---|
| `./install.sh` | prepara o ambiente inteiro (docker → imagem → data → banco). Subcomandos: `docker` · `image` · `mysql` · `build` (= `./build-server.sh`) · `wipe` (= `./wipe-all.sh`) |
| `./build-server.sh [target]` | compila via container woody (`all` por padrão; ex.: `allgameserver`) |
| `./setup-mysql.sh [start\|stop\|status\|reset\|logs\|sql]` | gerencia o MySQL 4.1 |
| `./start-servers.sh [-v]` | sobe loginserver → sharedserver → gameserver em background (PIDs em `.server-pids`, logs em `vsserver/log/`) |
| `./stop-servers.sh [-9]` | encerra os servidores (SIGTERM; `-9` força) |
| `./wipe-all.sh [code\|bd]` | limpeza total; `code` = só artefatos de build, `bd` = só banco/docker/imagens |

---

## Estrutura do repo

```
vssource/
├── install.sh / build-server.sh / setup-mysql.sh / wipe-all.sh
├── start-servers.sh / stop-servers.sh
├── vsserver/                # = server-master
│   ├── src/                 # código-fonte (Core/ = ativo; OLDCore/ = backup/paralelo)
│   ├── src/conf/            # confs: gameserver / loginserver / sharedserver / updateserver
│   ├── data/                # ⚠️ data ativa do servidor (atualmente inglês, 581 arquivos) — gitignorada
│   ├── zips/                # data-ingles.zip · data-coreano.zip (fonte da `data/`)
│   ├── sqls/                # banco real: DARKEDEN.tar.gz + USERINFO.tar.gz + patch-compat.sql
│   ├── docker/              # Dockerfile.woody + scripts internos + thirdparty/
│   └── (bin/ lib/ log/ temp/ são criados pelo build)
```

> ℹ️ `vsserver/data/` é **gitignorada** e contém a data em inglês (extraída de
> `vsserver/zips/data-ingles.zip`) — veja [Milestone 2](APPENDIX.pt.md#milestone-2--pasta-de-dados-inglês).

---

## Dependências de sistema

**Host (somente estas):**
- **Linux — base Debian/Ubuntu recomendada** (a instalação do Docker usa `apt-get`)
- **Docker** + o plugin **`docker compose` v2** (instalado/validado pelo `./install.sh docker`)
- **Internet** na primeira execução (para baixar `debian/eol:woody` e `vettadock/mysql-old:4.1`)
- `bash`, `sudo`, e seu usuário no grupo `docker`

**Todo o resto está dentro da imagem — nada a instalar no host:**
gcc-2.95.4, Lua 4.0.1, STLport 4.6.2 (+ `libstlport_gcc.a`), Xerces 2.8, cppunit 1.8.0
e o patch dos headers do gcc-2.95.4 (ICE fix).

---

## Third-party (vendido)

`vsserver/docker/thirdparty/` traz as **fontes exatas** usadas para compilar a toolchain
dentro da imagem, tornando o build da imagem **100% offline**:

| Tarball | Para quê |
|---|---|
| `lua-4.0.1.tar.gz` | API Lua 4 (`lua_open(size)`) usada pelos scripts |
| `STLport-4.6.2.tar.gz` | `<hash_map>`, `<slist>`, iostreams (`libstlport_gcc.a`) |
| `xerces-c-src_2_8_0.tar.gz` | parsing do XML de config (`SXml.cpp`) |
| `cppunit-1.8.0.tar.gz` | testes unitários (`CppUnit::TextUi::TestRunner`) |

São compilados pelo `setup-woody-toolchain.sh` na hora de construir a imagem (ver `Dockerfile.woody`).

---

## Status atual

- ✅ Imagem de build `darkeden-woody:test` (436MB) — toolchain 100% offline
- ✅ Todos os binários compilados: `loginserver`, `sharedserver`, `gameserver`, `updateserver`, `update`
- ✅ MySQL 4.1 com o pipeline de import do banco real `DARKEDEN` / `USERINFO`
- ✅ Servidores rodando: loginserver (9999), sharedserver (9977), gameserver (9998) — 157 zonas
- ℹ️ updateserver: compilado mas **não usado** (opcional)
- ℹ️ Data: variante inglês em uso (veja o [Apêndice](APPENDIX.pt.md))

---

## Feedback / sugestões

Sugestões, correções e melhorias são muito bem-vindas — abra uma **issue** ou um **pull
request**. Se você encontrar algo errado, desatualizado ou faltando nesta documentação
(scripts, dependências, third-party), reporte para mantermos tudo preciso.

---

## Apêndice

O passo a passo detalhado, milestones, confs e troubleshooting foram movidos
para **[APPENDIX.pt.md](APPENDIX.pt.md)** (inglês: **[APPENDIX.md](APPENDIX.md)**) para manter
este README conciso.
