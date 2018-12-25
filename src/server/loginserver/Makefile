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
VSHOME  = ../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
LOGDIR  = $(VSHOME)/log
DBINCDIR  = /usr/local/include/mysql
SRCDIR  = ../..
COREDIR = ../../Core
SERVDIR = ..
DBDIR   = ../database
MYSQLDIR = /usr/local/lib/mysql
BILLINGDIR = ../gameserver/billing

#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__LOGIN_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(DBINCDIR) -I$(BILLINGDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS     = -L$(LIBDIR) -lLoginServerDatabase -lLoginServerPackets -lServerCore -lCore -lLoginServerBilling -lLoginServerCBilling -lcpsso 
#LIBS     = -L$(LIBDIR) -lLoginServerDatabase -lLoginServerPackets -lServerCore -lCore -lLoginServerBilling -lLoginServerCBilling
SYSLIBS  = -L$(MYSQLDIR) -static -lmysqlclient -lpthread -lnsl -lz

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<


#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------
OBJS = \
	ClientManager.o UserInfoManager.o \
	GameServerGroupInfoManager.o GameServerManager.o \
	LoginPlayer.o LoginPlayerManager.o LoginServer.o \
	ZoneGroupInfoManager.o ZoneInfoManager.o main.o \
	ItemDestroyer.o ReconnectLoginInfoManager.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(BINDIR)/loginserver


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
$(TARGET) : $(OBJS) $(LIBDIR)/libLoginServerDatabase.a $(LIBDIR)/libLoginServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a $(LIBDIR)/libcpsso.a $(LIBDIR)/libLoginServerCBilling.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS) 
clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)
# DO NOT DELETE
ClientManager.o: ClientManager.cpp ../database/DatabaseManager.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ClientManager.h ../../Core/Assert.h LoginPlayerManager.h \
 ../PlayerManager.h ../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../Core/SocketAPI.h ../../Core/ServerSocket.h \
 ../../Core/SocketImpl.h ../../Core/Socket.h \
 ReconnectLoginInfoManager.h ReconnectLoginInfo.h ../Profile.h \
 ../PacketProfile.h ../../Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../GameWorldInfoManager.h \
 ../GameWorldInfo.h GameServerGroupInfoManager.h GameServerGroupInfo.h
UserInfoManager.o: UserInfoManager.cpp UserInfoManager.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h UserInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h \
 ../database/DB.h
GameServerGroupInfoManager.o: GameServerGroupInfoManager.cpp \
 GameServerGroupInfoManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 GameServerGroupInfo.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h \
 ../database/DB.h
GameServerManager.o: GameServerManager.cpp GameServerManager.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../Thread.h \
 ../pthreadAPI.h /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/signal.h /usr/include/bits/initspin.h \
 /usr/include/bits/sigthread.h ../../Core/DatagramSocket.h \
 ../../Core/SocketAPI.h ../../Core/Datagram.h ../../Core/Properties.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 ../../Core/DatagramPacket.h ../../Core/Packet.h \
 ../../Core/SocketInputStream.h ../../Core/Socket.h \
 ../../Core/SocketImpl.h ../../Core/SocketOutputStream.h \
 ../LogClient.h /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h ../database/DB.h \
 ../database/DatabaseManager.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h \
 ../../Core/Lpackets/LGKickCharacter.h ../../Core/PacketFactory.h
LoginPlayer.o: LoginPlayer.cpp LoginPlayer.h ../../Core/Player.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../Core/PlayerStatus.h /usr/include/STL/deque \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_deque.h \
 ../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../PaySystem.h ../../Core/VSDateTime.h \
 ../gameserver/billing/BillingPlayerInfo.h \
 ../chinabilling/CBillingPlayerInfo.h ../chinabilling/CBillingInfo.h \
 ../../Core/Gpackets/GCReconnectLogin.h ../../Core/Packet.h \
 ../../Core/SocketInputStream.h ../../Core/Socket.h \
 ../../Core/SocketImpl.h ../../Core/SocketAPI.h \
 ../../Core/SocketOutputStream.h ../../Core/PacketFactory.h \
 ../../Core/Assert.h ../../Core/PacketFactoryManager.h \
 ../../Core/PacketValidator.h ../../Core/PacketIDSet.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h ../database/DB.h \
 ../database/DatabaseManager.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_hash_map.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../database/Statement.h \
 ../database/Result.h ../LogClient.h ../Profile.h ../PacketProfile.h \
 ../GameServerInfoManager.h ../GameServerInfo.h GameServerManager.h \
 ../Thread.h ../pthreadAPI.h ../../Core/DatagramSocket.h \
 ../../Core/Datagram.h ../gameserver/billing/BillingPlayerManager.h \
 ../gameserver/billing/BillingInfo.h ../../Core/Lpackets/LCLoginOK.h \
 ../../Core/Lpackets/LCLoginError.h \
 ../../Core/Lpackets/LGKickCharacter.h ../../Core/DatagramPacket.h \
 ../../Core/Lpackets/LCPCList.h ../../Core/PCInfo.h \
 ../../Core/PCSlayerInfo.h /usr/include/STL/bitset \
 ../../Core/PCVampireInfo.h ../../Core/PCOustersInfo.h
