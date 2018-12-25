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
DBINCDIR  = /usr/local/include/mysql
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
LOGDIR  = $(VSHOME)/log
SRCDIR  = $(VSHOME)/src
COREDIR = $(SRCDIR)/Core
SERVDIR = $(SRCDIR)/server


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o .gs.o .ls.o .us.o .ss.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBINCDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o : 
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

.cpp.gs.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -o $*.gs.o $<

.cpp.ls.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__LOGIN_SERVER__ $(INCLUDES) -o $*.ls.o $<

.cpp.us.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__UPDATE_SERVER__ $(INCLUDES) -o $*.us.o $<

.cpp.ss.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__SHARED_SERVER__ $(INCLUDES) -o $*.ss.o $<

#----------------------------------------------------------------------
# Server Core Library
#----------------------------------------------------------------------
DB_OBJS = Connection.o Statement.o Result.o DatabaseManager.o
DB_SRC  = $(DB_OBJS:.o=.cpp)
DB_LIB  = $(LIBDIR)/libDatabase.a

#----------------------------------------------------------------------
# Packet Library for GameServer
#----------------------------------------------------------------------
GS_DB_OBJS = Connection.gs.o Statement.gs.o Result.gs.o DatabaseManager.gs.o
GS_DB_SRCS = $(GS_DB_OBJS:.gs.o=.cpp)
GS_DB_LIB  = $(LIBDIR)/libGameServerDatabase.a

#----------------------------------------------------------------------
# Packet Library for LoginServer
#----------------------------------------------------------------------
LS_DB_OBJS = Connection.ls.o Statement.ls.o Result.ls.o DatabaseManager.ls.o
LS_DB_SRCS = $(LS_DB_OBJS:.ls.o=.cpp)
LS_DB_LIB  = $(LIBDIR)/libLoginServerDatabase.a

#----------------------------------------------------------------------
# Packet Library for Updateserver 
#----------------------------------------------------------------------
US_DB_OBJS = Connection.us.o Statement.us.o Result.gs.o DatabaseManager.us.o
US_DB_SRCS = $(US_DB_OBJS:.us.o=.cpp)
US_DB_LIB  = $(LIBDIR)/libUpdateServerDatabase.a

#----------------------------------------------------------------------
# Database Library for Updateserver 
#----------------------------------------------------------------------
SS_DB_OBJS = Connection.ss.o Statement.ss.o Result.ss.o DatabaseManager.ss.o
SS_DB_SRCS = $(SS_DB_OBJS:.ss.o=.cpp)
SS_DB_LIB  = $(LIBDIR)/libSharedServerDatabase.a

#----------------------------------------------------------------------
# All Targets
#----------------------------------------------------------------------
#TARGETS = $(CORE_LIB) $(LS_DB_LIB) $(GS_DB_LIB)
SRCS = $(LS_DB_SRCS) $(GS_DB_SRCS) $(US_DB_SRCS) $(SS_DB_SRCS)
TARGETS = $(DB_LIB) $(LS_DB_LIB) $(GS_DB_LIB) $(US_DB_LIB) $(SS_DB_LIB)

#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGETS)

$(DB_LIB) : $(DB_OBJS)
	ar rc $@ $^

$(LS_DB_LIB) : $(LS_DB_OBJS)
	ar rc $@ $^

$(GS_DB_LIB) : $(GS_DB_OBJS)
	ar rc $@ $^

$(US_DB_LIB) : $(US_DB_OBJS)
	ar rc $@ $^

$(SS_DB_LIB) : $(SS_DB_OBJS)
	ar rc $@ $^

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGETS)

depall : 
	gccmakedep $(SRCS) $(INCLUDES)

dep : 
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
Connection.o: Connection.cpp Connection.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 Statement.h
Statement.o: Statement.cpp Statement.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/bits/stdio_lim.h /usr/include/sys/time.h Result.h \
 /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/server/Profile.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h
