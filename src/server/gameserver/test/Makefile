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
SKILLDIR = ../skill
GSDIR    = ..
MYSQLDIR = /usr/local/lib/mysql
CPPUNITDIR = /usr/local/include/cppunit


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(CPPUNITDIR) -I.
#CCFLAGS  = -Wall -c -g  
CCFLAGS  = -Wall -c -g 

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

OBJS = \
	GameServerTest.o \
	GameServerTester.o \
	GameServerSkillTest.o \
	GameServerExpTest.o \
	GameServerItemTest.o \
	GameServerWarTest.o \
	GameServerSpeedCheckTest.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(LIBDIR)/libGameServerTest.a


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
GameServerTest.o: GameServerTest.cpp GameServerTest.h \
 /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
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
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/fstream  \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h TestDef.h
GameServerTester.o: GameServerTester.cpp ../../../Core/Types.h \
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
 ../../../Core/Properties.h /usr/include/STL/map \
 /home/darkeden/src/libs/stl_tree.h /home/darkeden/src/libs/stl_map.h \
 /home/darkeden/src/libs/stl_multimap.h /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 GameServerTest.h /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h TestDef.h \
 GameServerSkillTest.h GameServerExpTest.h GameServerItemTest.h \
 GameServerSpeedCheckTest.h GameServerWarTest.h
GameServerSkillTest.o: GameServerSkillTest.cpp GameServerSkillTest.h \
 GameServerTest.h /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
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
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/fstream  \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h TestDef.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../Object.h ../../../Core/Assert.h ../EffectManager.h \
 ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h /usr/include/STL/bitset \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /usr/include/STL/slist \
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
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h \
 ../skill/SkillHandlerManager.h ../skill/SkillHandler.h ../SkillInfo.h \
 ../Vampire.h ../../../Core/PCVampireInfo.h \
 ../../../Core/PCVampireInfo2.h ../../../Core/PCVampireInfo3.h \
 ../../../Core/VampireSkillInfo.h ../../../Core/SubVampireSkillInfo.h \
 ../skill/VampireSkillSlot.h ../Ousters.h \
 ../../../Core/PCOustersInfo.h ../../../Core/PCOustersInfo2.h \
 ../../../Core/PCOustersInfo3.h ../../../Core/OustersSkillInfo.h \
 ../../../Core/SubOustersSkillInfo.h ../skill/OustersSkillSlot.h \
 ../Monster.h ../MonsterInfo.h ../MonsterSummonInfo.h \
 ../MonsterInfoTypes.h ../Treasure.h ../PrecedenceTable.h \
 ../skill/HitRoll.h ../skill/SkillUtil.h ../ZoneUtil.h \
 ../../../Core/VSDateTime.h ../GamePlayer.h ../../../Core/Player.h \
 ../../../Core/SocketEncryptOutputStream.h \
 ../../../Core/SocketEncryptInputStream.h /usr/include/STL/deque \
 ../../../Core/PlayerStatus.h ../EventManager.h ../Event.h \
 ../../PaySystem.h ../billing/BillingPlayerInfo.h \
 ../../chinabilling/CBillingPlayerInfo.h \
 ../../chinabilling/CBillingInfo.h \
 ../../../Core/Gpackets/GCReconnectLogin.h ../gameguard/CSAuth.h \
 ../../Thread.h ../../pthreadAPI.h MockSkillInput.h
GameServerExpTest.o: GameServerExpTest.cpp GameServerExpTest.h \
 GameServerTest.h /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
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
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/fstream  \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h TestDef.h ../skill/SkillUtil.h \
 ../../../Core/ModifyInfo.h ../../../Core/Packet.h \
 ../../../Core/SocketInputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/SocketOutputStream.h ../Slayer.h ../PlayerCreature.h \
 ../Creature.h ../Object.h ../../../Core/Assert.h ../EffectManager.h \
 ../Effect.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../../Core/EffectInfo.h /usr/include/STL/bitset \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Item.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /usr/include/STL/slist \
 /home/darkeden/src/libs/stl_slist.h ../Zone.h ../Tile.h ../Obstacle.h \
 ../Portal.h ../quest/TriggerManager.h ../quest/Trigger.h \
 ../quest/Condition.h ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../PCManager.h ../CreatureManager.h ../../../Core/Encrypter.h \
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
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../skill/Skill.h ../skill/SkillSlot.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Vampire.h \
 ../../../Core/PCVampireInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/SubVampireSkillInfo.h ../skill/VampireSkillSlot.h \
 ../Ousters.h ../../../Core/PCOustersInfo.h \
 ../../../Core/PCOustersInfo2.h ../../../Core/PCOustersInfo3.h \
 ../../../Core/OustersSkillInfo.h ../../../Core/SubOustersSkillInfo.h \
 ../skill/OustersSkillSlot.h ../VariableManager.h
