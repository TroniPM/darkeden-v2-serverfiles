#!/bin/bash
# =====================================================================
# setup-woody-toolchain.sh - instala TODA a toolchain na imagem woody
# ---------------------------------------------------------------------
# Deixa a imagem PRONTA para o build do DarkEden. Roda dentro do
# container (Dockerfile) ou manualmente.
#
# Instala:
#   - Lua 4.0.1 (headers + liblua.a + liblualib.a)  [do tarball versionado]
#   - STLport 4.6.2 headers em /usr/include/STL      [do tarball versionado]
#   - libstlport_gcc.a (iostreams do STLport)        [compilada com gcc.mak]
#   - Shim /usr/include/STL/algo.h (-> <algorithm>)  [evita g++-3/algo.h]
#   - Xerces 2.8 (headers + libxerces-c.a)           [do tarball versionado]
#   - cppunit 1.8.0 (API TextUi::TestRunner)         [do tarball versionado]
#   - Patch dos headers do gcc-2.95.4 (ICE fix)
#
# IMPORTANTE: sem "|| true" — qualquer falha ABORTA (não mascarar erros).
# =====================================================================
set -e

THIRDPARTY="${1:-/src/docker/thirdparty}"
echo "======================================================================"
echo " Setup da toolchain woody (gcc-2.95.4 + libs da época)"
echo " Tarballs: $THIRDPARTY"
echo "======================================================================"

# ------------------------------------------------------------------
# 0. Pré-requisitos de rede/tarballs
# ------------------------------------------------------------------
for t in lua-4.0.1.tar.gz STLport-4.6.2.tar.gz xerces-c-src_2_8_0.tar.gz cppunit-1.8.0.tar.gz; do
    if [ ! -f "$THIRDPARTY/$t" ]; then
        echo "ERRO: tarball faltando: $THIRDPARTY/$t"
        exit 1
    fi
done
echo "==> Todos os tarballs presentes em $THIRDPARTY"

# ------------------------------------------------------------------
# 1. Lua 4.0.1 (API Lua 4 usada pelo código)
# ------------------------------------------------------------------
if [ ! -f /usr/local/include/lua.h ]; then
    echo "==> Instalando Lua 4.0.1..."
    mkdir -p /tmp/setup-lua
    cd /tmp/setup-lua
    tar xzf "$THIRDPARTY/lua-4.0.1.tar.gz"
    cd lua-4.0.1
    make all > /tmp/setup-lua.log 2>&1
    mkdir -p /usr/local/include /usr/local/lib
    cp include/lua.h include/lualib.h include/lauxlib.h /usr/local/include/
    cp lib/liblua.a lib/liblualib.a /usr/local/lib/
    echo "==> Lua 4.0.1 instalado (headers + liblua.a + liblualib.a)"
else
    echo "==> Lua 4.0.1 já presente"
fi