Result.o: Result.cpp Result.h /home/darkeden/vs/src/Core/Types.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/sys/time.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/Core/Assert.h
DatabaseManager.o: DatabaseManager.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/bits/stdio_lim.h DatabaseManager.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/c++/7/fstream \
  /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /home/darkeden/src/libs/stl_alloc.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h /home/darkeden/vs/src/server/Thread.h \
 /home/darkeden/vs/src/server/pthreadAPI.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h Result.h \
 Statement.h /home/darkeden/vs/src/Core/Assert.h DB.h
Connection.o: Connection.cpp Connection.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 Statement.h
Statement.o: Statement.cpp Statement.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/bits/stdio_lim.h /usr/include/sys/time.h Result.h \
 /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/server/Profile.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h
Result.o: Result.cpp Result.h /home/darkeden/vs/src/Core/Types.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/sys/time.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/Core/Assert.h
DatabaseManager.o: DatabaseManager.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/bits/stdio_lim.h DatabaseManager.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/c++/7/fstream \
  /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /home/darkeden/src/libs/stl_alloc.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h /home/darkeden/vs/src/server/Thread.h \
 /home/darkeden/vs/src/server/pthreadAPI.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h Result.h \
 Statement.h /home/darkeden/vs/src/Core/Assert.h DB.h
Connection.o: Connection.cpp Connection.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 Statement.h
Statement.o: Statement.cpp Statement.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/bits/stdio_lim.h /usr/include/sys/time.h Result.h \
 /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/server/Profile.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h
DatabaseManager.o: DatabaseManager.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/bits/stdio_lim.h DatabaseManager.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/c++/7/fstream \
  /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /home/darkeden/src/libs/stl_alloc.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h /home/darkeden/vs/src/server/Thread.h \
 /home/darkeden/vs/src/server/pthreadAPI.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h Result.h \
 Statement.h /home/darkeden/vs/src/Core/Assert.h DB.h
Connection.o: Connection.cpp Connection.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 Statement.h
Statement.o: Statement.cpp Statement.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/bits/stdio_lim.h /usr/include/sys/time.h Result.h \
 /home/darkeden/vs/src/Core/Assert.h \
 /home/darkeden/vs/src/server/Profile.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h
Result.o: Result.cpp Result.h /home/darkeden/vs/src/Core/Types.h \
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
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/sys/time.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/Core/Assert.h
DatabaseManager.o: DatabaseManager.cpp /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/bits/stdio_lim.h DatabaseManager.h \
 /home/darkeden/vs/src/Core/Types.h \
 /home/darkeden/vs/src/Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/c++/7/fstream \
  /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /home/darkeden/src/libs/stl_alloc.h \
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
 /home/darkeden/vs/src/Core/types/PlayerTypes.h \
 /home/darkeden/vs/src/Core/types/ObjectTypes.h \
 /home/darkeden/vs/src/Core/types/CreatureTypes.h \
 /home/darkeden/vs/src/Core/types/ItemTypes.h \
 /home/darkeden/vs/src/Core/types/ZoneTypes.h \
 /home/darkeden/vs/src/Core/types/QuestTypes.h \
 /home/darkeden/vs/src/Core/types/ShopTypes.h \
 /home/darkeden/vs/src/Core/types/GuildTypes.h \
 /home/darkeden/vs/src/Core/types/WarTypes.h \
 /home/darkeden/vs/src/Core/types/ServerType.h \
 /home/darkeden/vs/src/Core/Utility.h \
 /home/darkeden/vs/src/Core/Exception.h \
 /home/darkeden/vs/src/Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h \
 /home/darkeden/vs/src/server/Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /home/darkeden/vs/src/Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h /home/darkeden/vs/src/server/Thread.h \
 /home/darkeden/vs/src/server/pthreadAPI.h \
 /home/darkeden/vs/src/server/Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h Result.h \
 Statement.h /home/darkeden/vs/src/Core/Assert.h DB.h
