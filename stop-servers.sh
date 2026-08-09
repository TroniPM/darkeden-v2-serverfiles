#!/bin/bash
# =====================================================================
# stop-servers.sh - para os 3 servidores do DarkEden
# ---------------------------------------------------------------------
# Lê os PIDs salvos pelo start-servers.sh e os encerra.
#
# Uso:
#   ./stop-servers.sh            # para todos (SIGTERM)
#   ./stop-servers.sh -9         # força (SIGKILL)
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PIDFILE="$REPO_DIR/.server-pids"
SIGNAL="${1:-TERM}"

if [ ! -f "$PIDFILE" ]; then
    echo "Nenhum .server-pids encontrado. Os servidores foram iniciados por este script?"
    exit 1
fi

echo "======================================================================"
echo " Parando servidores (SIG$SIGNAL)..."
echo "======================================================================"

STOPPED=0
while IFS='=' read -r name pid; do
    if kill -0 "$pid" 2>/dev/null; then
        kill -"$SIGNAL" "$pid" 2>/dev/null && echo "  ⏹  $name  PID=$pid" && STOPPED=$((STOPPED+1))
    else
        echo "  - $name  PID=$pid (já morto)"
    fi
done < "$PIDFILE"

# Aguarda os processos terminarem
sleep 2

# Verifica se sobraram processos vivos
LEFT=0
while IFS='=' read -r name pid; do
    if kill -0 "$pid" 2>/dev/null; then
        echo "  ⚠️  $name PID=$pid ainda vivo"
        LEFT=$((LEFT+1))
    fi
done < "$PIDFILE"

if [ "$LEFT" -gt 0 ] && [ "$SIGNAL" != "KILL" ]; then
    echo ""
    echo "!! Alguns processos não terminaram. Forçando com SIGKILL..."
    ./stop-servers.sh -9 || true
else
    # Fallback: mata instâncias órfãs (não registradas no pidfile,
    # ex.: de runs anteriores ou do loginserver que forca filhos)
    for b in loginserver sharedserver gameserver; do
        pkill -f "bin/$b" 2>/dev/null || true
    done
    rm -f "$PIDFILE"
    echo ""
    echo "✅ Todos os servidores parados."
fi
echo "======================================================================"
# comando para pegar pid manualmente, caso o script não funcione corretamente
# ps aux | grep -E "(loginserver|sharedserver|gameserver)" | grep -v grep

# comando para parar tudo independente
# pkill -f "bin/(loginserver|sharedserver|gameserver)"

# forçar fechar
# pkill -9 -f "bin/(loginserver|sharedserver|gameserver)"