LoginPlayerManager.o: LoginPlayerManager.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/bits/stdio_lim.h LoginPlayerManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
  /usr/include/c++/7/streambuf \
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
 /usr/include/c++/7/bits/char_traits.h /home/darkeden/src/libs/stl_hash_fun.h \
 ../../Core/types/PlayerTypes.h ../../Core/types/ObjectTypes.h \
 ../../Core/types/CreatureTypes.h ../../Core/types/ItemTypes.h \
 ../../Core/types/ZoneTypes.h ../../Core/types/QuestTypes.h \
 ../../Core/types/ShopTypes.h ../../Core/types/GuildTypes.h \
 ../../Core/types/WarTypes.h ../../Core/types/ServerType.h \
 ../../Core/Utility.h ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../PlayerManager.h \
 ../Timeval.h /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../../Core/SocketAPI.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../Core/ServerSocket.h ../../Core/SocketImpl.h ../../Core/Socket.h \
 ../../Core/Assert.h LoginPlayer.h ../../Core/Player.h \
 ../../Core/PlayerStatus.h /usr/include/STL/deque \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_deque.h \
 ../PaySystem.h ../../Core/VSDateTime.h \
 ../gameserver/billing/BillingPlayerInfo.h \
 ../chinabilling/CBillingPlayerInfo.h ../chinabilling/CBillingInfo.h \
 ../../Core/Gpackets/GCReconnectLogin.h ../../Core/Packet.h \
 ../../Core/SocketInputStream.h ../../Core/SocketOutputStream.h \
 ../../Core/PacketFactory.h ../LogClient.h ../../Core/Properties.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 ReconnectLoginInfoManager.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h ReconnectLoginInfo.h \
 ../gameserver/billing/BillingInfo.h ../database/DB.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../database/Statement.h \
 ../database/Result.h
LoginServer.o: LoginServer.cpp LoginServer.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../../Core/Assert.h \
 ../GameServerInfoManager.h ../GameServerInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 GameServerGroupInfoManager.h GameServerGroupInfo.h \
 GameServerManager.h ../Thread.h ../pthreadAPI.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../Core/DatagramSocket.h ../../Core/SocketAPI.h \
 ../../Core/Datagram.h ClientManager.h ZoneInfoManager.h ZoneInfo.h \
 ZoneGroupInfoManager.h ZoneGroupInfo.h ../database/DatabaseManager.h \
 ../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 ../../Core/PacketFactoryManager.h ../../Core/Packet.h \
 ../../Core/SocketInputStream.h ../../Core/Socket.h \
 ../../Core/SocketImpl.h ../../Core/SocketOutputStream.h \
 ../../Core/PacketFactory.h ../../Core/PacketValidator.h \
 ../../Core/PacketIDSet.h ../../Core/PlayerStatus.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_bvector.h ItemDestroyer.h ../database/DB.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h \
 UserInfoManager.h UserInfo.h ../GameWorldInfoManager.h \
 ../GameWorldInfo.h ../chinabilling/CBillingPlayerManager.h \
 ../chinabilling/CBillingInfo.h LoginPlayer.h ../../Core/Player.h \
 /usr/include/STL/deque /home/darkeden/src/libs/stl_deque.h ../Timeval.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h ../PaySystem.h \
 ../../Core/VSDateTime.h ../gameserver/billing/BillingPlayerInfo.h \
 ../chinabilling/CBillingPlayerInfo.h \
 ../../Core/Gpackets/GCReconnectLogin.h ../LogClient.h
ZoneGroupInfoManager.o: ZoneGroupInfoManager.cpp \
 ZoneGroupInfoManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ZoneGroupInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h
ZoneInfoManager.o: ZoneInfoManager.cpp ZoneInfoManager.h \
 ../../Core/Types.h ../../Core/types/SystemTypes.h \
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
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ZoneInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../database/DatabaseManager.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h
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
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h LoginServer.h \
 ../LogClient.h ../../Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h /usr/include/bits/stdio_lim.h \
 /usr/include/sys/time.h /usr/include/sys/resource.h \
 /usr/include/bits/resource.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h
ItemDestroyer.o: ItemDestroyer.cpp ItemDestroyer.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../database/DB.h \
 ../database/DatabaseManager.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h ../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../database/Statement.h ../database/Result.h /usr/include/sys/time.h
ReconnectLoginInfoManager.o: ReconnectLoginInfoManager.cpp \
 ReconnectLoginInfoManager.h ../../Core/Types.h \
 ../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../Core/types/PlayerTypes.h \
 ../../Core/types/ObjectTypes.h ../../Core/types/CreatureTypes.h \
 ../../Core/types/ItemTypes.h ../../Core/types/ZoneTypes.h \
 ../../Core/types/QuestTypes.h ../../Core/types/ShopTypes.h \
 ../../Core/types/GuildTypes.h ../../Core/types/WarTypes.h \
 ../../Core/types/ServerType.h ../../Core/Utility.h \
 ../../Core/Exception.h ../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ReconnectLoginInfo.h ../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../Core/Assert.h
