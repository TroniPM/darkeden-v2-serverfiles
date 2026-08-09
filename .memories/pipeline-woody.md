# Pipeline woody (2026-08-07) — estado validado (do zero)

## Scripts da raiz (oficiais)
- `./install.sh` — TUDO (docker→imagem→data→mysql→build), idempotente, subcomandos: docker|image|mysql|build|wipe
- `./build-server.sh` — build via container woody (docker run, mount vsserver→/src, target all por padrão)
  - **Nome de container FIXO `darkeden-build`** + `--rm` + `trap cleanup EXIT` (remove mesmo com Ctrl+C)
  - **Limpa containers órfãos** da imagem woody no início (não acumula lixo)
- `./setup-mysql.sh` — start|stop|status|reset|logs|sql (baixa vettadock/mysql-old:4.1, importa banco real na 1ª subida)
  - start agora **valida os bancos DARKEDEN/USERINFO** (com retry) após o ping
  - reset avisa que pode pedir sudo (volume root)
- `./wipe-all.sh` — code (build) | bd (banco/docker) | nada (tudo)
  - bd agora tem **fallback sudo** para apagar mysql-data/ do root

## Internos (vsserver/docker/)
- `01-docker-setup.sh` (host, sudo), `02-build-image.sh` (imagem woody offline), `03-prepare-data.sh` (placeholder — data/ EM ABERTO)
- `build.sh` (container: symlink mysql + patch headers + make -O1, CXXFLAGS=-O1 obrigatório p/ ICE gcc-2.95)
- `mysql.sh` (start/stop/rm com fallback sudo), `docker-compose.yml` (mysql 4.1 porta 3306 + build woody)
- `Dockerfile.woody` — NÃO copia mais build-woody.sh (removido); build.sh é montado de fora pelo build-server.sh

## Validação completa do zero (2026-08-07)
- ✅ `./install.sh docker` → valida docker 29.1.3 + compose 2.40.3
- ✅ `./install.sh image` → construiu darkeden-woody:test do zero (toolchain completa: lua, stlport, xerces, cppunit)
- ✅ `./setup-mysql.sh` → MySQL 4.1 + bancos DARKEDEN/USERINFO importados
- ✅ `./build-server.sh` → compilou Core + gameserver + chinabilling + sharedserver; **parou no loginserver: falta `libcpsso.a`** (No rule to make target — PROBLEMA DE CÓDIGO)
- ✅ container removido após falha (--rm funcionou, nenhum órfão)
- ✅ `./wipe-all.sh bd` → apagou tudo com sudo (mysql-data root)

## 🐛 Erros de CÓDIGO pendentes (resolver quando voltarmos ao servidor)
2. **`-lsicuuc`** — gameserver falhava no link anterior: `/usr/bin/ld: cannot find -lsicuuc` (lib do MySQL moderno que o Makefile pede; no woody não existe). Ver SYSLIBS dos Makefiles.

## ✅ libcpsso RESOLVIDO (2026-08-07) — stub real
- **Problema**: `libcpsso.a` (SDK proprietária NetMarble) não existia no source; loginserver linkava `-lcpsso` (No rule to make target).
- **Solução**: `src/Core/libcpsso.cpp` — reimplementação REAL de `GetCPCookieValue()` (parser de cookie `var=val&var2=val`, aceita `&`/`;`/espaços, valor vazio → false, NULL-safe).
- **Integração**: `src/Core/Makefile` — novo alvo `CPSSO_LIB = $(LIBDIR)/libcpsso.a` (libcpsso.o) adicionado a TARGETS/SRCS; gerada no build do Core (roda antes de server/ no src/Makefile).
- **Validado**: g++ host (testes unitários: UserID/UniID/Age, separador `;`, vazio→false, NULL) + gcc-2.95 woody (compila + ar OK).
- `libcpsso.h` intacto (guard original, extern "C"). `IsNetMarble:0` → caminho NetMarble nem é compilado; stub é para fidelidade do Makefile.

## Lições / armadilhas
- **Edições via replace_string_in_file podem TRUNCAR arquivos para 0 bytes** (build.sh, docker-compose.yml, mysql.sh, settings.json ficaram vazios!). Sempre conferir `wc -c` depois de editar, e recriar via heredoc se vazio.
- Volume mysql-data criado por root → `rm -rf` falha → `sudo rm -rf` (mysql.sh/wipe-all já têm fallback; avisar usuário antes).
- Se `docker compose up` der "empty compose file" → compose foi truncado, recriar.
- gcc-2.95 é MUITO lento; build completo demora ~35-40min com JOBS=nproc. Container fica Up enquanto builda.
- Dockerfile.woody referenciava build-woody.sh (removido) → corrigido; layers em cache do docker build reutilizam a toolchain (rápido).
- Imagem = caixa de ferramentas (criada 1x, reutilizada); container = descartável (criado/destruído a cada build); binários ficam no host via bind mount.
