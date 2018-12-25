#--------------------------------------------------------------------------------
#
# Filename    : Makefile
# Written By  : Reiot
#
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Directories
#--------------------------------------------------------------------------------
VSHOME  = ../../..
STLDIR  = /usr/include/STL
BINDIR  = $(VSHOME)/bin
LIBDIR  = $(VSHOME)/lib
SRCDIR  = $(VSHOME)/src
COREDIR = ..
SERVDIR = ../../server
DBDIR   = $(SERVDIR)/database
GSDIR   = $(SERVDIR)/gameserver
LSDIR   = $(SERVDIR)/loginserver
SSDIR	= $(SERVDIR)/sharedserver
CLIDIR  = ../../client
LCCDIR  = $(CLIDIR)/linux/console


#--------------------------------------------------------------------------------
# General Rules
#--------------------------------------------------------------------------------
.SUFFIXES : .cpp .gs.o .ls.o .ss.o

CC       = g++
DEFS     = -D__LINUX__ -D_REENTRANT
INCLUDES = -I$(STLDIR) -I$(COREDIR)
CCFLAGS  = -Wall -c -g 
#CCFLAGS  = -Wall -c -g 

TARGET1 = $(LIBDIR)/libGameServerPackets.a
TARGET2 = $(LIBDIR)/libLoginServerPackets.a
TARGET3 = $(LIBDIR)/libLinuxConsoleClientPackets.a
TARGET4 = $(LIBDIR)/libSharedServerPackets.a

OBJS1	= \
		RCSay.gs.o RCSayHandler.gs.o

OBJS2	= \
		RCSay.ls.o RCSayHandler.ls.o

OBJS4	= \
		RCSay.ss.o RCSayHandler.ss.o

SRCS	= $(OBJS1:.gs.o=.cpp)

.cpp.gs.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__GAME_SERVER__ $(INCLUDES) -I$(SERVDIR) -I$(GSDIR) -I$(DBDIR) -o $*.gs.o $<

.cpp.ls.o : 
	$(CC) $(CCFLAGS) $(DEFS) -D__LOGIN_SERVER__ $(INCLUDES) -I$(SERVDIR) -I$(LSDIR) -I$(DBDIR) -o $*.ls.o $<

.cpp.ss.o :
	$(CC) $(CCFLAGS) $(DEFS) -D__SHARED_SERVER__ $(INCLUDES) -I$(SERVDIR) -I$(SSDIR) -I$(DBDIR) -o $*.ss.o $<

#--------------------------------------------------------------------------------
# Actions
#--------------------------------------------------------------------------------

#all : $(TARGET1) $(TARGET2) $(TARGET3)
all : $(TARGET1) $(TARGET2) $(TARGET4)

allloginserver : $(TARGET2)

allgameserver : $(TARGET1)

allsharedserver : $(TARGET4)

$(TARGET1) : $(OBJS1)
	ar r $@ $(OBJS1)

$(TARGET2) : $(OBJS2)
	ar r $@ $(OBJS2)

$(TARGET3) : $(OBJS3)
	ar r $@ $(OBJS3)

$(TARGET4) : $(OBJS4)
	ar r $@ $(OBJS4)

clean :
	rm -rf *.o

cleanloginserver :
	rm -rf *.ls.o

cleangameserver :
	rm -rf *.gs.o

cleansharedserver :
	rm -rf *.ss.o

cleanall :
	rm -rf *.o

depall :
	gccmakedep $(SRCS) $(INCLUDES) $(DEFS)

dep :
	gccmakedep $(SRCS) $(INCLUDES) $(DEFS)

# DO NOT DELETE
RCSay.o: RCSay.cpp RCSay.h ../DatagramPacket.h ../Packet.h ../Types.h \
 ../types/SystemTypes.h /usr/include/c++/7/iostream \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../Utility.h ../Exception.h ../StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 ../SocketOutputStream.h ../Datagram.h ../PacketFactory.h
RCSayHandler.o: RCSayHandler.cpp RCSay.h ../DatagramPacket.h \
 ../Packet.h ../Types.h ../types/SystemTypes.h \
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
 /home/darkeden/src/libs/stl_hash_fun.h ../types/PlayerTypes.h \
 ../types/ObjectTypes.h ../types/CreatureTypes.h ../types/ItemTypes.h \
 ../types/ZoneTypes.h ../types/QuestTypes.h ../types/ShopTypes.h \
 ../types/GuildTypes.h ../Utility.h ../Exception.h ../StringStream.h \
 /usr/include/c++/7/list /home/darkeden/src/libs/stl_list.h \
 ../SocketInputStream.h ../Socket.h ../SocketImpl.h ../SocketAPI.h \
 ../SocketOutputStream.h ../Datagram.h ../PacketFactory.h
