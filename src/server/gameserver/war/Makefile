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
VSHOME   = ../../../..
STLDIR   = /usr/include/STL
BINDIR   = $(VSHOME)/bin
LIBDIR   = $(VSHOME)/lib
LOGDIR   = $(VSHOME)/log
SRCDIR   = ../../..
COREDIR  = ../../../Core
SERVDIR  = ../..
DBDIR    = ../../database
GSDIR    = ..
MYSQLDIR = /usr/local/lib/mysql


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

OBJS = \
	Schedule.o \
	Scheduler.o \
	War.o \
	RaceWar.o \
	GuildWar.o \
	SiegeWar.o \
	WarSchedule.o \
	WarScheduler.o \
	WarSystem.o \
	ZoneItemPosition.o \
	InventoryItemPosition.o \
	MouseItemPosition.o \
	CorpseItemPosition.o \
	RaceWarLimiter.o \
	DragonEyeManager.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(LIBDIR)/libWar.a


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : $(TARGET)

$(TARGET) : $(OBJS)
	ar rc $@ $^

clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)

# DO NOT DELETE
Schedule.o: Schedule.cpp ../../../Core/Exception.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Work.h Schedule.h \
 ../../../Core/VSDateTime.h
Scheduler.o: Scheduler.cpp Scheduler.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_config.h \
 /usr/include/c++/7/stdexcept /home/darkeden/src/libs/stl_exception.h \
 /usr/include/c++/7/exception \
 /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/sys/select.h /usr/include/i386-linux-gnu/bits/select.h \
 /home/darkeden/src/libs/sigset.h /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/assert.h /usr/include/c++/7/string \
 /usr/include/ctype.h /usr/include/c++/7/functional \
 /usr/include/c++/7/bits/stl_function.h /home/darkeden/src/libs/stl_iterator_base.h \
 /usr/include/c++/7/memory /home/darkeden/src/libs/stl_algobase.h \
 /home/darkeden/src/libs/stl_relops.h /home/darkeden/src/libs/stl_pair.h \
 /usr/include/c++/7/ext/type_traits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/limits.h \
 /usr/lib/gcc/i686-linux-gnu/7/include-fixed/syslimits.h \
 /usr/include/limits.h /usr/include/i386-linux-gnu/bits/posix1_lim.h \
 /usr/include/i386-linux-gnu/bits/local_lim.h /usr/include/linux/limits.h \
 /usr/include/i386-linux-gnu/bits/posix2_lim.h \
 /home/darkeden/src/libs/new.h \
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h ../../../Core/Exception.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
 /usr/include/c++/7/iostream /usr/include/c++/7/fstream \
  ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h Work.h Schedule.h \
 ../../../Core/VSDateTime.h ../../../Core/Assert.h
War.o: War.cpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h War.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h Work.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h ../../../Core/VSDateTime.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 WarSystem.h Scheduler.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h Schedule.h \
 ../../../Core/Gpackets/GCWarList.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 ../../../Core/GuildWarInfo.h ../../../Core/WarInfo.h \
 ../../../Core/ValueList.h ../../../Core/RaceWarInfo.h \
 ../../../Core/Properties.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/i386-linux-gnu/sys/time.h \
 ../../../Core/Assert.h ../ZoneGroupManager.h ../ZoneGroup.h ../Zone.h \
 ../Tile.h /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h \
 ../Object.h ../Creature.h ../EffectManager.h ../Effect.h \
 ../../Timeval.h /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h /usr/include/c++/7/bitset ../Item.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../ObjectRegistry.h ../Party.h ../../../Core/ModifyInfo.h \
 ../PCManager.h ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h ../../../Core/GameTime.h \
 ../../../Core/Gpackets/GMServerInfo.h ../../../Core/DatagramPacket.h \
 ../../../Core/Datagram.h ../HolyLandRaceBonus.h ../ZoneUtil.h \
 ../CastleInfoManager.h ../PlayerCreature.h ../InventorySlot.h \
 ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 ../ShrineInfoManager.h ../ZoneInfoManager.h ../ZoneInfo.h \
 ../StringPool.h ../../../Core/Gpackets/GCSystemMessage.h \
 ../../../Core/Gpackets/GCNoticeEvent.h
