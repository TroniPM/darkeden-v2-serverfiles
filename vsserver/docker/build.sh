#!/bin/bash
# =====================================================================
# build.sh - compila o DarkEden server DENTRO do container woody
# ---------------------------------------------------------------------
# Ambiente: Debian 3.0 (woody) + gcc-2.95.4 + STLport 4.6.2 + xerces 2.8
# USO (dentro do container): bash /src/docker/build.sh
#
# A toolchain (lua, STLport+lib, xerces, cppunit, patch headers) já vem
# instalada na imagem pelo setup-woody-toolchain.sh (Dockerfile.woody).
# Este script APENAS compila o servidor e escreve o log em build.log.
# =====================================================================
set -e

echo "======================================================================"
echo " Build do DarkEden server (ambiente woody - gcc-2.95.4)"
echo "======================================================================"

SRC_DIR="${SRC_DIR:-/src}"
cd "$SRC_DIR/src"

echo "==> g++: $(g++ --version | head -1)"
echo "==> Compilando em: $(pwd)"
echo ""

# ------------------------------------------------------------------
# 1. Symlink mysql (Makefiles esperam /usr/local/include/mysql)
# ------------------------------------------------------------------
mkdir -p /usr/local/include
ln -sfn /usr/include/mysql /usr/local/include/mysql 2>/dev/null || true
export CPLUS_INCLUDE_PATH="/usr/local/include/mysql:${CPLUS_INCLUDE_PATH:-}"

# ------------------------------------------------------------------
# 2. Verifica dependências (devem estar na imagem via setup)
# ------------------------------------------------------------------
echo ""
echo "==> Verificando dependências..."
OK=1
for h in /usr/include/mysql/mysql.h /usr/local/include/lua.h /usr/local/include/xercesc/util/PlatformUtils.hpp /usr/include/STL/iostream /usr/local/include/cppunit/extensions/HelperMacros.h; do
    if [ -f "$h" ]; then
        echo "    OK: $h"
    else
        echo "    FALTA: $h"
        OK=0
    fi
done
if [ ! -f /usr/local/lib/libstlport_gcc.a ]; then
    echo "    FALTA: /usr/local/lib/libstlport_gcc.a (iostreams do STLport)"
    OK=0
fi
if [ $OK -ne 1 ]; then
    echo "ERRO: dependências faltando. Rode o setup-woody-toolchain.sh na imagem."
    exit 1
fi

# ------------------------------------------------------------------
# 3. Patch dos headers (CRÍTICO para o gcc-2.95.4) - idempotente
# ------------------------------------------------------------------
echo ""
echo "==> Aplicando patch dos headers (gcc-2.95.4 ICE fix)..."
bash "$SRC_DIR/docker/patch-woody-headers.sh"

# ------------------------------------------------------------------
# 4. Build (log em build.log na raiz do repo)
# ------------------------------------------------------------------
echo ""
echo "==> Iniciando make (pode demorar - gcc-2.95 é lento)"
echo "    Log completo: $SRC_DIR/build.log"
echo ""

LOGFILE="$SRC_DIR/build.log"
BUILD_TARGET="${BUILD_TARGET:-all}"
JOBS="${JOBS:-4}"
# -O1 é necessário: sem otimização o gcc-2.95.4 volta a ter ICE
# no STLport (_threads.h:579). Com -O1 + headers patcheados compila.
CXXFLAGS="${CXXFLAGS:--O1}"
echo "    Target: $BUILD_TARGET | Jobs: $JOBS | CXXFLAGS: $CXXFLAGS"

set +e
make -C "$SRC_DIR/src" -j"$JOBS" "$BUILD_TARGET" CXXFLAGS="$CXXFLAGS" > "$LOGFILE" 2>&1
MAKE_RC=$?
set -e

# ------------------------------------------------------------------
# 5. Resumo
# ------------------------------------------------------------------
if [ $MAKE_RC -eq 0 ]; then
    echo "======================================================================"
    echo " BUILD OK! Binários em: $SRC_DIR/bin/"
    ls -la "$SRC_DIR/bin/" 2>/dev/null || echo "    (bin/ vazio)"
    echo "======================================================================"
else
    echo "======================================================================"
    echo " BUILD FALHOU (exit $MAKE_RC)"
    echo " Últimas 60 linhas do log ($LOGFILE):"
    tail -60 "$LOGFILE"
    echo "----------------------------------------------------------------------"
    echo " Dica: grep -n 'error:\|Error [0-9]' $LOGFILE | head -20"
    echo "======================================================================"
    exit $MAKE_RC
fi
