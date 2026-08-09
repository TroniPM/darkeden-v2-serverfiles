# Woody gcc-2.95.4 ICE fix — headers patch

## RESUMO DO DIA 2 (2026-08-07 — encerrado pelo usuário)
- **VITÓRIA**: o patch dos headers destravou o gcc-2.95.4 — build do Core 100% + libs de
  pacotes + loginserver LINKADO (com libstlport_gcc + libcpsso)
- gameserver ~80% compilando; último fix aplicado: Treasure.cpp (nocreate) — NÃO relançado
- **REGRAS do usuário**: log SEMPRE via build-woody.sh → build.log (não comandos manuais);
  versionar tarballs no thirdparty/; avisar antes de sudo; não excluir sem autorização
- **A rede do container woody está BLOQUEADA** (lua.org, archive.debian.org, snapshot):
  baixar tarballs no HOST e versionar no repo

## Descoberta (2026-08-07)
O bug do `<exception>` do gcc-2.95.4 **NÃO é um ICE de frontend irreparável** — é um bug com
**funções inline com especificação de exceção** (`throw()`, `__THROW`) em headers de sistema.

## A solução que FUNCIONOU (sobrescrever headers)
Patchear os headers dentro do container woody:
1. `/usr/lib/gcc-lib/i386-linux/2.95.4/include/exception`:
   - `bad_exception () { }` → `bad_exception ();`
   - `~bad_exception () { }` → `~bad_exception ();`
2. `/usr/lib/gcc-lib/i386-linux/2.95.4/include/new`:
   - `virtual const char* what() const throw() { return "bad_alloc"; }` → `virtual const char* what() const throw();`
   - `throw (std::bad_alloc)` → `throw()`
   - placement new inline: remover `throw()` dos corpos `{ return place; }`
3. glibc headers `/usr/include/{wchar,stdlib,string,stdio,math,ctype}.h`:
   - `extern __inline ` → `extern `
   - remover ` __THROW`
4. Compilar com `-O1` (sem -O o ICE volta no STLport `_threads.h:579`)

## Resultado
- ICE eliminado — SXml.cpp compila
- Script salvo em `vsserver/docker/patch-woody-headers.sh`

## Correções de código-fonte relacionadas
- `SXml.cpp` usa `ofstream` → **deve usar `endl`**, não `eos` (a substituição global
  `<< endl` → `<< eos` foi ERRO nesse arquivo — revertido)
- **Heurística eos/endl**: arquivos que usam a CLASSE `StringStream` → `eos`;
  quem só usa `ofstream`/`cout` → `endl`. 565 corrigidos p/ eos, 2245 p/ endl.
- `Statement.cpp` (database + theoneserver) e `SXml.cpp`: adicionar `#include <stdarg.h>`

## Link (fase 2)
- `libcpsso.a` = cópia de `libCSAuth.a` (o Makefile do loginserver espera esse nome)
- **14 libs 64-bit residuais do build gcc-11** causavam "File format not recognized" →
  removidas; `.o` antigos também (rebuild limpo 32-bit)
- `libLoginServerBilling.a`/`libGameServerBilling.a` geradas por `gameserver/billing`
  que roda DEPOIS do loginserver → buildar billing antes
- **libstlport_gcc.a** (2.6MB) compilada com `gcc.mak` (C-locale; o gcc-linux.mak falha
  no c_locale_glibc) → copiada para `lib/`
- Makefiles dos 5 servidores ganharam `-lstlport_gcc` na linha LIBS (backup em /tmp/mkbackup)

## Dependências (todas versionadas em vsserver/docker/thirdparty/)
| Tarball | Fonte | Nota |
|---|---|---|
| STLport-4.6.2.tar.gz | SF | já estava |
| xerces-c-src_2_8_0.tar.gz | apache archive | já estava |
| lua-4.0.1.tar.gz | lua.org (baixado no HOST) | Dockerfile falhava (site bloqueado) |
| cppunit-1.8.0.tar.gz | sourceforge (HOST) | **1.8.0** tem `CppUnit::TextUi::TestRunner` (API do código); 1.10.2 NÃO tem |

- `build-woody.sh` agora instala automaticamente (idempotente): Lua 4.0.1, libstlport_gcc,
  cppunit 1.8.0, e o shim de `/usr/include/STL/algo.h` (→ `<algorithm>`)
- **cppunit**: código usa `CppUnit::TextUi::TestRunner` (1.8.x); TestDef.h foi revertido
  para o API original (1.10.2 tentado antes — removido do thirdparty)

## Correções de código (dia 2 - 2026-08-07)
- `Zone.cpp`: 75x `SMP.read(&var, sz)` → `(char*)&var` (STLport read só aceita char*);
  8x `| ios::nocreate` removidos
- `Treasure.cpp` + `updateserver/main.cpp`: nocreate removidos (varredura geral feita)
- **Shim `<algo.h>`**: sem ele o gcc-2.95 resolve p/ `/usr/include/g++-3/algo.h` nativo
  (stl_function.h quebra). Shim criado em /usr/include/STL/algo.h → <algorithm>
- `Slayer.cpp` PASSou após o shim

## Estado do build (fim do dia)
- **Compila**: Core inteiro, database, billing, loginserver (link OK com stlport),
  quest, test (cppunit 1.8.0 OK), grande parte do gameserver (PlayerCreature, ZoneUtil,
  AbilityBalance, Slayer, Zone...)
- **Bloqueado em**: Treasure.cpp (nocreate — CORRIGIDO, falta relançar)
- **Próximo passo (amanhã)**: relançar build-woody.sh — esperar novos erros de código
  antigo (read/nocreate padrões já mapeados)

## Padrão do bug
gcc-2.95.4 + glibc-2.2.5 ICE em: construtores inline de classes de exceção,
métodos virtuais inline com throw(), funções `extern __inline ... __THROW` da glibc.
Remove corpo inline ou especificação de exceção → ICE avança para o próximo header.