RaceWar.o: RaceWar.cpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h RaceWar.h War.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h Work.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h ../../../Core/VSDateTime.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 WarSystem.h Scheduler.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h Schedule.h \
 ../../../Core/Gpackets/GCWarList.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 ../../../Core/GuildWarInfo.h ../../../Core/WarInfo.h \
 ../../../Core/ValueList.h ../../../Core/RaceWarInfo.h \
 ../../../Core/Properties.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/i386-linux-gnu/sys/time.h \
 ../../../Core/Assert.h ../ZoneGroupManager.h ../ZoneGroup.h ../Zone.h \
 ../Tile.h /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h \
 ../Object.h ../Creature.h ../EffectManager.h ../Effect.h \
 ../../Timeval.h /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h /usr/include/c++/7/bitset ../Item.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../ObjectRegistry.h ../Party.h ../../../Core/ModifyInfo.h \
 ../PCManager.h ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h ../../../Core/GameTime.h \
 ../../../Core/Gpackets/GMServerInfo.h ../../../Core/DatagramPacket.h \
 ../../../Core/Datagram.h ../ZoneUtil.h ../CastleInfoManager.h \
 ../PlayerCreature.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 ../ShrineInfoManager.h ../ZoneInfoManager.h ../ZoneInfo.h \
 ../../../Core/Gpackets/GCWarScheduleList.h ../HolyLandManager.h \
 ../VariableManager.h RaceWarLimiter.h ../PCLimiter.h \
 ../RegenZoneManager.h ../MonsterCorpse.h ../ItemFactory.h \
 ../Inventory.h ../VolumeInfo.h ../Corpse.h DragonEyeManager.h \
 ../item/WarItem.h ../ItemInfo.h ../InfoClassManager.h ../ItemLoader.h \
 ../../../Core/Gpackets/GCSystemMessage.h \
 ../../../Core/Gpackets/GCNoticeEvent.h ../../../Core/Cpackets/CGSay.h
GuildWar.o: GuildWar.cpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../Guild.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Assert.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../../../Core/VSDateTime.h ../GuildManager.h ../../Timeval.h \
 /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h GuildWar.h War.h Work.h WarSystem.h Scheduler.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_bvector.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h Schedule.h \
 ../../../Core/Gpackets/GCWarList.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 ../../../Core/GuildWarInfo.h ../../../Core/WarInfo.h \
 ../../../Core/ValueList.h ../../../Core/RaceWarInfo.h \
 ../../../Core/Properties.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../ZoneGroupManager.h ../ZoneGroup.h \
 ../Zone.h ../Tile.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../Object.h ../Creature.h \
 ../EffectManager.h ../Effect.h ../../../Core/EffectInfo.h \
 /usr/include/c++/7/bitset ../Item.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../ObjectRegistry.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h \
 ../HolyLandRaceBonus.h ../ZoneUtil.h ../CastleInfoManager.h \
 ../PlayerCreature.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 ../CastleShrineInfoManager.h ../ShrineInfoManager.h \
 ../ZoneInfoManager.h ../ZoneInfo.h \
 ../../../Core/Gpackets/GCSystemMessage.h \
 ../../../Core/Gpackets/GCNoticeEvent.h \
 ../../../Core/Gpackets/GCWarScheduleList.h \
 ../../../Core/Cpackets/CGSay.h
