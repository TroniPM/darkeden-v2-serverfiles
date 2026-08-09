#!/bin/bash
# =====================================================================
# wipe-all - apaga TUDO do DarkEden server (build + banco + imagem)
# ---------------------------------------------------------------------
# USO:
#   ./wipe-all.sh            # apaga TUDO (build + banco/docker + imagem)
#   ./wipe-all.sh code       # apaga só os arquivos de build (.o/.d/.a, bin/...)
#   ./wipe-all.sh bd         # apaga só banco/docker (container, dados, imagem)
#
# ⚠️ O modo completo apaga os dados do banco (mysql-data/). Na próxima
#    subida (./setup-mysql.sh) os tarballs de sqls/ são reimportados do zero.
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$REPO_DIR"

# ------------------------------------------------------------------
# 0. Modo
# ------------------------------------------------------------------
DO_CODE=0
DO_BD=0
case "${1:-}" in
    code) DO_CODE=1 ;;
    bd)   DO_BD=1 ;;
    "")
        DO_CODE=1
        DO_BD=1
        ;;
    *)
        echo "Uso: $0 [code|bd]"
        echo "  (sem parâmetro = apaga TUDO; code = build; bd = banco/docker)"
        exit 1
        ;;
esac

if [ "$DO_CODE" -eq 1 ] && [ "$DO_BD" -eq 1 ]; then
    MODE="TUDO"
elif [ "$DO_CODE" -eq 1 ]; then
    MODE="CÓDIGO (build)"
else
    MODE="BANCO (docker)"
fi

echo "======================================================================"
echo " WIPE - DarkEden server  (modo: $MODE)"
echo " Repo: $REPO_DIR"
echo "======================================================================"

# ------------------------------------------------------------------
# 1. Para os servidores (se estiverem rodando)
# ------------------------------------------------------------------
echo ""
echo "==> [1/3] Parando servidores (se estiverem no ar)..."
pkill -f "bin/loginserver" 2>/dev/null || true
pkill -f "bin/sharedserver" 2>/dev/null || true
pkill -f "bin/gameserver"  2>/dev/null || true
rm -f .server-pids 2>/dev/null || true
echo "  OK"

# ------------------------------------------------------------------
# 2. Artefatos de build (modo: code)
# ------------------------------------------------------------------
if [ "$DO_CODE" -eq 1 ]; then
    echo ""
    echo "==> [2/3] Apagando artefatos de build..."
    find vsserver/src -name "*.o" -delete 2>/dev/null || true
    find vsserver/src -name "*.d" -delete 2>/dev/null || true
    find vsserver/src -name "*.a" -delete 2>/dev/null || true
    find vsserver/src -name "*.so" -delete 2>/dev/null || true
    find vsserver/src -type d -name ".deps" -exec rm -rf {} + 2>/dev/null || true
    # Deleta as pastas DE VEZ (o build recria com o dono correto)
    rm -rf vsserver/bin vsserver/lib vsserver/log vsserver/temp
    rm -f vsserver/build.log 2>/dev/null || true
    echo "  OK (src limpo; bin/, lib/, log/, temp/ DELETADOS - o build recria)"
else
    echo ""
    echo "==> [2/3] PULADO (use 'code' para apagar artefatos de build)"
fi

# ------------------------------------------------------------------
# 3. Banco/docker (modo: bd)
# ------------------------------------------------------------------
if [ "$DO_BD" -eq 1 ]; then
    echo ""
    echo "==> [3/3] Jogando fora Docker (container, volume, imagem woody)..."
    cd vsserver/docker
    docker compose down --remove-orphans 2>/dev/null || true
    docker rm -f darkeden-mysql 2>/dev/null || true
    # Os arquivos do MySQL dentro de mysql-data/ pertencem ao root
    # (criados pelo container). rm normal falha com permissão negada,
    # então tenta primeiro sem sudo e usa sudo como fallback.
    if ! rm -rf mysql-data 2>/dev/null; then
        echo "  ⚠️  mysql-data/ tem arquivos do root — usando sudo para apagar"
        echo "      (vai pedir a senha)"
        sudo rm -rf mysql-data
    fi
    docker rmi -f vettadock/mysql-old:4.1 2>/dev/null || true
    docker rmi -f darkeden-woody:test 2>/dev/null || true
    cd "$REPO_DIR"
    echo "  OK (sem container, sem dados do banco, sem imagens)"
else
    echo ""
    echo "==> [3/3] PULADO (use 'bd' para apagar banco/docker)"
fi

# ------------------------------------------------------------------
# 4. Resumo
# ------------------------------------------------------------------
echo ""
echo "======================================================================"
echo " PRONTO."
if [ "$DO_CODE" -eq 1 ] && [ "$DO_BD" -eq 1 ]; then
    echo "  - vsserver/src/     : sem .o/.d/.a/.so/.deps"
    echo "  - vsserver/bin lib log temp : DELETADOS (o build-server recria)"
    echo "  - docker/           : sem mysql-data, sem container, sem imagens"
    echo "  - sqls/             : INTACTOS (DARKEDEN.tar.gz, USERINFO.tar.gz, patch-compat.sql)"
    echo ""
    echo " Para recomeçar:"
    echo "   ./install.sh            # prepara TUDO de novo"
    echo "   ./setup-mysql.sh        # só o banco"
    echo "   ./build-server.sh all   # só o build"
elif [ "$DO_CODE" -eq 1 ]; then
    echo "  CÓDIGO limpo (servidores parados + artefatos de build apagados)."
    echo "  Docker/banco intactos. Rebuild: ./build-server.sh all"
else
    echo "  BANCO limpo (servidores parados + docker zerado)."
    echo "  Build intacto. Banco: ./setup-mysql.sh"
fi
echo "======================================================================"
