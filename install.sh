#!/bin/bash
# =====================================================================
# install - PREPARA TUDO do DarkEden server (vssource)
# ---------------------------------------------------------------------
# Fluxo oficial: ambiente WOODY (Debian 3.0 + gcc-2.95.4 + STLport 4.6.2
# + xerces 2.8 + cppunit 1.8.0) rodando DENTRO do Docker.
# No host só precisa de Docker + plugin compose.
#
# USO (um comando para o leigo):
#   ./install.sh              # prepara TUDO exceto build: docker, imagem, data, banco
#   ./install.sh docker       # só prepara o docker no host (pede sudo 1x)
#   ./install.sh image        # só constrói a imagem darkeden-woody:test
#   ./install.sh mysql        # só sobe o MySQL 4.1 (baixa imagem + importa banco real)
#   ./install.sh build        # compila o servidor (target all) — mesmo que ./build-server.sh
#   ./install.sh wipe         # apaga build + banco + imagem
#
# ⚠️ O install NÃO compila o servidor (o build fica para o ./build-server.sh,
#    para o usuário ter controle de quando compilar).
#
# IDEMPOTENTE: pode rodar quantas vezes quiser — cada etapa verifica se
# já está pronta e pula. Nada quebra.
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DOCKER_DIR="$REPO_DIR/vsserver/docker"
STATE_FILE="$REPO_DIR/.install-state"

# ----------------------------------------------------------------------
# Cores (só para deixar a saída clara para o leigo)
# ----------------------------------------------------------------------
if [ -t 1 ]; then
    C_GREEN="\033[32m"; C_YELLOW="\033[33m"; C_RED="\033[31m"; C_BOLD="\033[1m"; C_RESET="\033[0m"
else
    C_GREEN=""; C_YELLOW=""; C_RED=""; C_BOLD=""; C_RESET=""
fi
ok()   { echo -e "${C_GREEN}  ✔ $1${C_RESET}"; }
info() { echo -e "${C_YELLOW}  → $1${C_RESET}"; }
err()  { echo -e "${C_RED}  ✘ $1${C_RESET}"; }
step() { echo ""; echo -e "${C_BOLD}==> $1${C_RESET}"; }

# ----------------------------------------------------------------------
# Helpers
# ----------------------------------------------------------------------
have_docker()  { command -v docker >/dev/null 2>&1 && docker info >/dev/null 2>&1; }
have_compose() { docker compose version >/dev/null 2>&1; }
have_image()   { docker image inspect darkeden-woody:test >/dev/null 2>&1; }
data_ready()   { [ -d "$REPO_DIR/vsserver/data" ] && [ -n "$(ls -A "$REPO_DIR/vsserver/data" 2>/dev/null)" ]; }

# ----------------------------------------------------------------------
# Etapas
# ----------------------------------------------------------------------

step_docker() {
    step "Etapa 1/5 — Docker no host"
    if have_docker && have_compose; then
        ok "Docker já está instalado e acessível ($(docker --version | cut -d' ' -f3 | tr -d ','))"
        ok "Plugin compose presente ($(docker compose version | head -1))"
        return 0
    fi
    info "Docker/compose ausente ou sem acesso — instalando (vai pedir sudo/senha)..."
    # REGRA DO USUÁRIO: avisar antes do sudo
    echo ""
    echo "  ⚠️  O próximo comando usa sudo para instalar o Docker."
    echo "      Será pedida a sua senha no terminal. Digite e aguarde."
    echo ""
    read -r -p "  Pressione ENTER para continuar (ou Ctrl+C para cancelar)... " _
    sudo bash "$DOCKER_DIR/01-docker-setup.sh"
    ok "Docker pronto"
}

step_image() {
    step "Etapa 2/5 — Imagem de build woody (darkeden-woody:test)"
    if have_image; then
        ok "Imagem já existe — pulando"
        return 0
    fi
    info "Imagem ausente — construindo (baixa Debian woody + compila Lua 4.0.1,"
    info "STLport 4.6.2, Xerces 2.8 e cppunit 1.8.0 — pode demorar bastante)"
    bash "$DOCKER_DIR/02-build-image.sh"
    ok "Imagem darkeden-woody:test criada"
}