SiegeWar.o: SiegeWar.cpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sched.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../Guild.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Assert.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../../../Core/VSDateTime.h ../GuildManager.h ../../Timeval.h \
 /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h SiegeWar.h War.h Work.h WarSystem.h Scheduler.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_bvector.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h Schedule.h \
 ../../../Core/Gpackets/GCWarList.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../../../Core/PacketFactory.h \
 ../../../Core/GuildWarInfo.h ../../../Core/WarInfo.h \
 ../../../Core/ValueList.h ../../../Core/RaceWarInfo.h \
 ../../../Core/Properties.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../ZoneGroupManager.h ../ZoneGroup.h \
 ../Zone.h ../Tile.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../Object.h ../Creature.h \
 ../EffectManager.h ../Effect.h ../../../Core/EffectInfo.h \
 /usr/include/c++/7/bitset ../Item.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../ObjectRegistry.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h \
 ../HolyLandRaceBonus.h ../ZoneUtil.h ../CastleInfoManager.h \
 ../PlayerCreature.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 ../ZoneInfoManager.h ../ZoneInfo.h ../SiegeManager.h \
 ../../GameServerInfoManager.h ../../GameServerInfo.h \
 ../LoginServerManager.h ../../Thread.h ../../pthreadAPI.h \
 ../../../Core/DatagramSocket.h \
 ../../../Core/Gpackets/GCSystemMessage.h \
 ../../../Core/Gpackets/GCNoticeEvent.h \
 ../../../Core/Gpackets/GCWarScheduleList.h \
 ../../../Core/Gpackets/GCNPCResponse.h ../../../Core/Cpackets/CGSay.h \
 ../../../Core/Gpackets/GGCommand.h
WarSchedule.o: WarSchedule.cpp WarSchedule.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h Work.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h Schedule.h \
 ../../../Core/VSDateTime.h War.h ../GuildManager.h \
 ../../../Core/Assert.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 ../../Timeval.h /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_hash_map.h ../../../Core/Properties.h \
 /usr/include/c++/7/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../Zone.h ../Tile.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../Object.h ../Creature.h \
 ../EffectManager.h ../Effect.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../Item.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_bvector.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../ObjectRegistry.h ../Party.h ../../../Core/ModifyInfo.h \
 ../PCManager.h ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../CastleInfoManager.h \
 ../PlayerCreature.h ../InventorySlot.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h GuildWar.h \
 SiegeWar.h ../../../Core/Gpackets/GCWarScheduleList.h \
 ../../../Core/Gpackets/GCWarList.h ../../../Core/GuildWarInfo.h \
 ../../../Core/WarInfo.h ../../../Core/ValueList.h \
 ../../../Core/RaceWarInfo.h
WarScheduler.o: WarScheduler.cpp WarSchedule.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h Work.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h Schedule.h \
 ../../../Core/VSDateTime.h War.h WarScheduler.h Scheduler.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_hash_map.h \
 ../../Mutex.h /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/signal.h /usr/include/i386-linux-gnu/bits/initspin.h \
 /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph ../../../Core/Assert.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/i386-linux-gnu/sys/time.h ../Zone.h ../Tile.h \
 /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h ../Object.h \
 ../Creature.h ../EffectManager.h ../Effect.h ../../Timeval.h \
 /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h /usr/include/c++/7/bitset ../Item.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../ObjectRegistry.h ../Party.h ../../../Core/ModifyInfo.h \
 ../PCManager.h ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h ../../../Core/Properties.h \
 /usr/include/c++/7/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h GuildWar.h \
 SiegeWar.h ../VariableManager.h /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 ../../../Core/Gpackets/GCWarScheduleList.h \
 ../../../Core/PacketFactory.h WarSystem.h \
 ../../../Core/Gpackets/GCWarList.h ../../../Core/GuildWarInfo.h \
 ../../../Core/WarInfo.h ../../../Core/ValueList.h \
 ../../../Core/RaceWarInfo.h
