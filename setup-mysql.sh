#!/bin/bash
# =====================================================================
# setup-mysql - prepara o MySQL 4.1 (banco do DarkEden server)
# ---------------------------------------------------------------------
# Faz TUDO do banco:
#   1. garante docker no host (./install.sh docker se faltar)
#   2. baixa a imagem vettadock/mysql-old:4.1 (1ª vez)
#   3. sobe o container darkeden-mysql
#   4. na 1ª subida, o entrypoint extrai os tarballs do banco REAL do
#      servidor (vsserver/sqls/DARKEDEN.tar.gz e USERINFO.tar.gz — FRM/MYD/MYI),
#      importa no datadir e aplica o patch de compatibilidade
#      (vsserver/sqls/patch-compat.sql)
#
# USO:
#   ./setup-mysql.sh          # prepara (baixa imagem + sobe + deploy do banco)
#   ./setup-mysql.sh stop     # para o MySQL
#   ./setup-mysql.sh status   # mostra se está de pé + bancos
#   ./setup-mysql.sh reset    # APAGA dados e recomeça do zero (arquivos reais)
#   ./setup-mysql.sh logs     # mostra os logs
#   ./setup-mysql.sh sql      # abre o cliente mysql (root sem senha)
#
# O MySQL roda no Docker (porta 3306 exposta). Dados em
# vsserver/docker/mysql-data/.
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DOCKER_DIR="$REPO_DIR/vsserver/docker"
CONTAINER="darkeden-mysql"

echo "======================================================================"
echo " MySQL 4.1 - DarkEden server"
echo "======================================================================"

# ------------------------------------------------------------------
# 0. Garante docker
# ------------------------------------------------------------------
if ! docker info >/dev/null 2>&1; then
    echo "==> Docker não acessível — preparando (./install.sh docker)..."
    bash "$REPO_DIR/install.sh" docker
fi

# ------------------------------------------------------------------
# 1. Comandos
# ------------------------------------------------------------------
cmd="${1:-start}"

case "$cmd" in
    start|preparar|setup)
        # Se o volume tem resíduos do root (inicialização interrompida),
        # avisa ANTES — o docker compose up falharia em loop.
        if [ -d "$DOCKER_DIR/mysql-data" ] && [ -n "$(ls -A "$DOCKER_DIR/mysql-data" 2>/dev/null)" ]; then
            if ! [ -r "$DOCKER_DIR/mysql-data" ]; then
                echo ""
                echo "  ⚠️  mysql-data/ tem arquivos que você não consegue ler"
                echo "      (criados por root numa inicialização anterior)."
                echo "      Isso impede o MySQL de inicializar de novo."
                echo ""
                echo "      Solução: ./setup-mysql.sh reset   (apaga e reimporta do zero)"
                echo "      (vai pedir sua senha sudo para apagar os arquivos do root)"
                echo ""
                exit 1
            fi
        fi
        # Sobe (baixa a imagem mysql-old:4.1 se não existir; importa os
        # tarballs do banco real na 1ª criação do volume; aguarda readiness)
        bash "$DOCKER_DIR/mysql.sh" start
        # Valida que os bancos existem (não só o ping) — o import dos
        # arquivos reais + patch roda DEPOIS do ping, então tenta por ~60s.
        if docker ps --format '{{.Names}}' | grep -q "^$CONTAINER$"; then
            echo ""
            echo "==> Aguardando import do banco real (DARKEDEN/USERINFO)..."
            BANCOS_OK=0
            for i in $(seq 1 30); do
                BANCOS=$(docker exec "$CONTAINER" mysql -uroot -N -e "SHOW DATABASES;" 2>/dev/null || true)
                if echo "$BANCOS" | grep -q "DARKEDEN" && echo "$BANCOS" | grep -q "USERINFO"; then
                    BANCOS_OK=1
                    break
                fi
                sleep 2
            done
            if [ "$BANCOS_OK" -eq 1 ]; then
                echo ""
                echo "  ✅ Bancos DARKEDEN e USERINFO presentes (import + patch OK)"
            else
                echo ""
                echo "  ⚠️  MySQL de pé, mas os bancos DARKEDEN/USERINFO não apareceram."
                echo "      O import dos tarballs pode ter falhado. Veja: ./setup-mysql.sh logs"
                echo "      Para recomeçar: ./setup-mysql.sh reset"
            fi
        fi
        ;;
    stop)
        bash "$DOCKER_DIR/mysql.sh" stop
        ;;
    status)
        if docker ps --format '{{.Names}}' | grep -q "^$CONTAINER$"; then
            echo "  ✔ MySQL 4.1 de pé (container $CONTAINER)"
            echo "  Bancos:"
            docker exec "$CONTAINER" mysql --default-character-set=latin1 -uroot -e "SHOW DATABASES;" 2>/dev/null || echo "    (não respondeu ainda — rode ./setup-mysql.sh logs)"
        else
            echo "  ✘ MySQL parado. Rode: ./setup-mysql.sh"
        fi
        ;;
    reset)
        echo "==> Apagando dados e recomeçando do zero (tarballs reais + patch)..."
        echo ""
        echo "  ⚠️  Se o volume tiver arquivos do root, vai pedir a senha sudo"
        echo "      para apagar vsserver/docker/mysql-data/. Digite e aguarde."
        echo ""
        bash "$DOCKER_DIR/mysql.sh" rm
        bash "$DOCKER_DIR/mysql.sh" start
        ;;
    logs)
        bash "$DOCKER_DIR/mysql.sh" logs
        ;;
    sql)
        bash "$DOCKER_DIR/mysql.sh" sql
        ;;
    *)
        echo "Uso: $0 [start|stop|status|reset|logs|sql]"
        echo "  (sem argumento = start: baixa imagem + sobe + importa SQLs)"
        exit 1
        ;;
esac
