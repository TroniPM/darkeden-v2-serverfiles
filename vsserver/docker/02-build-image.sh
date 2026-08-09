#!/bin/bash
# =====================================================================
# 02-build-image.sh - constrói a imagem de build WOODY do DarkEden
# ---------------------------------------------------------------------
# Cria a imagem darkeden-woody:test com TODA a toolchain da época:
#   - Debian 3.0 (woody) + gcc-2.95.4 (o compilador original)
#   - 32-bit (Intel 80386) - como o servidor original
#   - Lua 4.0.1, STLport 4.6.2 + lib, Xerces 2.8, cppunit 1.8.0
#   - Patch dos headers (ICE fix do gcc-2.95.4)
#
# Build 100% OFFLINE: os tarballs ficam em docker/thirdparty/.
# Nada é instalado no host — fica tudo DENTRO da imagem.
#
# USO: ./02-build-image.sh
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DOCKER_DIR="$REPO_DIR/docker"

echo "======================================================================"
echo " Construindo imagem de build do DarkEden server (woody - gcc-2.95.4)"
echo "======================================================================"

# Verifica docker
if ! docker info >/dev/null 2>&1; then
    echo "ERRO: docker não acessível. Rode antes: ./install docker"
    exit 1
fi

# Verifica tarballs (build 100% offline - rede do woody bloqueada)
echo "==> Verificando tarballs em thirdparty/..."
for t in lua-4.0.1.tar.gz STLport-4.6.2.tar.gz xerces-c-src_2_8_0.tar.gz cppunit-1.8.0.tar.gz; do
    if [ ! -f "$DOCKER_DIR/thirdparty/$t" ]; then
        echo "ERRO: tarball faltando: docker/thirdparty/$t"
        exit 1
    fi
done
echo "    OK: todos os tarballs presentes"

cd "$DOCKER_DIR"

# ------------------------------------------------------------------
# Constrói a imagem usando o Dockerfile.woody
# ------------------------------------------------------------------
echo "==> docker build -f Dockerfile.woody -t darkeden-woody:test ."
echo "    (pode demorar: baixa debian/eol:woody + compila lua, stlport, xerces, cppunit)"
docker build -f Dockerfile.woody -t darkeden-woody:test .

echo ""
echo "======================================================================"
echo " Imagem darkeden-woody:test criada!"
echo " Próximo passo: ./build-server  (ou ./install para TUDO)"
echo "======================================================================"
