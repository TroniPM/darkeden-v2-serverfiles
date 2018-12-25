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
WARDIR	 = ../war
MYSQLDIR = /usr/local/lib/mysql
CPPUNITDIR = /usr/local/include/cppunit


#----------------------------------------------------------------------
# General Rules
#----------------------------------------------------------------------
.SUFFIXES    : .cpp .o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT -D__GAME_SERVER__
INCLUDES = -I. -I$(STLDIR) -I$(COREDIR) -I$(SERVDIR) -I$(DBDIR) -I$(GSDIR) -I$(SKILLDIR) -I$(CPPUNITDIR) -I$(WARDIR)
CCFLAGS  = -Wall -c -g  
#CCFLAGS  = -Wall -c -g 
LIBS	 = #-L$(LIBDIR) -lWar
SYSLIBS  = -lcppunit

.cpp.o :
	$(CC) $(CCFLAGS) $(DEFS) $(INCLUDES) $<

#----------------------------------------------------------------------
# Objects
#----------------------------------------------------------------------

OBJS = \
	main.o \
#	Scheduler.o \
#	Schedule.o \
#	VSDateTime.o \
#	StringStream.o \
#	ScheduleTest.o

SRCS = $(OBJS:.o=.cpp)

TARGET = testAlone


#----------------------------------------------------------------------
# actions
#----------------------------------------------------------------------
all : 
	$(MAKE) $(TARGET)

$(TARGET) : $(OBJS) #$(LIBDIR)/libWar.a
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
main.o: main.cpp ../../../Core/Types.h \
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
 ../../../Core/Utility.h ../../../Core/Exception.h \
 ../../../Core/StringStream.h /usr/include/c++/7/list \
 /home/darkeden/src/libs/stl_list.h /usr/include/bits/stdio_lim.h \
 ScheduleTest.h /usr/local/include/cppunit/extensions/HelperMacros.h \
 /usr/local/include/cppunit/Portability.h \
 /usr/local/include/cppunit/config-auto.h /usr/include/STL/strstream \
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
 /usr/local/include/cppunit/ui/text/TestRunner.h TestDef.h
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
 ../../../Core/Utility.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h Work.h Schedule.h \
 VSDateTime.h ../../../Core/Assert.h
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
 ../../../Core/Utility.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h Work.h Schedule.h \
 VSDateTime.h
VSDateTime.o: VSDateTime.cpp VSDateTime.h
ScheduleTest.o: ScheduleTest.cpp ScheduleTest.h \
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
 ../../../Core/types/WarTypes.h ../../../Core/Utility.h \
 ../../../Core/Exception.h ../../../Core/StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h TestDef.h Work.h \
 Schedule.h VSDateTime.h Scheduler.h /usr/include/STL/queue \
 /home/darkeden/src/libs/stl_deque.h /home/darkeden/src/libs/stl_queue.h \
 /usr/include/STL/hash_map /home/darkeden/src/libs/stl_hashtable.h \
 /home/darkeden/src/libs/stl_hash_map.h /usr/include/unistd.h \
 /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
 /usr/include/getopt.h
