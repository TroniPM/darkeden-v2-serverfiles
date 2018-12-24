//////////////////////////////////////////////////////////////////////////////
// Filename    : PacketUtil.h
// Written by  : excel96
// Description : 
// ���� ������, ����Ⱑ ������ ��Ŷ�� ����� ���� ���� �ϳ��� ���������ν�,
// ���������� ��������.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PACKETUTIL_H__
#define __PACKETUTIL_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////

class Creature;
class Slayer;
class Vampire;
class Ousters;
class Monster;
class NPC;
class Item;
class SlayerCorpse;
class VampireCorpse;
class OustersCorpse;
class MonsterCorpse;
class SLAYER_RECORD;
class VAMPIRE_RECORD;
class OUSTERS_RECORD;
class GamePlayer;
class PlayerCreature;

class GCUpdateInfo;
class GCAddSlayer;
class GCAddVampire;
class GCAddOusters;
class GCAddMonster;
class GCAddNPC;
class GCAddNewItemToZone;
class GCDropItemToZone;
class GCAddSlayerCorpse;
class GCAddVampireCorpse;
class GCAddMonsterCorpse;
class GCAddOustersCorpse;
class GCOtherModifyInfo;
class GCCreateItem;
class GCWarScheduleList;
class GCMiniGameScores;
class GCPetStashList;
class GCModifyInformation;
class GCLoadInventory;
class GCLoadGear;

//class GCItemNameInfoList;

//////////////////////////////////////////////////////////////////////////////
// function headers
//////////////////////////////////////////////////////////////////////////////

// MOdifyInformation �� ��忬�������� ����� �ִ´�.
void makeGCModifyInfoGuildUnion(GCModifyInformation* pModifyInformation, Creature* pCreature) throw();
void makeGCOtherModifyInfoGuildUnion(GCOtherModifyInfo* pModifyInformation, Creature* pCreature) throw();
void sendGCOtherModifyInfoGuildUnion(Creature* pTargetCreature) throw();
void sendGCOtherModifyInfoGuildUnionByGuildID(uint gID) throw();
	
	
// ��Ż�̳�, �׾ �� ���̸� �̵��� �� ����, GCUpdateInfo ������ �����Ѵ�.
void makeGCUpdateInfo(GCUpdateInfo* pUpdateInfo, Creature* pCreature) throw();
// ��Ŷ ��Ȱ �κ��丮 ����
void makeGCLoadInventory(GCLoadInventory* pUpdateInfo, Creature* pCreature, int Type) throw();

// ��Ŷ ��Ȱ ��� ����
void makeGCLoadGear(GCLoadGear* pUpdateInfo, Creature* pCreature, int Type) throw();

// �����̾� �߰� ��Ŷ�� �����Ѵ�.
void makeGCAddSlayer(GCAddSlayer* pAddSlayer, Slayer* pSlayer) throw();

// �����̾� �߰� ��Ŷ�� �����Ѵ�.
void makeGCAddVampire(GCAddVampire* pAddVampire, Vampire* pVampire) throw();

// �ƿ콺�ͽ� �߰� ��Ŷ�� �����Ѵ�.
void makeGCAddOusters(GCAddOusters* pAddOusters, Ousters* pOusters) throw();

// ���� �߰� ��Ŷ�� �����Ѵ�.
void makeGCAddMonster(GCAddMonster* pAddMonster, Monster* pMonster) throw();

// NPc �߰� ��Ŷ�� �����Ѵ�.
void makeGCAddNPC(GCAddNPC* pAddNPC, NPC* pNPC) throw();

// ���ο� �������� ������ �߰��� �� ������ GCAddNewItemToZone�� �����Ѵ�.
void makeGCAddNewItemToZone(GCAddNewItemToZone* pAddItem, Item* pItem, int X, int Y) throw();

// ���ο� �������� ������ �߰��� �� ������ GCAddNewItemToZone�� �����Ѵ�.
void makeGCDropItemToZone(GCDropItemToZone* pAddItem, Item* pItem, int X, int Y) throw();

// ������ �����̾� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
void makeGCAddSlayerCorpse(GCAddSlayerCorpse* pAddSlayerCorpse, SlayerCorpse* pSlayerCorpse) throw();

// ������ �����̾� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
void makeGCAddVampireCorpse(GCAddVampireCorpse* pAddVampireCorpse, VampireCorpse* pVampireCorpse) throw();

// ������ ���� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
void makeGCAddMonsterCorpse(GCAddMonsterCorpse* pAddMonsterCorpse, MonsterCorpse* pMonsterCorpse, int X, int Y) throw();

// ������ �ƿ콺���� ��ü�� �߰��� �� ������ ��Ŷ�� �����Ѵ�.
void makeGCAddOustersCorpse(GCAddOustersCorpse* pAddOustersCorpse, OustersCorpse* pOustersCorpse) throw();

// �ٸ� ����� �ִ� ü�� ���� ���� ����Ǿ��� ��쿡 ���ư��� GCOtherModifyInfo�� �����Ѵ�.
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Slayer* pSlayer, const SLAYER_RECORD* prev);
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Vampire* pVampire, const VAMPIRE_RECORD* prev);
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Ousters* pOusters, const OUSTERS_RECORD* prev);

// ��� ���� ���� ������ �����ش�.
void sendPayInfo(GamePlayer* pGamePlayer) throw(Error);

// ������ ����
void makeGCCreateItem(GCCreateItem* pGCCreateItem, Item* pItem, CoordInven_t x, CoordInven_t y) throw(Error);

// ���� �� ����Ʈ�� �����ش�.
void sendEffectLevelUp(Creature* pCreature) throw (Error);

// GamePlayer���� GCSystemMessage(msg)�� ������. incoming�� �ִ� ���� zone�� ���� �ѷ��ش�.
void sendSystemMessage(GamePlayer* pGamePlayer, const string& msg) throw (Error);

bool makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList, ZoneID_t zoneID) throw(Error);

// �̸��� �ٴ� ������ ������ �����ִ� ��Ŷ
//void makeGCItemNameInfoList(GCItemNameInfoList* pInfo, PlayerCreature* pPC) throw(Error);

void sendGCMiniGameScores( PlayerCreature* pPC, BYTE gameType, BYTE Level );

void makeGCPetStashList( GCPetStashList* pPacket, PlayerCreature* pPC );

#endif
