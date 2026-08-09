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
	QuestInfo.o \
	MonsterKillQuestInfo.o \
	GatherItemQuestInfo.o \
	MeetNPCQuestInfo.o \
	RewardClass.o \
	RandomRewardClass.o \
	SlayerWeaponRewardClass.o \
	AnotherQuestRewardClass.o \
	RewardInfo.o \
	ItemRewardInfo.o \
	QuestAdvanceRewardInfo.o \
	AnotherQuestRewardInfo.o \
	MiniGameQuestInfo.o \
	QuestInfoManager.o \
	SimpleQuestInfoManager.o \
	EventQuestInfoManager.o \
	RewardClassInfoManager.o \
	SimpleQuestRewardManager.o \
	QuestManager.o \
	QuestStatus.o \
	MonsterKillQuestStatus.o \
	GatherItemQuestStatus.o \
	DummyQuestStatus.o \
	MeetNPCQuestStatus.o \
	MiniGameQuestStatus.o \
	EventQuestAdvance.o \
	EventQuestLootingManager.o

SRCS = $(OBJS:.o=.cpp)

TARGET = $(LIBDIR)/libMission.a

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
