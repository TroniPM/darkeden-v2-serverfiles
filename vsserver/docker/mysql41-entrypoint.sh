#!/bin/bash
# =====================================================================
# mysql41-entrypoint.sh - entrypoint do MySQL 4.1 (darkeden-mysql)
# ---------------------------------------------------------------------
# A imagem vettadock/mysql-old:4.1 NÃO tem entrypoint com initdb — ela
# só roda mysqld_safe. Este wrapper adiciona:
#   1. Inicializa o datadir (mysql_install_db) se estiver vazio
#   2. IMPORTA o banco REAL do servidor (FRM/MYD/MYI): extrai os tarballs
#      DARKEDEN.tar.gz + USERINFO.tar.gz da raiz de ../sqls (montado em
#      /docker-entrypoint-initdb.d, read-only → extração vai para /tmp)
#      e copia para o datadir
#   3. Sobe o mysqld em background
#   4. Aplica o patch de compatibilidade (patch-compat.sql)
#   5. Traz o mysqld de volta para foreground (fica "docker logs"-ável)
#
# ⚠️ O banco NÃO vem de dumps .sql — os dumps do opendarkeden têm schema
#    diferente do código deste servidor. A fonte é SEMPRE a pasta real.
#
# Uso: docker run ... bash /docker/mysql41-entrypoint.sh
# =====================================================================
set -e

MYSQL_HOME="/usr/local/mysql"
DATADIR="$MYSQL_HOME/data"
INITDB_DIR="/docker-entrypoint-initdb.d"
PATCH_SQL="$INITDB_DIR/patch-compat.sql"
REALDATA_FLAG="$DATADIR/.realdata-deployed"
PATCH_FLAG="$DATADIR/.patch-applied"

echo "==> [entrypoint] MySQL 4.1 (darkeden) iniciando..."

# ------------------------------------------------------------------
# 1. Datadir vazio? Inicializa (cria o banco mysql/ de sistema)
# ------------------------------------------------------------------
if [ ! -d "$DATADIR/mysql" ] || [ -z "$(ls -A "$DATADIR/mysql" 2>/dev/null)" ]; then
    echo "==> [entrypoint] Datadir vazio — rodando mysql_install_db..."
    chown -R mysql:mysql "$DATADIR" 2>/dev/null || true
    # ⚠️ mysql_install_db procura ./bin/my_print_defaults RELATIVO ao cwd
    # → precisa rodar DE /usr/local/mysql (não de scripts/)
    cd "$MYSQL_HOME"
    su mysql -s /bin/bash -c "cd $MYSQL_HOME && $MYSQL_HOME/scripts/mysql_install_db --datadir=$DATADIR" \
        || "$MYSQL_HOME/scripts/mysql_install_db" --datadir="$DATADIR" --user=mysql
    echo "==> [entrypoint] Datadir inicializado."
fi

# ------------------------------------------------------------------
# 2. Importa o banco REAL (FRM/MYD/MYI) — 1ª subida apenas
#    Fonte: tarballs DARKEDEN.tar.gz + USERINFO.tar.gz na raiz de
#    vsserver/sqls/ ($INITDB_DIR). Como o mount é READ-ONLY, a extração
#    vai para /tmp/realdb e de lá copia para o datadir.
# ------------------------------------------------------------------
if [ ! -f "$REALDATA_FLAG" ]; then
    REALTMP_DIR="/tmp/realdb"
    rm -rf "$REALTMP_DIR"
    mkdir -p "$REALTMP_DIR"

    # Extrai os tarballs (cada um contém a pasta do banco: DARKEDEN/, USERINFO/)
    if [ -f "$INITDB_DIR/DARKEDEN.tar.gz" ]; then
        echo "==> [entrypoint] Extraindo $INITDB_DIR/DARKEDEN.tar.gz ..."
        ( cd "$REALTMP_DIR" && tar -xzf "$INITDB_DIR/DARKEDEN.tar.gz" )
    fi
    if [ -f "$INITDB_DIR/USERINFO.tar.gz" ]; then
        echo "==> [entrypoint] Extraindo $INITDB_DIR/USERINFO.tar.gz ..."
        ( cd "$REALTMP_DIR" && tar -xzf "$INITDB_DIR/USERINFO.tar.gz" )
    fi

    if [ ! -d "$REALTMP_DIR/DARKEDEN" ] || [ ! -d "$REALTMP_DIR/USERINFO" ]; then
        echo "!! [entrypoint] ERRO: banco real não encontrado."
        echo "!! [entrypoint] Esperado: DARKEDEN.tar.gz e USERINFO.tar.gz"
        echo "!! [entrypoint] na raiz de vsserver/sqls/ (montado em $INITDB_DIR)"
        exit 1
    fi

    echo "==> [entrypoint] Copiando banco REAL (FRM/MYD/MYI) para o datadir..."
    rm -rf "$DATADIR/DARKEDEN" "$DATADIR/USERINFO"
    cp -a "$REALTMP_DIR/DARKEDEN" "$DATADIR/"
    cp -a "$REALTMP_DIR/USERINFO" "$DATADIR/"
    # Remove arquivos temporários de ALTER antigos (não são tabelas)
    rm -f "$DATADIR/DARKEDEN"/#sql-*.frm
    chown -R mysql:mysql "$DATADIR/DARKEDEN" "$DATADIR/USERINFO"
    touch "$REALDATA_FLAG"
    echo "==> [entrypoint] Banco real importado: DARKEDEN=$(ls "$DATADIR/DARKEDEN" | wc -l) arquivos, USERINFO=$(ls "$DATADIR/USERINFO" | wc -l)"
