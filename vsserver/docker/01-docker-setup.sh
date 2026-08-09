#!/bin/bash
# =====================================================================
# 01-docker-setup.sh - prepara o Docker no host (DarkEden server)
# ---------------------------------------------------------------------
# Instala/valida o que é necessário para rodar o build woody E o MySQL:
#   - docker.io (se ausente)
#   - plugin docker-compose-v2 (se ausente)
#   - adiciona o usuário ao grupo docker (para não precisar de sudo)
#   - valida: docker info + docker compose version
#
# USO: sudo ./01-docker-setup.sh
# =====================================================================
set -euo pipefail

echo "======================================================================"
echo " Setup Docker - DarkEden server (vssource)"
echo "======================================================================"

# ------------------------------------------------------------------
# 1. Sudo
# ------------------------------------------------------------------
if [ "$(id -u)" -ne 0 ]; then
    echo "ERRO: rode com sudo: sudo ./01-docker-setup.sh"
    exit 1
fi

# ------------------------------------------------------------------
# 2. Docker
# ------------------------------------------------------------------
if command -v docker >/dev/null 2>&1; then
    echo "==> docker já instalado: $(docker --version)"
else
    echo "==> Instalando docker.io..."
    apt-get update
    apt-get install -y --no-install-recommends docker.io
fi

# ------------------------------------------------------------------
# 3. Plugin compose
# ------------------------------------------------------------------
if docker compose version >/dev/null 2>&1; then
    echo "==> docker compose já instalado: $(docker compose version | head -1)"
else
    echo "==> Instalando plugin docker-compose-v2..."
    apt-get update
    apt-get install -y --no-install-recommends docker-compose-v2
fi

# ------------------------------------------------------------------
# 4. Grupo docker (evitar sudo em todo comando)
# ------------------------------------------------------------------
if [ -n "${SUDO_USER:-}" ]; then
    if id -nG "$SUDO_USER" | grep -qw docker; then
        echo "==> usuário $SUDO_USER já está no grupo docker"
    else
        echo "==> adicionando $SUDO_USER ao grupo docker..."
        usermod -aG docker "$SUDO_USER"
        echo "    ⚠️  Faça logout/login (ou reabra o terminal) para o grupo valer."
    fi
fi

# ------------------------------------------------------------------
# 5. Sobe o daemon se necessário
# ------------------------------------------------------------------
if ! docker info >/dev/null 2>&1; then
    echo "==> daemon docker parado — subindo (systemctl start docker)..."
    systemctl start docker 2>/dev/null || service docker start 2>/dev/null || true
fi

# ------------------------------------------------------------------
# 6. Validação final
# ------------------------------------------------------------------
echo ""
echo "==> Validação:"
docker info >/dev/null 2>&1 && echo "  ✅ docker info OK (daemon acessível)" || echo "  ❌ docker info falhou — veja se o daemon está de pé"
docker compose version >/dev/null 2>&1 && echo "  ✅ docker compose OK: $(docker compose version | head -1)" || echo "  ❌ docker compose ausente"

echo ""
echo "======================================================================"
echo " Docker pronto! Próximo passo: ./install image"
echo "======================================================================"
