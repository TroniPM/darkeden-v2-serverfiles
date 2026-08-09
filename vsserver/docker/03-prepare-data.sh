#!/bin/bash
# =====================================================================
# 03-prepare-data.sh - prepara a pasta de dados (vsserver/data/)
# ---------------------------------------------------------------------
# ⚠️ DECISÃO EM ABERTO (2026-08-07): qual data usar?
#   - data/data-ingles/data/   (581 arquivos, recomendada pelo README)
#   - data/data - coreano/data/ (628 arquivos, nomes EUC-KR)
#
# Enquanto não decidirmos (README → Milestone 2), este script apenas
# verifica se data/ está populada e avisa. Quando decidirmos, o passo
# de copiar entra aqui.
#
# USO: ./03-prepare-data.sh
# =====================================================================
set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DATA_DIR="$REPO_DIR/data"

echo "======================================================================"
echo " Preparando pasta de dados (vsserver/data/)"
echo "======================================================================"

if [ -d "$DATA_DIR" ] && [ -n "$(ls -A "$DATA_DIR" 2>/dev/null)" ]; then
    echo "  ✅ data/ já populada ($(ls "$DATA_DIR" | wc -l) itens)"
    exit 0
fi

echo ""
echo "  ⚠️  data/ está vazia ou não existe."
echo "  A escolha da data (inglês vs coreano) ainda está EM ABERTO —"
echo "  ver README → Milestone 2. Vamos decidir quando chegarmos lá."
echo ""
echo "  (Nada foi copiado. O servidor pode não carregar tudo até lá.)"
