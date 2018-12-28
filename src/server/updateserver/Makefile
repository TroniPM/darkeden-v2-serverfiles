#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Directories Setting
#----------------------------------------------------------------------
VSHOME   = ../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../..
COREDIR  = ../../Core
SERVDIR  = ..
DBDIR    = ../database


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__UPDATE_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS     = -L$(LIBDIR) -lUpdateServerPackets -lServerCore -lCore
SYSLIBS  = -lpthread -lnsl

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS   = main.o UpdateServer.o UpdateServerPlayer.o
SRCS   = $(OBJS:.o=.cpp)
TARGET = $(BINDIR)/updateserver
UPDATE = $(BINDIR)/update

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET) $(UPDATE)

$(TARGET) : $(OBJS) $(LIBDIR)/libUpdateServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS)

$(UPDATE) : update.o $(LIBDIR)/libCore.a
	$(CC) -o $@ update.o -L$(LIBDIR) -lCore

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET) $(UPDATE)

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
main.o: main.cpp ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h UpdateServer.h \
 ../../Core/Properties.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../../Core/ServerSocket.h \
 ../../Core/SocketImpl.h ../../Core/SocketAPI.h ../../Core/Socket.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h /usr/include/dirent.h \
 /usr/include/bits/dirent.h /usr/include/sys/stat.h \
 /usr/include/bits/stat.h /usr/include/sys/resource.h \
 /usr/include/bits/resource.h ../../Core/UpdateManager.h \
 ../../Core/Update.h ../../Core/UpdateDef.h ../../Core/Assert.h \
 ../../Core/SocketInputStream.h ../../Core/SocketOutputStream.h \
 ../../Core/Resource.h ../../Core/ResourceManager.h
UpdateServer.o: UpdateServer.cpp /usr/include/c++/7/fstream \
   \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/time.h /usr/include/i386-linux-gnu/bits/time.h /usr/include/signal.h \
 /home/darkeden/src/libs/sigset.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h \
 /usr/include/asm/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h /usr/include/stdio.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h /usr/include/fcntl.h \
 /usr/include/bits/fcntl.h /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/c++/7/backward/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_algobase.h \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /usr/include/string.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h /usr/include/stdlib.h \
 /usr/include/alloca.h \
 /home/darkeden/src/libs/new.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /home/darkeden/src/libs/stl_iterator_base.h /home/darkeden/src/libs/stl_iterator.h \
 /home/darkeden/src/libs/stl_alloc.h /usr/include/assert.h \
 /home/darkeden/src/libs/stl_construct.h /home/darkeden/src/libs/stl_tempbuf.h \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /home/darkeden/src/libs/stl_uninitialized.h /usr/include/c++/7/bits/stl_function.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_fun.h \
 /home/darkeden/src/libs/stl_hash_map.h UpdateServer.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/include/ctype.h /usr/include/c++/7/functional \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /usr/include/c++/7/memory /home/darkeden/src/libs/stl_raw_storage_iter.h \
 /usr/include/c++/7/algorithm /usr/include/c++/7/bits/char_traits.h \
 ../../Core/types/PlayerTypes.h ../../Core/types/ObjectTypes.h \
 ../../Core/types/CreatureTypes.h ../../Core/types/ItemTypes.h \
 ../../Core/types/ZoneTypes.h ../../Core/types/QuestTypes.h \
 ../../Core/types/ShopTypes.h ../../Core/types/GuildTypes.h \
 ../../Core/types/WarTypes.h ../../Core/types/ServerType.h \
 ../../Core/Utility.h ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 ../../Core/Properties.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../../Core/ServerSocket.h \
 ../../Core/SocketImpl.h ../../Core/SocketAPI.h ../../Core/Socket.h \
 ../../Core/Assert.h ../SystemAPI.h UpdateServerPlayer.h \
 ../../Core/Player.h ../../Core/PlayerStatus.h /usr/include/STL/deque \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_deque.h \
 ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/SocketOutputStream.h ../Timeval.h /usr/include/i386-linux-gnu/sys/time.h \
 /usr/include/c++/7/bitset
UpdateServerPlayer.o: UpdateServerPlayer.cpp UpdateServerPlayer.h \
 ../../Core/Player.h ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 ../../Core/PlayerStatus.h /usr/include/STL/deque \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_deque.h \
 ../../Core/Packet.h ../../Core/SocketInputStream.h \
 ../../Core/Socket.h ../../Core/SocketImpl.h ../../Core/SocketAPI.h \
 ../../Core/SocketOutputStream.h ../Timeval.h /usr/include/i386-linux-gnu/sys/time.h \
 /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/7/bitset ../../Core/Assert.h \
 ../../Core/Upackets/CUBeginUpdate.h ../../Core/PacketFactory.h \
 ../../Core/UpdateManager.h ../../Core/Update.h ../../Core/UpdateDef.h \
 ../../Core/Resource.h ../../Core/ResourceManager.h \
 ../../Core/Upackets/CURequest.h ../../Core/Upackets/CUEndUpdate.h \
 ../../Core/Upackets/CURequestLoginMode.h