WarSystem.o: WarSystem.cpp WarSystem.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 Scheduler.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h Work.h Schedule.h \
 ../../../Core/VSDateTime.h ../../../Core/Gpackets/GCWarList.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h ../../../Core/GuildWarInfo.h \
 ../../../Core/WarInfo.h ../../../Core/ValueList.h \
 ../../../Core/RaceWarInfo.h ../../../Core/Assert.h War.h RaceWar.h \
 WarSchedule.h WarScheduler.h ../../../Core/Player.h ../GamePlayer.h \
 ../../../Core/SocketEncryptOutputStream.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h \
 ../../../Core/SocketEncryptInputStream.h /usr/include/STL/deque \
 ../../Timeval.h /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/PlayerStatus.h ../EventManager.h \
 ../Event.h ../skill/Skill.h ../../PaySystem.h \
 ../billing/BillingPlayerInfo.h \
 ../../chinabilling/CBillingPlayerInfo.h \
 ../../chinabilling/CBillingInfo.h \
 ../../../Core/Gpackets/GCReconnectLogin.h /usr/include/c++/7/bitset \
 ../gameguard/CSAuth.h ../ZoneGroupManager.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../ZoneGroup.h ../Zone.h ../Tile.h \
 /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h ../Object.h \
 ../Creature.h ../EffectManager.h ../Effect.h \
 ../../../Core/EffectInfo.h ../Item.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../ObjectRegistry.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h \
 ../CastleInfoManager.h ../PlayerCreature.h ../InventorySlot.h \
 ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 ../../../Core/Gpackets/GCSystemMessage.h \
 ../../../Core/Gpackets/GCWarScheduleList.h \
 ../../../Core/Gpackets/GCNoticeEvent.h ../VariableManager.h \
 GuildWar.h SiegeWar.h ../EventRefreshHolyLandPlayer.h \
 ../ShrineInfoManager.h ../ClientManager.h ../HolyLandManager.h \
 ../StringPool.h /usr/include/i386-linux-gnu/bits/stdio_lim.h
ZoneItemPosition.o: ZoneItemPosition.cpp ../../../Core/Assert.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../Item.h \
 ../Object.h ../Effect.h ../../Timeval.h /usr/include/i386-linux-gnu/sys/time.h \
 /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h ../EffectManager.h \
 ../../../Core/EffectInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h /usr/include/c++/7/bitset \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 ../Corpse.h ../ItemFactory.h ../Zone.h ../Tile.h \
 /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h ../Creature.h \
 ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_hash_map.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../ZoneGroup.h ../../../Core/GameTime.h \
 ../../../Core/Gpackets/GMServerInfo.h ../../../Core/DatagramPacket.h \
 ../../../Core/Datagram.h ../../../Core/PacketFactory.h ../ZoneUtil.h \
 ../../../Core/VSDateTime.h ../../../Core/Gpackets/GCDeleteObject.h \
 ../../../Core/Gpackets/GCAddEffectToTile.h ZoneItemPosition.h \
 GlobalItemPosition.h
InventoryItemPosition.o: InventoryItemPosition.cpp \
 ../../../Core/Assert.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../Item.h \
 ../Object.h ../Effect.h ../../Timeval.h /usr/include/i386-linux-gnu/sys/time.h \
 /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h ../EffectManager.h \
 ../../../Core/EffectInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h /usr/include/c++/7/bitset \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 ../PlayerCreature.h ../Creature.h ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../../../Core/Player.h ../PCFinder.h \
 ../NPC.h ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../couple/PartnerWaitingManager.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../ZoneGroup.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h \
 ../CreatureUtil.h ../RelicUtil.h InventoryItemPosition.h \
 GlobalItemPosition.h ../../../Core/Gpackets/GCDeleteInventoryItem.h \
 ../../../Core/Gpackets/GCAddEffect.h
