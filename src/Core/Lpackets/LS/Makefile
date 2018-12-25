#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
VSHOME  = ../../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = $(VSHOME)/src/Core
SERVDIR = $(VSHOME)/src/server
DBDIR   = $(SERVDIR)/database
GSDIR   = $(SERVDIR)/gameserver
LSDIR   = $(SERVDIR)/loginserver
SSDIR   = $(SERVDIR)/sharedserver
SKILLDIR= $(GSDIR)/skill
ITEMDIR = $(GSDIR)/item
BILLINGDIR = $(GSDIR)/billing


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__LOGIN_SERVER__ 
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(ITEMDIR) -I$(BILLINGDIR)

CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

TARGET_GS  = $(LIBDIR)/libGameServerPackets.a
TARGET_LS  = $(LIBDIR)/libLoginServerPackets.a
TARGET_SS  = $(LIBDIR)/libSharedServerPackets.a

TARGET = $(TARGET_LS)

include ../OBJS

.cpp.o : 
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

all : $(TARGET)

$(TARGET) : $(OBJS)
	ar r $@ $(OBJS)

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o

depall :
	gccmakedep	$(SRCS) $(INCLUDES) $(DEFS)

dep :
	gccmakedep	$(SRCS) $(INCLUDES) $(DEFS)

# DO NOT DELETE
LCCreatePCError.o: LCCreatePCError.cpp LCCreatePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCCreatePCErrorHandler.o: LCCreatePCErrorHandler.cpp LCCreatePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCCreatePCOK.o: LCCreatePCOK.cpp LCCreatePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCCreatePCOKHandler.o: LCCreatePCOKHandler.cpp LCCreatePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCError.o: LCDeletePCError.cpp LCDeletePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCErrorHandler.o: LCDeletePCErrorHandler.cpp LCDeletePCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCOK.o: LCDeletePCOK.cpp LCDeletePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCDeletePCOKHandler.o: LCDeletePCOKHandler.cpp LCDeletePCOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginError.o: LCLoginError.cpp LCLoginError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginErrorHandler.o: LCLoginErrorHandler.cpp LCLoginError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginOK.o: LCLoginOK.cpp LCLoginOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCLoginOKHandler.o: LCLoginOKHandler.cpp LCLoginOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCPCList.o: LCPCList.cpp LCPCList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/PCInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCPCListHandler.o: LCPCListHandler.cpp LCPCList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/PCInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCQueryResultPlayerID.o: LCQueryResultPlayerID.cpp \
 LCQueryResultPlayerID.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCQueryResultPlayerIDHandler.o: LCQueryResultPlayerIDHandler.cpp \
 LCQueryResultPlayerID.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCQueryResultCharacterName.o: LCQueryResultCharacterName.cpp \
 LCQueryResultCharacterName.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCQueryResultCharacterNameHandler.o: \
 LCQueryResultCharacterNameHandler.cpp LCQueryResultCharacterName.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCReconnect.o: LCReconnect.cpp LCReconnect.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCReconnectHandler.o: LCReconnectHandler.cpp LCReconnect.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerError.o: LCRegisterPlayerError.cpp \
 LCRegisterPlayerError.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerErrorHandler.o: LCRegisterPlayerErrorHandler.cpp \
 LCRegisterPlayerError.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerOK.o: LCRegisterPlayerOK.cpp LCRegisterPlayerOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCRegisterPlayerOKHandler.o: LCRegisterPlayerOKHandler.cpp \
 LCRegisterPlayerOK.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCSelectPCError.o: LCSelectPCError.cpp LCSelectPCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCSelectPCErrorHandler.o: LCSelectPCErrorHandler.cpp LCSelectPCError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCServerList.o: LCServerList.cpp LCServerList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/ServerGroupInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h \
 /home/darkeden/vs/src/Core/PCInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCServerListHandler.o: LCServerListHandler.cpp LCServerList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/ServerGroupInfo.h
LCWorldList.o: LCWorldList.cpp LCWorldList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/WorldInfo.h \
 /home/darkeden/vs/src/Core/PCSlayerInfo.h \
 /home/darkeden/vs/src/Core/PCInfo.h /usr/include/STL/bitset \
 /home/darkeden/vs/src/Core/PCVampireInfo.h
LCWorldListHandler.o: LCWorldListHandler.cpp LCWorldList.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/WorldInfo.h
LCVersionCheckOK.o: LCVersionCheckOK.cpp LCVersionCheckOK.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCVersionCheckOKHandler.o: LCVersionCheckOKHandler.cpp \
 LCVersionCheckOK.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCVersionCheckError.o: LCVersionCheckError.cpp LCVersionCheckError.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LCVersionCheckErrorHandler.o: LCVersionCheckErrorHandler.cpp \
 LCVersionCheckError.h /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnection.o: LGIncomingConnection.cpp \
 LGIncomingConnection.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionHandler.o: LGIncomingConnectionHandler.cpp \
 LGIncomingConnection.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h
LGIncomingConnectionOK.o: LGIncomingConnectionOK.cpp \
 LGIncomingConnectionOK.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionOKHandler.o: LGIncomingConnectionOKHandler.cpp \
 LGIncomingConnectionOK.h /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionError.o: LGIncomingConnectionError.cpp \
 LGIncomingConnectionError.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGIncomingConnectionErrorHandler.o: \
 LGIncomingConnectionErrorHandler.cpp LGIncomingConnectionError.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGKickCharacter.o: LGKickCharacter.cpp LGKickCharacter.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
LGKickCharacterHandler.o: LGKickCharacterHandler.cpp LGKickCharacter.h \
 /home/darkeden/vs/src/Core/DatagramPacket.h \
 /home/darkeden/vs/src/Core/Packet.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h \
 /home/darkeden/vs/src/Core/SocketInputStream.h \
 /home/darkeden/vs/src/Core/Socket.h \
 /home/darkeden/vs/src/Core/SocketImpl.h \
 /home/darkeden/vs/src/Core/SocketAPI.h \
 /home/darkeden/vs/src/Core/SocketOutputStream.h \
 /home/darkeden/vs/src/Core/Datagram.h \
 /home/darkeden/vs/src/Core/PacketFactory.h
