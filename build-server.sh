#!/bin/bash
# =====================================================================
# build-server - compila o DarkEden server via container WOODY
# ---------------------------------------------------------------------
# Rodado DE FORA do docker (na raiz do projeto) — o usuário NÃO precisa
# saber nada de docker. Este script faz a mágica: sobe um container com
# a imagem darkeden-woody:test (gcc-2.95.4 + toolchain da época) e roda
# o make lá dentro, com o código montado de vsserver/src.
#
# USO:
#   ./build-server.sh          # compila (padrão: target all)
#   ./build-server.sh <target> # outro target (allgameserver, allloginserver...)
#
# Pré-requisito: ./install.sh (cria a imagem darkeden-woody:test)
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DOCKER_DIR="$REPO_DIR/vsserver/docker"
IMAGE="darkeden-woody:test"
CONTAINER="darkeden-build"
TARGET="${1:-all}"

echo "======================================================================"
echo " DarkEden server - build via container woody (gcc-2.95.4)"
echo " Repo   : $REPO_DIR"
echo " Target : $TARGET"
echo "======================================================================"

# ------------------------------------------------------------------
# 0. Verificações
# ------------------------------------------------------------------
if ! docker info >/dev/null 2>&1; then
    echo "ERRO: docker não acessível. Rode: ./install.sh docker"
    exit 1
fi
if ! docker image inspect "$IMAGE" >/dev/null 2>&1; then
    echo "ERRO: imagem $IMAGE não existe. Rode: ./install.sh image"
    exit 1
fi

# ------------------------------------------------------------------
# 0.5 Limpeza de containers órfãos de builds anteriores
#    Se um build anterior foi interrompido (Ctrl+C, kill, crash), o
#    container pode ter ficado para trás (rodando ou parado). Limpamos
#    todos os containers com a imagem woody que não sejam o atual.
# ------------------------------------------------------------------
echo "==> Limpando containers órfãos de builds anteriores..."
ORPHANS="$(docker ps -aq --filter "ancestor=$IMAGE" | grep -v "$(docker ps -aq --filter "name=$CONTAINER" 2>/dev/null || true)" 2>/dev/null || true)"
if [ -n "$ORPHANS" ]; then
    docker rm -f $ORPHANS >/dev/null 2>&1 || true
    echo "    removidos: $(echo "$ORPHANS" | wc -l) container(s)"
else
    echo "    nada a limpar"
fi
# Garante que o container com nome fixo não existe (de build anterior)
docker rm -f "$CONTAINER" >/dev/null 2>&1 || true

# ------------------------------------------------------------------
# 1. Cria pastas de saída (bin/lib/log/temp) antes do container —
#    senão o make pode criar com dono root e o usuário não consegue
#    apagar depois (permissão negada).
# ------------------------------------------------------------------
mkdir -p "$REPO_DIR/vsserver/bin" "$REPO_DIR/vsserver/lib" "$REPO_DIR/vsserver/log" "$REPO_DIR/vsserver/temp"

# ------------------------------------------------------------------
# 2. Roda o build dentro do container woody
#    - Nome FIXO (darkeden-build) para fácil identificação e limpeza
#    - Monta vsserver/ em /src (código + conf + data + docker/)
#    - O container roda docker/build.sh (make com target e jobs)
#    - Log sai em vsserver/build.log (sobrevive ao --rm)
#    - --rm: remove o container ao final (sucesso OU erro)
# ------------------------------------------------------------------
echo ""
echo "==> Compilando (target: $TARGET | jobs: $(nproc))..."
echo "    Log completo: vsserver/build.log"
echo ""

# usa trap para garantir remoção mesmo se interrompido (Ctrl+C)
cleanup() {
    docker rm -f "$CONTAINER" >/dev/null 2>&1 || true
}
trap cleanup EXIT

docker run --rm --name "$CONTAINER" \
    -v "$REPO_DIR/vsserver":/src \
    -e SRC_DIR=/src \
    -e BUILD_TARGET="$TARGET" \
    -e JOBS="$(nproc)" \
    "$IMAGE" \
    bash /src/docker/build.sh

echo ""
echo "======================================================================"
echo " Processo finalizado. Binários em: vsserver/bin/"
ls -la "$REPO_DIR/vsserver/bin/" 2>/dev/null || true
echo "======================================================================"
