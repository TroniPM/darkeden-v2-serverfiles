#!/bin/bash
# =====================================================================
# start-servers.sh - sobe os 3 servidores do DarkEden em background
# ---------------------------------------------------------------------
# Cada servidor roda como processo FILHO deste script (mesmo pai),
# cada um com seu próprio PID.
#
# ⚠️ Antes de subir, MATA instâncias antigas dos 3 servidores (mesmo
#    que não estejam registradas no pidfile) — evita "address already
#    in use" por processos órfãos de runs anteriores.
#
# Uso (rodar da RAIZ do projeto):
#   ./start-servers.sh            # sobe loginserver -> sharedserver -> gameserver
#   ./start-servers.sh -v         # modo verboso (mostra logs de cada um)
#   ./stop-servers.sh             # para todos (script irmão)
#
# ⚠️ Este script NÃO copia os confs — os servidores rodam DE DENTRO de
#    vsserver/ (HomePath: . nos confs, que aponta para vsserver/data/).
#    Os confs usados são os de vsserver/src/conf/.
#
# 📌 PRIMEIRA VEZ / CLIENTE EM OUTRO PC — não esquecer:
#    O cliente conecta no gameserver pelo IP da tabela GameServerInfo.
#    Se estiver 127.0.0.1, o cliente (fora da VM) não conecta. Atualizar:
#      docker exec darkeden-mysql /usr/local/mysql/bin/mysql \
#        --default-character-set=latin1 --socket=/tmp/mysql.sock -uroot \
#        -e "UPDATE DARKEDEN.GameServerInfo SET IP='<IP-da-VM-na-LAN>';"
#    (VER IP com: ip -4 addr | grep inet)
#    E no cliente: loginserver = <IP-da-VM>:9999
#    Obs.: WorldDBInfo.Host fica 127.0.0.1 (uso interno servidor->MySQL).
#
# PIDs salvos em: .server-pids (usado pelo stop-servers.sh)
# Logs de cada servidor: vsserver/log/loginserver.out, ...
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SERVER_DIR="$REPO_DIR/vsserver"
cd "$SERVER_DIR"

VERBOSE=0
[ "${1:-}" = "-v" ] && VERBOSE=1

PIDFILE="$REPO_DIR/.server-pids"
LOG_DIR="$SERVER_DIR/log"
mkdir -p "$LOG_DIR"

# ------------------------------------------------------------------
# 0. Verificações
# ------------------------------------------------------------------
echo "======================================================================"
echo " Iniciando servidores DarkEden"
echo " Repo: $REPO_DIR"
echo "======================================================================"

# MySQL rodando?
if ! docker ps --format '{{.Names}}' 2>/dev/null | grep -q darkeden-mysql; then
    echo "!! MySQL não está rodando. Suba com: ./setup-mysql.sh"
    exit 1
fi

# Binários existem?
for b in loginserver sharedserver gameserver; do
    [ -f "bin/$b" ] || { echo "!! Falta bin/$b. Compile primeiro (./build-server.sh all)"; exit 1; }
done

# Confs existem?
for c in loginserver sharedserver gameserver; do
    [ -f "src/conf/$c.conf" ] || { echo "!! Falta src/conf/$c.conf"; exit 1; }
done

# Limpa PID file antigo
rm -f "$PIDFILE"

# Mata instâncias antigas que podem ter sobrado de runs anteriores
# (elas seguram as portas — sem isso o novo bind falha com
# "BindException: address already in use" e o processo morre na hora)
for b in loginserver sharedserver gameserver; do
    pkill -f "bin/$b" 2>/dev/null || true
done
sleep 1

# ------------------------------------------------------------------
# Função: sobe um servidor e espera o próximo
# ------------------------------------------------------------------
start_one() {
    local name="$1"
    local bin="$2"
    local conf="$3"
    local port="$4"
    local out="$LOG_DIR/$name.out"

    echo ""
    echo "==> Subindo $name (porta $port)..."

    # Sobe como filho deste script (background), PID próprio
    # HomePath: . nos confs → roda DE DENTRO de vsserver/ (data/ fica aqui)
    nohup "./bin/$bin" -f "src/conf/$conf.conf" > "$out" 2>&1 &
    local pid=$!
    echo "$name=$pid" >> "$PIDFILE"
    echo "    PID $pid -> $out"

    # Aguarda o processo continuar vivo (não crashar em ~3s)
    sleep 3
    if ! kill -0 "$pid" 2>/dev/null; then
        echo "!! $name morreu ao iniciar. Últimas linhas do log:"
        tail -15 "$out"
        echo "    Dica: veja README.md seção Manutenção/troubleshooting."
        return 1
    fi

    if [ "$VERBOSE" = "1" ]; then
        echo "    --- últimas linhas de $name.out ---"
        tail -5 "$out"
        echo "    ------------------------------------"
    fi
    echo "    OK: $name rodando (PID $pid)"
    return 0
}

# ------------------------------------------------------------------
# 1. loginserver (porta 9999)
# ------------------------------------------------------------------
start_one "loginserver" "loginserver" "loginserver" "9999" || exit 1

# Pequena pausa para o loginserver estabilizar antes do próximo
sleep 15

# ------------------------------------------------------------------
# 2. sharedserver (porta 9977)
# ------------------------------------------------------------------
start_one "sharedserver" "sharedserver" "sharedserver" "9977" || exit 1

sleep 15

# ------------------------------------------------------------------
# 3. gameserver (porta 9998)
# ------------------------------------------------------------------
start_one "gameserver" "gameserver" "gameserver" "9998" || exit 1

# ------------------------------------------------------------------
# 4. Resumo
# ------------------------------------------------------------------
echo ""
echo "======================================================================"
echo " Servidores no ar (todos filhos do PID $$):"
echo "======================================================================"
while IFS='=' read -r name pid; do
    if kill -0 "$pid" 2>/dev/null; then
        echo "  ✅ $name  PID=$pid  (pai=$$)"
    else
        echo "  ❌ $name  PID=$pid  (MORTO)"
    fi
done < "$PIDFILE"
echo ""
echo " Logs: $LOG_DIR/*.out"
echo " Para parar tudo: ./stop-servers.sh"
echo " Para ver processos: ps --ppid $$"
echo "======================================================================"