else
    echo "==> [entrypoint] Banco real já importado (flag existe)."
fi

# ------------------------------------------------------------------
# 3. Sobe o mysqld em background (socket em /tmp/mysql.sock)
# ------------------------------------------------------------------
echo "==> [entrypoint] Subindo mysqld..."
"$MYSQL_HOME/bin/mysqld_safe" --user=mysql --datadir="$DATADIR" \
    --socket=/tmp/mysql.sock --port=3306 >/tmp/mysqld_safe.log 2>&1 &
MYSQLD_PID=$!

# Aguarda o mysqld responder
echo "==> [entrypoint] Aguardando mysqld ficar pronto..."
for i in $(seq 1 60); do
    if "$MYSQL_HOME/bin/mysqladmin" --socket=/tmp/mysql.sock -uroot ping >/dev/null 2>&1; then
        echo "==> [entrypoint] mysqld pronto!"
        break
    fi
    if ! kill -0 "$MYSQLD_PID" 2>/dev/null; then
        echo "!! [entrypoint] mysqld morreu. Log:"
        tail -20 /tmp/mysqld_safe.log
        exit 1
    fi
    sleep 1
done

# ------------------------------------------------------------------
# 4. Patch de compatibilidade (1ª subida — flag protege re-execução)
#    ⚠️ charset latin1 explícito: o cliente do container não carrega a
#    tabela de charsets e imprime lixo sem isso.
# ------------------------------------------------------------------
if [ -f "$PATCH_SQL" ]; then
    if [ ! -f "$PATCH_FLAG" ]; then
        echo "==> [entrypoint] Aplicando patch de compatibilidade ($(basename "$PATCH_SQL"))..."
        if "$MYSQL_HOME/bin/mysql" --default-character-set=latin1 --socket=/tmp/mysql.sock -uroot < "$PATCH_SQL" 2>&1 | tee /tmp/patch-compat.log; then
            touch "$PATCH_FLAG"
            echo "==> [entrypoint] Patch aplicado."
        else
            echo "!! [entrypoint] Patch FALHOU — ver /tmp/patch-compat.log"
            echo "!! [entrypoint] Vai tentar de novo no próximo start (não marca a flag)."
        fi
    else
        echo "==> [entrypoint] Patch já aplicado (flag existe)."
    fi
else
    echo "!! [entrypoint] Aviso: $PATCH_SQL não encontrado — sem patch de compatibilidade!"
fi

# Usuário + senha antiga + limpeza de anônimos: garantia extra, roda sempre
"$MYSQL_HOME/bin/mysql" --default-character-set=latin1 --socket=/tmp/mysql.sock -uroot -e \
    "GRANT ALL PRIVILEGES ON DARKEDEN.* TO 'elcastle'@'%' IDENTIFIED BY 'elca110'; \
     GRANT ALL PRIVILEGES ON USERINFO.* TO 'elcastle'@'%' IDENTIFIED BY 'elca110'; \
     UPDATE mysql.user SET Password=OLD_PASSWORD('elca110') WHERE User='elcastle' AND Host='%'; \
     DELETE FROM mysql.user WHERE User=''; \
     FLUSH PRIVILEGES;" 2>/dev/null \
    || echo "    !! Aviso: não conseguiu ajustar senha/usuários anônimos"

echo "==> [entrypoint] MySQL 4.1 pronto. Esperando..."
echo "    Root: sem senha (docker exec) | Usuário server: elcastle/elca110"

# ------------------------------------------------------------------
# 5. Fica em foreground (espera o mysqld, mantém logs no docker)
# ------------------------------------------------------------------
wait "$MYSQLD_PID"
