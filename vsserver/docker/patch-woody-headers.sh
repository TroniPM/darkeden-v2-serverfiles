#!/bin/bash
# ============================================================================
# patch-woody-headers.sh
# ----------------------------------------------------------------------------
# Corrige os ICEs (Internal Compiler Error) do gcc-2.95.4 do Debian woody
# ao compilar o DarkEden com a glibc-2.2.5 + STLport.
#
# O bug: o gcc-2.95.4 tem um bug de geração de código (vtable mismatch / ICE)
# ao processar funções inline com especificação de exceção (throw()/__THROW)
# declaradas em headers de sistema:
#   - <exception>  -> bad_exception () { }  (construtor inline)
#   - <new>        -> bad_alloc::what() const throw() inline + operator new
#   - glibc        -> extern __inline ... __THROW (wchar.h, stdlib.h, etc.)
#
# Solução: sobrescrever esses headers removendo os corpos inline e as
# especificações de exceção (que não afetam ABI aqui — o jogo é linkado
# estaticamente e não usa essas funções inline da glibc).
#
# USO: rodar DENTRO do container darkeden-woody:test como root.
# ============================================================================

set -e

EXCDIR=/usr/lib/gcc-lib/i386-linux/2.95.4/include
GCC_HEADERS="$EXCDIR/exception $EXCDIR/new"

echo "=== [1/3] Patcheando headers do gcc-2.95.4 ==="

# exception: bad_exception com construtor/destrutrutor inline -> declaração
if [ -f "$EXCDIR/exception" ]; then
  sed "s/bad_exception () { }/bad_exception ();/; s/~bad_exception () { }/~bad_exception ();/" \
    "$EXCDIR/exception" > /tmp/e.p && cp /tmp/e.p "$EXCDIR/exception"
  echo "  ✅ exception (bad_exception sem corpo inline)"
fi

# new: bad_alloc::what() inline -> declaração; operator new sem throw(std::bad_alloc)
if [ -f "$EXCDIR/new" ]; then
  sed "s|virtual const char\* what() const throw() { return \"bad_alloc\"; }|virtual const char* what() const throw();|; \
       s/ throw (std::bad_alloc)/ throw()/g; \
       s|inline void \*operator new(size_t, void \*place) throw() { return place; }|inline void *operator new(size_t, void *place) { return place; }|; \
       s|inline void \*operator new\[\](size_t, void \*place) throw() { return place; }|inline void *operator new[](size_t, void *place) { return place; }|" \
    "$EXCDIR/new" > /tmp/n.p && cp /tmp/n.p "$EXCDIR/new"
  echo "  ✅ new (bad_alloc::what + operator new sem throw)"
fi

echo "=== [2/3] Patcheando headers da glibc (remover extern __inline + __THROW) ==="
cd /usr/include
for f in wchar.h stdlib.h string.h stdio.h math.h ctype.h; do
  if [ -f "$f" ]; then
    sed "s/^extern __inline /extern /; s/ __THROW//g" "$f" > /tmp/h.p && cp /tmp/h.p "$f"
    echo "  ✅ $f"
  fi
done

echo "=== [3/3] Verificação ==="
echo "  exception: $(grep -c 'bad_exception ()' "$EXCDIR/exception" 2>/dev/null || echo 0) corpo(s) inline restante(s)"
echo "  new:       $(grep -c 'throw (std::bad_alloc)' "$EXCDIR/new" 2>/dev/null || echo 0) throw(std::bad_alloc) restante(s)"
echo "  wchar.h:   $(grep -c '__inline' /usr/include/wchar.h 2>/dev/null || echo 0) __inline restante(s)"
echo ""
echo "✅ Patch de headers aplicado com sucesso."
