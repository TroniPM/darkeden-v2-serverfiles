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
	PartnerWaitingManager.o \
	CoupleManager.o \
	WaitForMeet.o \
	WaitForApart.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(LIBDIR)/libCouple.a


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
PartnerWaitingManager.o: PartnerWaitingManager.cpp ../PlayerCreature.h \
 ../Creature.h ../Object.h ../../../Core/Types.h \
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
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 ../../../Core/Assert.h ../EffectManager.h ../Effect.h ../../Timeval.h \
 /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 ../InventorySlot.h ../Item.h /usr/include/c++/7/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/c++/7/backward/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../PCFinder.h ../NPC.h ../Zone.h \
 ../Tile.h ../Obstacle.h ../Portal.h ../quest/TriggerManager.h \
 ../quest/Trigger.h ../quest/Condition.h ../quest/PropertyBuffer.h \
 ../Sector.h ../Party.h ../../../Core/ModifyInfo.h ../PCManager.h \
 ../CreatureManager.h ../../../Core/Encrypter.h \
 ../../../Core/EncryptUtility.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 ../Inventory.h ../VolumeInfo.h ../couple/PartnerWaitingManager.h \
 /usr/include/c++/7/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 WaitForMeet.h PartnerWaitingManager.h WaitForApart.h \
 ../VariableManager.h ../../../Core/Gpackets/GCNPCResponse.h
CoupleManager.o: CoupleManager.cpp ../../database/DatabaseManager.h \
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
 /usr/include/c++/7/backward/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_vector.h /home/darkeden/src/libs/stl_hash_map.h \
 ../../database/Connection.h /usr/local/include/mysql/mysql.h \
 /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 ../../database/DB.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/i386-linux-gnu/sys/time.h ../PlayerCreature.h \
 ../Creature.h ../Object.h ../../../Core/Assert.h ../EffectManager.h \
 ../Effect.h ../../Timeval.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../ObjectRegistry.h ../InventorySlot.h \
 ../Item.h /usr/include/c++/7/vector /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_bvector.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /home/darkeden/src/libs/slist /home/darkeden/src/libs/stl_slist.h CoupleManager.h
WaitForMeet.o: WaitForMeet.cpp ../../../Core/Assert.h \
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
 ../../../Core/Player.h ../GamePlayer.h \
 ../../../Core/SocketEncryptOutputStream.h \
 ../../../Core/SocketOutputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 ../../../Core/SocketEncryptInputStream.h \
 ../../../Core/SocketInputStream.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 /usr/include/STL/deque /home/darkeden/src/libs/stl_range_errors.h \
 /home/darkeden/src/libs/stl_deque.h ../../../Core/Packet.h ../../Timeval.h \
 /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/PlayerStatus.h ../EventManager.h \
 ../Event.h ../skill/Skill.h ../../PaySystem.h \
 ../../../Core/VSDateTime.h ../billing/BillingPlayerInfo.h \
 ../../chinabilling/CBillingPlayerInfo.h \
 ../../chinabilling/CBillingInfo.h \
 ../../../Core/Gpackets/GCReconnectLogin.h \
 ../../../Core/PacketFactory.h /usr/include/c++/7/bitset \
 ../gameguard/CSAuth.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../Object.h ../EffectManager.h ../Effect.h ../../../Core/EffectInfo.h \
 ../ObjectRegistry.h ../InventorySlot.h ../Item.h \
 /usr/include/c++/7/vector /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/c++/7/backward/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../Zone.h ../Tile.h ../Obstacle.h \
 ../Portal.h ../quest/TriggerManager.h ../quest/Trigger.h \
 ../quest/Condition.h ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_queue.h ../Inventory.h \
 ../VolumeInfo.h ../../../Core/PCSlayerInfo.h ../../../Core/PCInfo.h \
 ../../../Core/PCSlayerInfo2.h ../../../Core/PCSlayerInfo3.h \
 ../../../Core/InventoryInfo.h ../../../Core/InventorySlotInfo.h \
 ../../../Core/PCItemInfo.h ../../../Core/SubItemInfo.h \
 ../ItemLoaderManager.h ../ItemLoader.h ../../../Core/GearInfo.h \
 ../../../Core/GearSlotInfo.h ../../../Core/ExtraInfo.h \
 ../../../Core/ExtraSlotInfo.h ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/c++/7/cstdio \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../PacketUtil.h ../../../Core/ItemNameInfo.h ../FlagSet.h \
 ../StringPool.h WaitForMeet.h PartnerWaitingManager.h CoupleManager.h \
 ../VariableManager.h ../item/CoupleRing.h ../item/CoupleRingBase.h \
 ../ItemInfo.h ../InfoClassManager.h ../ItemFactory.h \
 ../item/VampireCoupleRing.h ../ItemFactoryManager.h \
 ../../../Core/Gpackets/GCCreateItem.h \
 ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Gpackets/GCSystemMessage.h
WaitForApart.o: WaitForApart.cpp ../../../Core/Assert.h \
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
 ../../../Core/Player.h ../Slayer.h ../PlayerCreature.h ../Creature.h \
 ../Object.h ../EffectManager.h ../Effect.h ../../Timeval.h \
 /usr/include/i386-linux-gnu/sys/time.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h /usr/include/i386-linux-gnu/bits/confname.h \
 /usr/include/getopt.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/c++/7/bitset ../ObjectRegistry.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/initspin.h /usr/lib/i386-linux-gnu/perl/5.26.1/bits/sigthread.ph \
 ../InventorySlot.h ../Item.h /usr/include/c++/7/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h ../Garbage.h ../RankBonus.h \
 ../ExpFwd.h ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/c++/7/backward/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /home/darkeden/src/libs/slist \
 /home/darkeden/src/libs/stl_slist.h ../Zone.h ../Tile.h ../Obstacle.h \
 ../Portal.h ../quest/TriggerManager.h ../quest/Trigger.h \
 ../quest/Condition.h ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../Inventory.h ../VolumeInfo.h \
 ../../../Core/PCSlayerInfo.h ../../../Core/PCInfo.h \
 ../../../Core/PCSlayerInfo2.h ../../../Core/PCSlayerInfo3.h \
 ../../../Core/InventoryInfo.h ../../../Core/InventorySlotInfo.h \
 ../../../Core/PCItemInfo.h ../../../Core/SubItemInfo.h \
 ../ItemLoaderManager.h ../ItemLoader.h ../../../Core/GearInfo.h \
 ../../../Core/GearSlotInfo.h ../../../Core/ExtraInfo.h \
 ../../../Core/ExtraSlotInfo.h ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/PCSkillInfo.h \
 ../../../Core/SubSlayerSkillInfo.h ../CreatureUtil.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/c++/7/cstdio \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../PacketUtil.h ../../../Core/ItemNameInfo.h ../FlagSet.h \
 ../StringPool.h WaitForApart.h PartnerWaitingManager.h \
 CoupleManager.h ../item/CoupleRing.h ../item/CoupleRingBase.h \
 ../ItemInfo.h ../InfoClassManager.h ../ItemFactory.h \
 ../item/VampireCoupleRing.h ../ItemFactoryManager.h \
 ../../../Core/Gpackets/GCCreateItem.h \
 ../../../Core/Gpackets/GCDeleteInventoryItem.h \
 ../../../Core/Gpackets/GCRemoveFromGear.h \
 ../../../Core/Gpackets/GCNPCResponse.h \
 ../../../Core/Gpackets/GCSystemMessage.h