# ------------------------------------------------------------------
# 2. STLport 4.6.2 headers em /usr/include/STL
# ------------------------------------------------------------------
if [ ! -f /usr/include/STL/iostream ]; then
    echo "==> Instalando STLport 4.6.2 headers..."
    mkdir -p /usr/include/STL
    tar xzf "$THIRDPARTY/STLport-4.6.2.tar.gz" -C /tmp
    cp -r /tmp/STLport-4.6.2/stlport/* /usr/include/STL/
    echo "==> STLport headers: $(ls /usr/include/STL | wc -l) arquivos"
else
    echo "==> STLport headers já presentes"
fi

# ------------------------------------------------------------------
# 3. Shim <algo.h> (header antigo do SGI STL)
#    Sem ele o gcc-2.95 resolve para /usr/include/g++-3/algo.h (quebra)
# ------------------------------------------------------------------
if [ ! -f /usr/include/STL/algo.h ]; then
    echo "==> Criando shim /usr/include/STL/algo.h..."
    cat > /usr/include/STL/algo.h << 'SHIM_EOF'
// Shim do STLport para compatibilidade com o codigo antigo (2005):
// <algo.h> era o header do SGI STL; no STLport 4.6 virou <algorithm>.
#ifndef _STLP_OLD_ALGO_H
#define _STLP_OLD_ALGO_H
#include <algorithm>
#endif
SHIM_EOF
    echo "==> Shim algo.h criado"
else
    echo "==> Shim algo.h já presente"
fi

# ------------------------------------------------------------------
# 4. libstlport_gcc.a (iostreams do STLport: _STL::cout, ios_base::Init)
#    Compilada com gcc.mak (C-locale only; o gcc-linux.mak falha no glibc)
# ------------------------------------------------------------------
if [ ! -f /usr/local/lib/libstlport_gcc.a ]; then
    echo "==> Compilando libstlport_gcc.a..."
    mkdir -p /tmp/setup-stlport
    cd /tmp/setup-stlport
    tar xzf "$THIRDPARTY/STLport-4.6.2.tar.gz"
    cd STLport-4.6.2/src
    export STLPORT_DIR=/tmp/setup-stlport/STLport-4.6.2
    make -f gcc.mak all_static > /tmp/setup-stlport.log 2>&1
    cp /tmp/setup-stlport/STLport-4.6.2/lib/libstlport_gcc.a /usr/local/lib/
    echo "==> libstlport_gcc.a instalada em /usr/local/lib/"
else
    echo "==> libstlport_gcc.a já presente"
fi

# ------------------------------------------------------------------
# 5. Xerces 2.8 (API sax2 que o código usa)
# ------------------------------------------------------------------
if [ ! -f /usr/local/include/xercesc/util/PlatformUtils.hpp ]; then
    echo "==> Compilando Xerces 2.8..."
    mkdir -p /tmp/setup-xerces
    cd /tmp/setup-xerces
    tar xzf "$THIRDPARTY/xerces-c-src_2_8_0.tar.gz"
    export XERCESCROOT=/tmp/setup-xerces/xerces-c-src_2_8_0
    cd "$XERCESCROOT/src/xercesc"
    ./runConfigure -plinux -cgcc -xg++ -b32 > /tmp/setup-xerces-conf.log 2>&1
    # O xerces 2.8: o 1o make FALHA de propósito (gera headers .hpp na
    # primeira passada); o 2o make é o build real. Permitir a 1a falha.
    make -j2 > /tmp/setup-xerces-make.log 2>&1 || true
    make -j2 > /tmp/setup-xerces-make2.log 2>&1
    mkdir -p /usr/local/include /usr/local/lib
    cp -r "$XERCESCROOT/include/xercesc" /usr/local/include/
    cd "$XERCESCROOT/obj"
    ar rcs /usr/local/lib/libxerces-c.a LINUX/*.o
    echo "==> Xerces 2.8 instalado (headers + libxerces-c.a)"
else
    echo "==> Xerces 2.8 já presente"
fi

# ------------------------------------------------------------------
# 6. cppunit 1.8.0 (API CppUnit::TextUi::TestRunner do código)
# ------------------------------------------------------------------
if [ ! -f /usr/local/include/cppunit/extensions/HelperMacros.h ]; then
    echo "==> Compilando cppunit 1.8.0..."
    mkdir -p /tmp/setup-cppunit
    cd /tmp/setup-cppunit
    tar xzf "$THIRDPARTY/cppunit-1.8.0.tar.gz"
    cd cppunit-1.8.0
    ./configure --disable-doxygen --disable-shared --enable-static --prefix=/usr/local > /tmp/setup-cppunit-conf.log 2>&1
    make -j4 > /tmp/setup-cppunit-make.log 2>&1
    make install > /tmp/setup-cppunit-install.log 2>&1
    echo "==> cppunit 1.8.0 instalado"
else
    echo "==> cppunit 1.8.0 já presente"
fi

# ------------------------------------------------------------------
# 7. Patch dos headers do gcc-2.95.4 (ICE fix)
#    O gcc-2.95.4 tem ICE com funções inline com throw()/__THROW
# ------------------------------------------------------------------
echo "==> Aplicando patch dos headers (gcc-2.95.4 ICE fix)..."
if [ -f /src/docker/patch-woody-headers.sh ]; then
    bash /src/docker/patch-woody-headers.sh
else
    # fallback: mesmo patch embutido (executável standalone)
    EXCDIR=/usr/lib/gcc-lib/i386-linux/2.95.4/include
    if [ -f "$EXCDIR/exception" ]; then
        sed "s/bad_exception () { }/bad_exception ();/; s/~bad_exception () { }/~bad_exception ();/" \
            "$EXCDIR/exception" > /tmp/e.p && cp /tmp/e.p "$EXCDIR/exception"
    fi
    if [ -f "$EXCDIR/new" ]; then
        sed "s|virtual const char\* what() const throw() { return \"bad_alloc\"; }|virtual const char* what() const throw();|; \
             s/ throw (std::bad_alloc)/ throw()/g; \
             s|inline void \*operator new(size_t, void \*place) throw() { return place; }|inline void *operator new(size_t, void *place) { return place; }|; \
             s|inline void \*operator new\[\](size_t, void \*place) throw() { return place; }|inline void *operator new[](size_t, void *place) { return place; }|" \
            "$EXCDIR/new" > /tmp/n.p && cp /tmp/n.p "$EXCDIR/new"
    fi
    cd /usr/include
    for f in wchar.h stdlib.h string.h stdio.h math.h ctype.h; do
        if [ -f "$f" ]; then
            sed "s/^extern __inline /extern /; s/ __THROW//g" "$f" > /tmp/h.p && cp /tmp/h.p "$f"
        fi
    done
    echo "==> Patch embutido aplicado"
fi

echo ""
echo "======================================================================"
echo " Toolchain woody PRONTA!"
echo "   lua:     $(ls /usr/local/include/lua.h 2>/dev/null && echo OK || echo FALTA)"
echo "   stlport: $(ls /usr/include/STL/iostream 2>/dev/null && echo OK || echo FALTA)"
echo "   stlport lib: $(ls /usr/local/lib/libstlport_gcc.a 2>/dev/null && echo OK || echo FALTA)"
echo "   xerces:  $(ls /usr/local/include/xercesc/util/PlatformUtils.hpp 2>/dev/null && echo OK || echo FALTA)"
echo "   cppunit: $(ls /usr/local/include/cppunit/extensions/HelperMacros.h 2>/dev/null && echo OK || echo FALTA)"
echo "======================================================================"