GameServerItemTest.o: GameServerItemTest.cpp GameServerItemTest.h \
 GameServerTest.h /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
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
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/fstream  \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h TestDef.h ../Item.h ../Object.h \
 ../../../Core/Assert.h ../Effect.h ../../Timeval.h \
 /usr/include/sys/time.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h ../EffectManager.h ../../../Core/EffectInfo.h \
 ../../../Core/Packet.h ../../../Core/SocketInputStream.h \
 ../../../Core/Socket.h ../../../Core/SocketImpl.h \
 ../../../Core/SocketAPI.h ../../../Core/SocketOutputStream.h \
 /usr/include/STL/bitset ../VariableManager.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h ../ItemFactoryManager.h \
 ../ItemFactory.h ../Vampire.h ../PlayerCreature.h ../Creature.h \
 ../ObjectRegistry.h ../../Mutex.h /usr/include/pthread.h \
 /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 ../InventorySlot.h ../Garbage.h ../RankBonus.h ../ExpFwd.h \
 ../../../Core/Gpackets/GCMonsterKillQuestInfo.h \
 ../../../Core/PacketFactory.h \
 ../../../Core/Gpackets/GCSelectQuestID.h ../OptionInfo.h \
 /usr/include/STL/slist /home/darkeden/src/libs/stl_slist.h ../Inventory.h \
 ../VolumeInfo.h ../Zone.h ../Tile.h ../Obstacle.h ../Portal.h \
 ../quest/TriggerManager.h ../quest/Trigger.h ../quest/Condition.h \
 ../quest/PropertyBuffer.h ../Sector.h ../Party.h \
 ../../../Core/ModifyInfo.h ../PCManager.h ../CreatureManager.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 /usr/include/STL/queue /home/darkeden/src/libs/stl_deque.h \
 /home/darkeden/src/libs/stl_queue.h ../../../Core/PCVampireInfo.h \
 ../../../Core/PCInfo.h ../../../Core/PCVampireInfo2.h \
 ../../../Core/PCVampireInfo3.h ../../../Core/InventoryInfo.h \
 ../../../Core/InventorySlotInfo.h ../../../Core/PCItemInfo.h \
 ../../../Core/SubItemInfo.h ../../../Core/GearInfo.h \
 ../../../Core/GearSlotInfo.h ../../../Core/ExtraInfo.h \
 ../../../Core/ExtraSlotInfo.h ../../../Core/VampireSkillInfo.h \
 ../../../Core/PCSkillInfo.h ../../../Core/SubVampireSkillInfo.h \
 ../CreatureUtil.h ../skill/VampireSkillSlot.h ../skill/Skill.h \
 ../../../Core/Gpackets/GCModifyInformation.h ../Slayer.h \
 ../../../Core/PCSlayerInfo.h ../../../Core/PCSlayerInfo2.h \
 ../../../Core/PCSlayerInfo3.h ../ItemLoaderManager.h ../ItemLoader.h \
 ../../../Core/RideMotorcycleInfo.h \
 ../../../Core/RideMotorcycleSlotInfo.h \
 ../../../Core/SlayerSkillInfo.h ../../../Core/SubSlayerSkillInfo.h \
 ../SlayerAttrExpTable.h ../SomethingGrowingUp.h ../../database/DB.h \
 ../../database/DatabaseManager.h ../../database/Connection.h \
 /usr/local/include/mysql/mysql.h /usr/local/include/mysql/mysql_com.h \
 /usr/local/include/mysql/mysql_version.h ../../database/Statement.h \
 ../../database/Result.h /usr/include/STL/cstdio \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h ../skill/SkillSlot.h ../ZoneUtil.h \
 ../../../Core/VSDateTime.h ../ItemUtil.h
