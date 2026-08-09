#!/bin/bash
# =====================================================================
# mysql.sh - gerencia o MySQL 4.1 (DarkEden) via Docker Compose
# ---------------------------------------------------------------------
# Uso:
#   ./mysql.sh start          # sobe o MySQL 4.1 (deploy do banco na 1a vez)
#   ./mysql.sh stop           # para o container
#   ./mysql.sh logs           # mostra os logs
#   ./mysql.sh shell          # abre um bash dentro do container
#   ./mysql.sh sql            # abre o cliente mysql (root sem senha)
#   ./mysql.sh rm             # APAGA o container + volume de dados
#
# ⚠️ MySQL 4.1 (não 5.7!) — necessário porque o cliente da imagem woody
#    (libmysqlclient 3.23) só fala o protocolo antigo. O usuário do
#    server é elcastle/elca110 (senha formato antigo/OLD_PASSWORD).
#    Root: SEM senha (docker exec).
#
# 🗄️ BANCO: na 1a subida o entrypoint IMPORTA os arquivos REAIS do servidor
#    extraindo ../sqls/DARKEDEN.tar.gz e ../sqls/USERINFO.tar.gz (FRM/MYD/MYI)
#    para o datadir, e depois aplica ../sqls/patch-compat.sql (IPs locais,
#    nomes de zona, usuário). Os dumps .sql NÃO são usados — têm schema
#    diferente deste código.
#
# Dados persistidos em: ../docker/mysql-data/
# A porta 3306 está exposta no host (bloco "ports" no docker-compose.yml).
# =====================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

cmd="${1:-start}"

if ! docker info >/dev/null 2>&1; then
    echo "ERRO: docker não está acessível. Veja BUILD.md seção 1."
    exit 1
fi

start() {
    echo "==> Subindo MySQL 4.1 (docker compose up -d mysql)..."
    docker compose up -d mysql

    echo ""
    echo "==> Aguardando MySQL ficar pronto (import do banco real na 1a vez, ~30s)..."
    for i in $(seq 1 30); do
        if docker exec darkeden-mysql mysqladmin -uroot --socket=/tmp/mysql.sock ping >/dev/null 2>&1; then
            echo "==> MySQL 4.1 PRONTO!"
            echo "    Banco: arquivos REAIS (tarballs FRM/MYD/MYI) + patch-compat.sql"
            echo "    Usuário do server: elcastle / elca110"
            echo "    Root: sem senha (docker exec)"
            return 0
        fi
        sleep 2
    done
    echo "!! Não confirmou readiness em 60s. Veja: ./mysql.sh logs"
    return 1
}

case "$cmd" in
    start)  start ;;
    stop)   docker compose stop mysql ;;
    logs)   docker compose logs --tail 50 mysql ;;
    shell)  docker exec -it darkeden-mysql bash ;;
    sql)    docker exec -it darkeden-mysql mysql -uroot darkeden ;;
    rm)
        echo "==> Removendo container mysql e dados (docker/mysql-data/)..."
        docker compose rm -sf mysql || true
        # Os arquivos do MySQL dentro de mysql-data/ pertencem ao root
        # (criados pelo container). rm normal falha com permissão negada,
        # então tenta primeiro sem sudo e usa sudo como fallback.
        if ! rm -rf "$SCRIPT_DIR/mysql-data" 2>/dev/null; then
            echo "  ⚠️  mysql-data/ tem arquivos do root — usando sudo para apagar"
            echo "      (vai pedir a senha)"
            sudo rm -rf "$SCRIPT_DIR/mysql-data"
        fi
        echo "==> Dados apagados. Para reimportar os SQLs: ./mysql.sh start"
        ;;
    *)
        echo "Uso: $0 {start|stop|logs|shell|sql|rm}"
        exit 1
        ;;
esac