step_data() {
    step "Etapa 3/5 — Pasta de dados (vsserver/data/)"
    # ⚠️ DECISÃO EM ABERTO: qual data usar (inglesa vs coreana) — ver
    #    README, Milestone 2. Enquanto não decidida, apenas avisa.
    if data_ready; then
        ok "data/ já populada ($(ls "$REPO_DIR/vsserver/data" | wc -l) itens) — pulando"
        return 0
    fi
    info "data/ está vazia."
    info "  ⚠️  A escolha da data (inglês vs coreano) ainda está EM ABERTO"
    info "      (ver README → Milestone 2). Vamos decidir quando chegarmos lá."
    info "  Continuando sem data/ — o servidor pode não carregar tudo até lá."
}

step_mysql() {
    step "Etapa 4/5 — MySQL 4.1 (banco de dados)"
    if ! have_docker; then
        err "Docker não acessível — rode ./install.sh (sem argumentos) ou ./install.sh docker"
        return 1
    fi
    if docker ps --format '{{.Names}}' | grep -q '^darkeden-mysql$'; then
        ok "MySQL 4.1 já está de pé"
        return 0
    fi
    info "Subindo MySQL 4.1 (baixa a imagem vettadock/mysql-old:4.1 e importa o"
    info "banco real dos tarballs de vsserver/sqls/ na 1ª vez + patch-compat.sql)"
    bash "$DOCKER_DIR/mysql.sh" start
    ok "MySQL 4.1 pronto"
}

step_build() {
    step "Etapa 5/5 — Compilar o servidor (target: all)"
    if ! have_docker; then
        err "Docker não acessível — rode ./install.sh docker primeiro"
        return 1
    fi
    if ! have_image; then
        err "Imagem darkeden-woody:test ausente — rode ./install.sh image primeiro"
        return 1
    fi
    bash "$REPO_DIR/build-server.sh" all
    ok "Build concluído"
}

# ----------------------------------------------------------------------
# Resumo final
# ----------------------------------------------------------------------
summary() {
    echo ""
    echo "======================================================================"
    echo " INSTALAÇÃO CONCLUÍDA ✔"
    echo "======================================================================"
    echo ""
    echo "  O que está pronto:"
    have_docker && echo "    ✔ Docker (host)" || echo "    ✘ Docker — rode: ./install.sh docker"
    have_image  && echo "    ✔ Imagem de build woody" || echo "    ✘ Imagem — rode: ./install.sh image"
    data_ready  && echo "    ✔ data/ populada" || echo "    ⚠ data/ — decisão em aberto (Milestone 2)"
    docker ps --format '{{.Names}}' 2>/dev/null | grep -q '^darkeden-mysql$' && echo "    ✔ MySQL 4.1 (banco)" || echo "    ✘ MySQL — rode: ./setup-mysql.sh"
    [ -x "$REPO_DIR/vsserver/bin/gameserver" ] && echo "    ✔ Servidor compilado (bin/)" || echo "    ✘ Servidor — rode: ./build-server.sh"
    echo ""
    echo "  Próximos passos:"
    echo "    ./build-server.sh     # compila o servidor (demora na 1ª vez)"
    echo "    ./setup-mysql.sh      # gerencia o banco (status/reset/logs)"
    echo "    ./wipe-all.sh         # apaga build/banco/imagem (limpeza total)"
    echo ""
    echo "  Binários do servidor: vsserver/bin/ (após ./build-server.sh)"
    echo "======================================================================"
}

# ----------------------------------------------------------------------
# Main — roteia o comando
# ----------------------------------------------------------------------
cmd="${1:-}"

case "$cmd" in
    "")
        step_docker
        step_image
        step_data
        step_mysql || true
        summary
        ;;
    docker)
        step_docker
        ;;
    image)
        step_docker
        step_image
        ;;
    mysql)
        step_docker
        step_mysql
        ;;
    build)
        step_docker
        step_image
        step_build
        ;;
    wipe)
        bash "$REPO_DIR/wipe-all.sh"
        ;;
    *)
        echo "Uso: $0 [docker|image|mysql|build|wipe]"
        echo "  (sem argumento = prepara o ambiente: docker + imagem + banco, SEM build)"
        exit 1
        ;;
esac