GameServerWarTest.o: GameServerWarTest.cpp GameServerWarTest.h \
 GameServerTest.h /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
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
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/fstream  \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h TestDef.h ../../../Core/VSDateTime.h
GameServerSpeedCheckTest.o: GameServerSpeedCheckTest.cpp \
 GameServerSpeedCheckTest.h GameServerTest.h \
 /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/c++/7/string \
 /home/darkeden/src/libs/stl_config.h /home/darkeden/src/libs/stl_string_fwd.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stddef.h \
 /home/darkeden/src/libs/stl_alloc.h \
 /usr/include/c++/7/new \
 /usr/include/c++/7/exception \
 /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h /usr/include/i386-linux-gnu/bits/sched.h \
 /usr/include/time.h /usr/include/endian.h /usr/include/i386-linux-gnu/bits/endian.h \
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
  /usr/include/c++/7/streambuf \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/include/i386-linux-gnu/bits/wchar.h /usr/include/gconv.h \
 /usr/lib/gcc/i686-linux-gnu/7/include/stdarg.h \
 /home/darkeden/src/libs/stl_iterator.h /home/darkeden/src/libs/stl_construct.h \
 /home/darkeden/src/libs/stl_tempbuf.h /home/darkeden/src/libs/stl_uninitialized.h \
 /home/darkeden/src/libs/stl_raw_storage_iter.h /usr/include/c++/7/algorithm \
 /home/darkeden/src/libs/stl_algo.h /home/darkeden/src/libs/stl_heap.h \
 /usr/include/c++/7/bits/char_traits.h /usr/include/stdio.h \
 /home/darkeden/src/libs/stl_hash_fun.h /usr/include/STL/strstream \
 /usr/include/STL/strstream.h /usr/include/STL/strfile.h \
 /usr/local/include/cppunit/extensions/AutoRegisterSuite.h \
 /usr/local/include/cppunit/extensions/TestSuiteFactory.h \
 /usr/local/include/cppunit/extensions/TestFactory.h \
 /usr/local/include/cppunit/extensions/TestFactoryRegistry.h \
 /usr/include/STL/map /home/darkeden/src/libs/stl_tree.h \
 /home/darkeden/src/libs/stl_map.h /home/darkeden/src/libs/stl_multimap.h \
 /usr/local/include/cppunit/extensions/TestSuiteBuilder.h \
 /usr/local/include/cppunit/TestSuite.h \
 /usr/local/include/cppunit/Test.h /usr/include/STL/vector \
 /home/darkeden/src/libs/stl_range_errors.h /home/darkeden/src/libs/stl_vector.h \
 /home/darkeden/src/libs/stl_bvector.h \
 /usr/local/include/cppunit/TestCaller.h \
 /usr/local/include/cppunit/Exception.h \
 /usr/local/include/cppunit/SourceLine.h \
 /usr/local/include/cppunit/TestCase.h \
 /usr/local/include/cppunit/TestAssert.h \
 /usr/local/include/cppunit/Asserter.h \
 /usr/local/include/cppunit/TestFixture.h \
 /usr/local/include/cppunit/extensions/TypeInfoHelper.h \
 /usr/lib/gcc-lib/i686-redhat-linux/2.95.3/include/typeinfo \
 /usr/local/include/cppunit/TextTestRunner.h \
 /usr/local/include/cppunit/ui/text/TestRunner.h ../../../Core/Types.h \
 ../../../Core/types/SystemTypes.h /usr/include/c++/7/iostream \
 /usr/include/c++/7/fstream  \
 ../../../Core/types/PlayerTypes.h ../../../Core/types/ObjectTypes.h \
 ../../../Core/types/CreatureTypes.h ../../../Core/types/ItemTypes.h \
 ../../../Core/types/ZoneTypes.h ../../../Core/types/QuestTypes.h \
 ../../../Core/types/ShopTypes.h ../../../Core/types/GuildTypes.h \
 ../../../Core/types/WarTypes.h ../../../Core/types/ServerType.h \
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h TestDef.h ../GamePlayer.h \
 ../../../Core/Player.h ../../../Core/SocketEncryptOutputStream.h \
 ../../../Core/SocketOutputStream.h ../../../Core/Socket.h \
 ../../../Core/SocketImpl.h ../../../Core/SocketAPI.h \
 ../../../Core/Encrypter.h ../../../Core/EncryptUtility.h \
 ../../../Core/SocketEncryptInputStream.h \
 ../../../Core/SocketInputStream.h ../../Mutex.h \
 /usr/include/pthread.h /usr/include/sched.h /usr/include/signal.h \
 /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
 /usr/include/STL/deque /home/darkeden/src/libs/stl_deque.h \
 ../../../Core/Packet.h ../../Timeval.h /usr/include/sys/time.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/confname.h /usr/include/getopt.h \
 ../../../Core/PlayerStatus.h ../EventManager.h ../Event.h \
 ../skill/Skill.h ../../PaySystem.h ../../../Core/VSDateTime.h \
 ../billing/BillingPlayerInfo.h \
 ../../chinabilling/CBillingPlayerInfo.h \
 ../../chinabilling/CBillingInfo.h \
 ../../../Core/Gpackets/GCReconnectLogin.h \
 ../../../Core/PacketFactory.h /usr/include/STL/bitset \
 ../gameguard/CSAuth.h ../../../Core/Cpackets/CGVerifyTime.h
