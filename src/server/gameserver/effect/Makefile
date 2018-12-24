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

SRCS = $(OBJS:.o=.cpp)

TARGET = effect


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