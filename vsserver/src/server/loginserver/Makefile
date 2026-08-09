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
LIBS     = -L$(LIBDIR) -lLoginServerDatabase -lLoginServerPackets -lServerCore -lCore -lLoginServerBilling -lLoginServerCBilling -lcpsso  -lstlport_gcc
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
all : $(TARGET)

# libLoginServerBilling.a é gerado pelo Makefile de gameserver/billing
# (target allloginserver). Como o loginserver linka essa lib, garantimos
# que ela exista antes do link (o billing roda com -D__LOGIN_SERVER__).
$(LIBDIR)/libLoginServerBilling.a :
	$(MAKE) -C $(BILLINGDIR) allloginserver

$(TARGET) : $(OBJS) $(LIBDIR)/libLoginServerDatabase.a $(LIBDIR)/libLoginServerPackets.a $(LIBDIR)/libServerCore.a $(LIBDIR)/libCore.a $(LIBDIR)/libcpsso.a $(LIBDIR)/libLoginServerBilling.a $(LIBDIR)/libLoginServerCBilling.a
	$(CC) -o $@ $(OBJS) $(LIBS) $(SYSLIBS) 
clean :
	rm -rf *.o

cleanall :
	rm -rf *.o $(TARGET)

depall :
	gccmakedep $(SRCS) $(INCLUDES)

dep :
	gccmakedep $(SRCS) $(INCLUDES)
