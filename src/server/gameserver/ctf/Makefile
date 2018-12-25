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
WARDIR   = ../war
MYSQLDIR = /usr/local/lib/mysql


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(WARDIR) -I.
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

OBJS = \
	FlagManager.o \
	FlagWar.o \
	NewbieFlagWar.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(LIBDIR)/libCTF.a


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
FlagManager.o: FlagManager.cpp FlagManager.h ../../../Core/Types.h \
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
 ../war/Work.h ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h ../war/Scheduler.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_hash_map.h \
 ../war/Schedule.h ../../../Core/VSDateTime.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../../Core/Assert.h ../../../Core/Gpackets/GCFlagWarStatus.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h FlagWar.h NewbieFlagWar.h \
 ../PlayerCreature.h ../Creature.h ../Object.h ../EffectManager.h \
 ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h /usr/include/STL/bitset \
 ../ObjectRegistry.h ../InventorySlot.h ../Item.h ../Garbage.h \
 ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /home/darkeden/src/libs/stl_slist.h \
 ../MonsterCorpse.h ../ItemFactory.h ../Inventory.h ../VolumeInfo.h \
 ../Corpse.h ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 ../ZoneUtil.h ../../database/DB.h ../../database/DatabaseManager.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h ../../../Core/Properties.h \
 ../../../Core/Player.h ../EffectFlagInsert.h ../../../Core/NPCInfo.h \
 ../../../Core/Gpackets/GCDeleteInventoryItem.h \
 ../../../Core/Gpackets/GCAddEffect.h ../SystemAvailabilitiesManager.h \
 ../../../Core/Gpackets/GCSystemAvailabilities.h \
 /usr/include/bits/stdio_lim.h /usr/include/STL/cstdlib
FlagWar.o: FlagWar.cpp FlagWar.h ../war/Work.h \
 /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 ../../../Core/Exception.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/fstream \
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
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h ../../../Core/VSDateTime.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 FlagManager.h ../war/Scheduler.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h ../war/Schedule.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../../../Core/Assert.h ../../../Core/Gpackets/GCFlagWarStatus.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 ../../../Core/PacketFactory.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h ../ItemFactoryManager.h ../Item.h \
 ../Object.h ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h ../EffectManager.h \
 ../../../Core/EffectInfo.h /usr/include/STL/bitset ../ItemFactory.h \
 ../Zone.h ../Tile.h /usr/include/STL/slist \
 /home/darkeden/src/libs/stl_slist.h ../Creature.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../ObjectRegistry.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 ../ZoneUtil.h ../ZoneInfoManager.h ../ZoneInfo.h \
 ../GlobalItemPositionLoader.h ../war/GlobalItemPosition.h \
 ../MonsterSummonInfo.h ../MonsterInfoTypes.h ../ZoneGroupManager.h \
 ../ZoneGroup.h ../../../Core/GameTime.h \
 ../../../Core/Gpackets/GMServerInfo.h ../../../Core/DatagramPacket.h \
 ../../../Core/Datagram.h ../../../Core/Gpackets/GCNoticeEvent.h
NewbieFlagWar.o: NewbieFlagWar.cpp NewbieFlagWar.h FlagWar.h \
 ../war/Work.h /usr/include/c++/7/iostream  \
 /usr/include/c++/7/streambuf /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/wchar.h /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 ../../../Core/Exception.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/fstream \
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
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h ../../../Core/types/PlayerTypes.h \
 ../../../Core/types/ObjectTypes.h ../../../Core/types/CreatureTypes.h \
 ../../../Core/types/ItemTypes.h ../../../Core/types/ZoneTypes.h \
 ../../../Core/types/QuestTypes.h ../../../Core/types/ShopTypes.h \
 ../../../Core/types/GuildTypes.h ../../../Core/types/WarTypes.h \
 ../../../Core/types/ServerType.h ../../../Core/Utility.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h ../../../Core/VSDateTime.h \
 /usr/include/STL/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_bvector.h \
 ../ZoneUtil.h ../Creature.h ../Object.h ../../../Core/Assert.h \
 ../EffectManager.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset ../MonsterSummonInfo.h ../MonsterInfoTypes.h \
 ../Zone.h ../Tile.h /usr/include/STL/slist \
 /home/darkeden/src/libs/stl_slist.h ../Item.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h /usr/include/STL/hash_map \
 /home/darkeden/src/libs/stl_hashtable.h /home/darkeden/src/libs/stl_hash_map.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../ZoneInfoManager.h ../ZoneInfo.h \
 FlagManager.h ../war/Scheduler.h ../war/Schedule.h \
 ../../../Core/Gpackets/GCFlagWarStatus.h \
 ../../../Core/PacketFactory.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h