MouseItemPosition.o: MouseItemPosition.cpp ../../../Core/Assert.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../PlayerCreature.h \
 ../Creature.h ../Object.h ../EffectManager.h ../Effect.h \
 ../../Timeval.h /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 ../InventorySlot.h ../Item.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../../../Core/Player.h ../PCFinder.h \
 ../NPC.h ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../couple/PartnerWaitingManager.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../ZoneGroup.h \
 ../../../Core/GameTime.h ../../../Core/Gpackets/GMServerInfo.h \
 ../../../Core/DatagramPacket.h ../../../Core/Datagram.h ../ZoneUtil.h \
 ../../../Core/VSDateTime.h ../RelicUtil.h ../CreatureUtil.h \
 MouseItemPosition.h GlobalItemPosition.h \
 ../../../Core/Gpackets/GCDeleteInventoryItem.h \
 ../../../Core/Gpackets/GCAddEffect.h
CorpseItemPosition.o: CorpseItemPosition.cpp ../../../Core/Assert.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../Zone.h ../Tile.h \
 /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h ../Object.h \
 ../Creature.h ../EffectManager.h ../Effect.h ../../Timeval.h \
 /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../Item.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_hash_map.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../ZoneGroup.h ../../../Core/GameTime.h \
 ../../../Core/Gpackets/GMServerInfo.h ../../../Core/DatagramPacket.h \
 ../../../Core/Datagram.h ../../../Core/PacketFactory.h ../Corpse.h \
 ../ItemFactory.h ../MonsterCorpse.h ../Inventory.h ../VolumeInfo.h \
 ../InventorySlot.h ../ZoneUtil.h ../../../Core/VSDateTime.h \
 ../ItemUtil.h ../RelicUtil.h ../ItemFactoryManager.h \
 CorpseItemPosition.h GlobalItemPosition.h \
 ../../../Core/Gpackets/GCAddEffectToTile.h ../ctf/FlagManager.h \
 ../war/Work.h ../war/Scheduler.h ../war/Schedule.h \
 ../../../Core/Gpackets/GCFlagWarStatus.h /usr/include/c++/7/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h
RaceWarLimiter.o: RaceWarLimiter.cpp RaceWarLimiter.h ../PCLimiter.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 ../../database/DB.h ../../database/DatabaseManager.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/i386-linux-gnu/sys/time.h ../Slayer.h \
 ../PlayerCreature.h ../Creature.h ../Object.h ../../../Core/Assert.h \
 ../EffectManager.h ../Effect.h ../../Timeval.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../ObjectRegistry.h ../InventorySlot.h \
 ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../../../Core/PCSlayerInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../ItemLoaderManager.h ../ItemLoader.h \
 ../../../Core/GearInfo.h ../../../Core/GearSlotInfo.h \
 ../../../Core/ExtraInfo.h ../../../Core/ExtraSlotInfo.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h \
 /usr/include/STL/cstdio /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h ../../../Core/VSDateTime.h
DragonEyeManager.o: DragonEyeManager.cpp DragonEyeManager.h \
 ../../../Core/Types.h ../../../Core/types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 ../item/WarItem.h ../Item.h ../Object.h ../../../Core/Assert.h \
 ../Effect.h ../../Timeval.h /usr/include/i386-linux-gnu/sys/time.h \
 /usr/include/unistd.h /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h ../EffectManager.h \
 ../../../Core/EffectInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h /usr/include/c++/7/bitset \
 ../ItemInfo.h ../InfoClassManager.h ../ItemFactory.h ../ItemLoader.h \
 ../../Mutex.h /usr/include/pthread.h /usr/include/sched.h \
 /usr/include/signal.h /usr/include/i386-linux-gnu/bits/initspin.h \
 /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph ../ItemFactoryManager.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h ../ZoneUtil.h ../Creature.h \
 ../../../Core/VSDateTime.h ../Zone.h ../Tile.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../ObjectRegistry.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../GlobalItemPositionLoader.h \
 GlobalItemPosition.h ../EffectDragonEye.h ../EffectHasRelic.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h
