#----------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
# Description :
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Directories Setting
#----------------------------------------------------------------------
VSHOME  = ../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
LOGDIR  = $(VSHOME)/log
SRCDIR  = ..
COREDIR = ../Core
DBDIR    = ./database


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(DBDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o : 
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#----------------------------------------------------------------------
# Server Core Library
#----------------------------------------------------------------------
SERVER_CORE_OBJS = CondVar.o LogData.o LogClient.o Mutex.o PlayerManager.o GameWorldInfoManager.o SystemAPI.o Thread.o ThreadAttr.o Timeval.o pthreadAPI.o Profile.o PacketProfile.o GameServerInfoManager.o PaySystem.o
SERVER_CORE_LIB  = $(LIBDIR)/libServerCore.a

SERVER_CORE_SRCS = $(SERVER_CORE_OBJS:.o=.cpp)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C chinabilling
	$(MAKE) -C loginserver
	$(MAKE) -C gameserver
	$(MAKE) -C updateserver
	$(MAKE) -C sharedserver

server : $(SERVER_CORE_LIB)

allgameserver : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C chinabilling
	$(MAKE) -C gameserver

allloginserver : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C chinabilling
	$(MAKE) -C loginserver

allsharedserver : $(SERVER_CORE_LIB)
	$(MAKE) -C database
	$(MAKE) -C sharedserver

alltheoneserver : $(SERVER_CORE_LIB)
	$(MAKE) -C theoneserver

$(SERVER_CORE_LIB) : $(SERVER_CORE_OBJS)
	ar rc $@ $^

clean :
	$(MAKE) -C database clean
	$(MAKE) -C chinabilling clean
	$(MAKE) -C loginserver clean
	$(MAKE) -C gameserver clean
	$(MAKE) -C updateserver clean
	$(MAKE) -C sharedserver clean
	rm -rf *.o

cleanloginserver :
	$(MAKE) -C database clean
	$(MAKE) -C chinabilling clean
	$(MAKE) -C loginserver clean
	rm -rf *.o

cleangameserver :
	$(MAKE) -C database clean
	$(MAKE) -C chinabilling clean
	$(MAKE) -C gameserver clean
	rm -rf *.o

cleansharedserver :
	$(MAKE) -C database clean
	$(MAKE) -C sharedserver clean
	rm -rf *.o

cleanall :
	$(MAKE) -C database cleanall
	$(MAKE) -C chinabilling cleanall
	$(MAKE) -C loginserver cleanall
	$(MAKE) -C gameserver cleanall
	$(MAKE) -C updateserver cleanall
	$(MAKE) -C sharedserver cleanall
	rm -rf *.o $(SERVER_CORE_LIB)

depall :
	$(MAKE) -C database depall
	$(MAKE) -C chinabilling depall
	$(MAKE) -C loginserver depall
	$(MAKE) -C gameserver depall
	$(MAKE) -C updateserver depall
	$(MAKE) -C sharedserver depall
	gccmakedep $(SERVER_CORE_SRCS) $(INCLUDES)

dep :
	gccmakedep $(SERVER_CORE_SRCS) $(INCLUDES)
# DO NOT DELETE
CondVar.o: CondVar.cpp CondVar.h CondVarAttr.h /usr/include/pthread.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/sched.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/i386-linux-gnu/bits/time.h /usr/include/signal.h \
 /home/darkeden/src/libs/sigset.h /usr/include/bits/initspin.h \
 /usr/include/bits/sigthread.h pthreadAPI.h ../Core/Exception.h \
 ../Core/Types.h ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h /usr/include/i386-linux-gnu/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/string.h /usr/include/assert.h \
 /usr/include/ctype.h /usr/include/c++/7/functional \
 /usr/include/c++/7/bits/stl_function.h /usr/include/c++/7/stdexcept \
 /home/darkeden/src/libs/stl_exception.h /home/darkeden/src/libs/stl_iterator_base.h \
 /usr/include/c++/7/memory /home/darkeden/src/libs/stl_algobase.h \
 /home/darkeden/src/libs/stl_relops.h /home/darkeden/src/libs/stl_pair.h \
 /usr/include/c++/7/ext/type_traits.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h Mutex.h Thread.h \
 LogClient.h
LogData.o: LogData.cpp /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/sys/socket.h \
 /usr/include/sys/uio.h /usr/include/bits/uio.h \
 /usr/include/bits/socket.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/sys/time.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/include/bits/wordsize.h /usr/include/bits/in.h \
 /usr/include/bits/byteswap.h /usr/include/arpa/inet.h \
 /usr/include/errno.h /usr/include/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/asm/errno.h \
 /usr/include/fcntl.h /usr/include/bits/fcntl.h /usr/include/netdb.h \
 /usr/include/rpc/netdb.h /usr/include/bits/netdb.h \
 /usr/include/signal.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
 /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h /usr/include/stdlib.h \
 /usr/include/alloca.h /usr/include/string.h /usr/include/sys/stat.h \
 /usr/include/bits/stat.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/sys/wait.h \
 /usr/include/sys/resource.h /usr/include/bits/resource.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/un.h LogData.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /home/darkeden/src/libs/stl_hash_fun.h \
 ../Core/types/PlayerTypes.h ../Core/types/ObjectTypes.h \
 ../Core/types/CreatureTypes.h ../Core/types/ItemTypes.h \
 ../Core/types/ZoneTypes.h ../Core/types/QuestTypes.h \
 ../Core/types/ShopTypes.h ../Core/types/GuildTypes.h \
 ../Core/types/WarTypes.h ../Core/types/ServerType.h ../Core/Utility.h
LogClient.o: LogClient.cpp /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/sys/socket.h \
 /usr/include/sys/uio.h /usr/include/bits/uio.h \
 /usr/include/bits/socket.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h /usr/include/bits/sockaddr.h \
 /usr/include/asm/socket.h /usr/include/asm/sockios.h \
 /usr/include/sys/time.h /usr/include/netinet/in.h \
 /usr/include/stdint.h /usr/include/i386-linux-gnu/bits/wchar.h \
 /usr/include/bits/wordsize.h /usr/include/bits/in.h \
 /usr/include/bits/byteswap.h /usr/include/arpa/inet.h \
 /usr/include/errno.h /usr/include/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/asm/errno.h \
 /usr/include/fcntl.h /usr/include/bits/fcntl.h /usr/include/netdb.h \
 /usr/include/rpc/netdb.h /usr/include/bits/netdb.h \
 /usr/include/signal.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
 /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h /usr/include/stdlib.h \
 /usr/include/alloca.h /usr/include/string.h /usr/include/sys/stat.h \
 /usr/include/bits/stat.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/sys/wait.h \
 /usr/include/sys/resource.h /usr/include/bits/resource.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/sys/un.h LogClient.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/assert.h /usr/include/ctype.h \
 /usr/include/c++/7/functional /usr/include/c++/7/bits/stl_function.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /home/darkeden/src/libs/stl_iterator_base.h /usr/include/c++/7/memory \
 /home/darkeden/src/libs/stl_algobase.h /home/darkeden/src/libs/stl_relops.h \
 /home/darkeden/src/libs/stl_pair.h /usr/include/c++/7/ext/type_traits.h \
 /home/darkeden/src/libs/new.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /home/darkeden/src/libs/stl_hash_fun.h \
 ../Core/types/PlayerTypes.h ../Core/types/ObjectTypes.h \
 ../Core/types/CreatureTypes.h ../Core/types/ItemTypes.h \
 ../Core/types/ZoneTypes.h ../Core/types/QuestTypes.h \
 ../Core/types/ShopTypes.h ../Core/types/GuildTypes.h \
 ../Core/types/WarTypes.h ../Core/types/ServerType.h ../Core/Utility.h \
 LogData.h
Mutex.o: Mutex.cpp Mutex.h /usr/include/pthread.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/sched.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/i386-linux-gnu/bits/time.h /usr/include/signal.h \
 /home/darkeden/src/libs/sigset.h /usr/include/bits/initspin.h \
 /usr/include/bits/sigthread.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h /usr/include/i386-linux-gnu/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/string.h /usr/include/assert.h \
 /usr/include/ctype.h /usr/include/c++/7/functional \
 /usr/include/c++/7/bits/stl_function.h /usr/include/c++/7/stdexcept \
 /home/darkeden/src/libs/stl_exception.h /home/darkeden/src/libs/stl_iterator_base.h \
 /usr/include/c++/7/memory /home/darkeden/src/libs/stl_algobase.h \
 /home/darkeden/src/libs/stl_relops.h /home/darkeden/src/libs/stl_pair.h \
 /usr/include/c++/7/ext/type_traits.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h MutexAttr.h pthreadAPI.h Thread.h \
 LogClient.h
PlayerManager.o: PlayerManager.cpp PlayerManager.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../Core/SocketAPI.h Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../Core/Assert.h ../Core/Socket.h ../Core/SocketImpl.h \
 ../Core/Player.h gameserver/Creature.h gameserver/Object.h \
 gameserver/EffectManager.h gameserver/Effect.h ../Core/EffectInfo.h \
 ../Core/Packet.h ../Core/SocketInputStream.h \
 ../Core/SocketOutputStream.h /usr/include/STL/bitset \
 gameserver/Slayer.h gameserver/PlayerCreature.h \
 gameserver/ObjectRegistry.h gameserver/InventorySlot.h \
 gameserver/Item.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h gameserver/Garbage.h \
 gameserver/RankBonus.h gameserver/ExpFwd.h \
 ../Core/Gpackets/GCMonsterKillQuestInfo.h ../Core/PacketFactory.h \
 ../Core/Gpackets/GCSelectQuestID.h gameserver/OptionInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /usr/include/STL/slist \
 /home/darkeden/src/libs/stl_slist.h gameserver/Zone.h gameserver/Tile.h \
 gameserver/Obstacle.h gameserver/Portal.h \
 gameserver/quest/TriggerManager.h gameserver/quest/Trigger.h \
 gameserver/quest/Condition.h gameserver/quest/PropertyBuffer.h \
 gameserver/Sector.h gameserver/Party.h ../Core/ModifyInfo.h \
 gameserver/PCManager.h gameserver/CreatureManager.h \
 ../Core/Encrypter.h ../Core/EncryptUtility.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 gameserver/Inventory.h gameserver/VolumeInfo.h ../Core/PCSlayerInfo.h \
 ../Core/PCInfo.h ../Core/PCSlayerInfo2.h ../Core/PCSlayerInfo3.h \
 ../Core/InventoryInfo.h ../Core/InventorySlotInfo.h \
 ../Core/PCItemInfo.h ../Core/SubItemInfo.h \
 gameserver/ItemLoaderManager.h gameserver/ItemLoader.h \
 ../Core/GearInfo.h ../Core/GearSlotInfo.h ../Core/ExtraInfo.h \
 ../Core/ExtraSlotInfo.h ../Core/RideMotorcycleInfo.h \
 ../Core/RideMotorcycleSlotInfo.h ../Core/SlayerSkillInfo.h \
 ../Core/PCSkillInfo.h ../Core/SubSlayerSkillInfo.h \
 gameserver/CreatureUtil.h gameserver/SlayerAttrExpTable.h \
 gameserver/SomethingGrowingUp.h database/DB.h \
 database/DatabaseManager.h database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h database/Statement.h \
 database/Result.h /usr/include/STL/cstdio \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h gameserver/skill/Skill.h \
 gameserver/skill/SkillSlot.h ../Core/Gpackets/GCModifyInformation.h
GameWorldInfoManager.o: GameWorldInfoManager.cpp \
 GameWorldInfoManager.h ../Core/Types.h ../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h GameWorldInfo.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h database/DatabaseManager.h \
 database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 database/Statement.h database/Result.h /usr/include/sys/time.h
SystemAPI.o: SystemAPI.cpp ../Core/Types.h ../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h SystemAPI.h \
 ../Core/Exception.h ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/errno.h \
 /usr/include/bits/errno.h /usr/include/linux/errno.h \
 /usr/include/asm/errno.h
Thread.o: Thread.cpp Thread.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h pthreadAPI.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ThreadAttr.h
ThreadAttr.o: ThreadAttr.cpp ThreadAttr.h /usr/include/pthread.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/sched.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/i386-linux-gnu/bits/time.h /usr/include/signal.h \
 /home/darkeden/src/libs/sigset.h /usr/include/bits/initspin.h \
 /usr/include/bits/sigthread.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h /usr/include/i386-linux-gnu/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/string.h /usr/include/assert.h \
 /usr/include/ctype.h /usr/include/c++/7/functional \
 /usr/include/c++/7/bits/stl_function.h /usr/include/c++/7/stdexcept \
 /home/darkeden/src/libs/stl_exception.h /home/darkeden/src/libs/stl_iterator_base.h \
 /usr/include/c++/7/memory /home/darkeden/src/libs/stl_algobase.h \
 /home/darkeden/src/libs/stl_relops.h /home/darkeden/src/libs/stl_pair.h \
 /usr/include/c++/7/ext/type_traits.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h pthreadAPI.h
Timeval.o: Timeval.cpp Timeval.h /usr/include/sys/time.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h \
 /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 ../Core/StringStream.h ../Core/Types.h ../Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h
pthreadAPI.o: pthreadAPI.cpp pthreadAPI.h /usr/include/pthread.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h /usr/include/sched.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/i386-linux-gnu/bits/time.h /usr/include/signal.h \
 /home/darkeden/src/libs/sigset.h /usr/include/bits/initspin.h \
 /usr/include/bits/sigthread.h ../Core/Exception.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/c++/7/fstream  \
 /usr/include/c++/7/string /home/darkeden/src/libs/stl_config.h \
 /home/darkeden/src/libs/stl_string_fwd.h /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/i386-linux-gnu/sys/types.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h /usr/include/i386-linux-gnu/sys/sysmacros.h \
 /usr/include/alloca.h /usr/include/string.h /usr/include/assert.h \
 /usr/include/ctype.h /usr/include/c++/7/functional \
 /usr/include/c++/7/bits/stl_function.h /usr/include/c++/7/stdexcept \
 /home/darkeden/src/libs/stl_exception.h /home/darkeden/src/libs/stl_iterator_base.h \
 /usr/include/c++/7/memory /home/darkeden/src/libs/stl_algobase.h \
 /home/darkeden/src/libs/stl_relops.h /home/darkeden/src/libs/stl_pair.h \
 /usr/include/c++/7/ext/type_traits.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 /usr/include/errno.h /usr/include/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/asm/errno.h
Profile.o: Profile.cpp Profile.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../Core/Assert.h Thread.h pthreadAPI.h ../Core/VSDateTime.h \
 ../Core/Gpackets/GMServerInfo.h ../Core/DatagramPacket.h \
 ../Core/Packet.h ../Core/SocketInputStream.h ../Core/Socket.h \
 ../Core/SocketImpl.h ../Core/SocketAPI.h ../Core/SocketOutputStream.h \
 ../Core/Datagram.h ../Core/PacketFactory.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h /usr/include/STL/iomanip.h
PacketProfile.o: PacketProfile.cpp PacketProfile.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h ../Core/VSDateTime.h \
 /usr/include/STL/iomanip.h /usr/include/i386-linux-gnu/bits/stdio_lim.h
GameServerInfoManager.o: GameServerInfoManager.cpp \
 GameServerInfoManager.h ../Core/Types.h ../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h GameServerInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 database/DB.h database/DatabaseManager.h database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 database/Statement.h database/Result.h /usr/include/sys/time.h
PaySystem.o: PaySystem.cpp PaySystem.h ../Core/Types.h \
 ../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../Core/types/PlayerTypes.h \
 ../Core/types/ObjectTypes.h ../Core/types/CreatureTypes.h \
 ../Core/types/ItemTypes.h ../Core/types/ZoneTypes.h \
 ../Core/types/QuestTypes.h ../Core/types/ShopTypes.h \
 ../Core/types/GuildTypes.h ../Core/types/WarTypes.h \
 ../Core/types/ServerType.h ../Core/Utility.h Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../Core/VSDateTime.h ../Core/Exception.h \
 ../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h database/DB.h database/DatabaseManager.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 database/Statement.h database/Result.h Thread.h pthreadAPI.h \
 ../Core/Properties.h /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h
