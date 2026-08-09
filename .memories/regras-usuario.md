# ⚠️ REGRAS DO USUÁRIO (DarkEden vssource) — LER SEMPRE

## 1. O outro projeto (darkeden-v2-sourcefiles-server-and-client) NÃO é fonte de verdade
- ❌ NÃO copiar decisões do outro projeto "porque lá funcionou".
- ✅ Usar APENAS como ÚLTIMO recurso, para conferir implementação quando um arquivo
  não compila e OLDCore também não ajuda.
- O usuário quer decisões TÉCNICAS CORRETAS, não "seguir o que já foi feito".

## 2. Exception specifications (throw) — PREFERÊNCIA DO USUÁRIO
- ❌ NÃO remover `throw(...)` só para compilar.
- ✅ O usuário QUER manter/ADICIONAR `throw(...)` — exceptions tornam a aplicação
  tolerante a falhas (não derruba o servidor).
- Se houver mismatch .h vs .cpp: ADICIONAR o throw no .cpp (e nos friends) para
  alinhar com o .h — NÃO remover do .h.
- Tratar ajustes de compilação em outro lugar (flags, etc.), preservando o throw.

## 3. Regra geral
- Perguntar/confirmar antes de alterar comportamento do código.
- Preferir preservar a semântica original do código de 2005.

## ⚠️ REGRA SUDO (2026-08-06) — IMPORTANTE
- SEMPRE que for usar um comando com `sudo` (ou que peça senha), AVISAR o usuário ANTES,
  para ele saber que será executado e digitar a senha.
- Caso contrário o sudo dá timeout (usuário não fica olhando o terminal).

## 4. ⚠️ IMPORTANTE (2026-08-06)
- SEMPRE que eu for EXCLUIR/remover algo do código apenas para compilar,
  DEVO INFORMAR o usuário ANTES e deixar ELE decidir (pode ser algo importante).
- Não assumir que "o outro projeto fez = está certo". Outro projeto é só
  referência de ÚLTIMO caso.

## 5. 🎯 FLUXO OFICIAL = WOODY (2026-08-07) — DECISÃO FINAL DO USUÁRIO
- O projeto usa SEMPRE o ambiente **woody**: Debian 3.0 + gcc-2.95.4 +
  STLport 4.6.2 + xerces 2.8 + cppunit 1.8.0 (imagem `darkeden-woody:test`).
- ❌ NUNCA sugerir/insinuar Ubuntu 22 / Ubuntu 26 / g++-11 / g++ moderno /
  shims compat_stl. Qualquer menção a esses é LIXO/desatualizado e deve ser
  REMOVIDA do projeto (scripts, README, Dockerfiles, compose).
- Toolchain woody é 100% offline (tarballs em `docker/thirdparty/`).
- Build do servidor roda DENTRO do container woody; no host só docker+compose.
- Pipeline alvo: UM script `install.sh` (prepara TUDO) + script de build +
  `wipe-all.sh`. Nada de múltiplos fluxos paralelos.
- Erros de compilação atuais (ex.: MonsterInfo.cpp) são PROBLEMA DE CÓDIGO,
  não de pipeline — resolver depois da pipeline pronta.
- ✅ PIPELINE PRONTA E VALIDADA (2026-08-07): install.sh/build-server.sh/setup-mysql.sh/wipe-all.sh
  funcionando do zero. Pendências de CÓDIGO: `libcpsso.a` (loginserver) e `-lsicuuc`
  (gameserver) — ver /memories/repo/pipeline-woody.md.
