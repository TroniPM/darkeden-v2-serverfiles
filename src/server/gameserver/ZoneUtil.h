//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneUtil.h
// Written by  : excel96
// Description : 
// ���� ���õ� Ư���� �۾����� �����ϴ� �Լ����� �� �ȿ� �����ϱ�,
// �� ������ �ʹ� Ŀ���� ������ �־, �� ���� �ܺη� ���� �Լ����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZONE_UTIL_H__
#define __ZONE_UTIL_H__

#include "Types.h"
#include "Exception.h"
#include "Creature.h"
#include "Effect.h"
#include "VSDateTime.h"
#include <list>

// forward declaration
class Zone;
class Mine;
class Effect;
class PlayerCreature;
class Item;
class Monster;
class Slayer;
class Corpse;

struct ZONE_COORD;
struct SUMMON_INFO;

// �������� ��ȯ
struct SUMMON_INFO2;

//////////////////////////////////////////////////////////////////////////////
// Ư�� ũ���ĸ� ���� �� �ִ� ��ġ�� ã�´�.
// 
// Zone*       pZone        : ���� ���� ������
// ZoneCoord_t cx           : ���ϰ��� �ϴ� �ʱ� ��ġ x
// ZoneCoord_t cy           : ���ϰ��� �ϴ� �ʱ� ��ġ y
// Creature::MoveMode MMode : ũ������ ������ ���
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePosition
(
	Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, Creature::MoveMode MMode
) throw();


//////////////////////////////////////////////////////////////////////////////
// Ư�� �������� ���� �� �ִ� ��ġ�� ã�´�.
//
// Zone*       pZone          : ���� ���� ������
// ZoneCoord_t cx             : ���ϰ��� �ϴ� �ʱ� ��ġ x
// ZoneCoord_t cy             : ���ϰ��� �ϴ� �ʱ� ��ġ y
// bool        bAllowCreature : ũ���İ� �����ϴ� ���� ��������?
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePositionForItem
(
	Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature, bool bAllowSafeZone = true, bool bForce = false
) throw();

//////////////////////////////////////////////////////////////////////////////
// Ư�� ����Ʈ�� ���� �� �ִ� ��ġ�� ã�´�.
//
// Zone*       pZone          : ���� ���� ������
// ZoneCoord_t cx             : ���ϰ��� �ϴ� �ʱ� ��ġ x
// ZoneCoord_t cy             : ���ϰ��� �ϴ� �ʱ� ��ġ y
// Effect::EffectClass EClass : ���ϰ��� �ϴ� ����Ʈ Ŭ����
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePositionForEffect
(
	Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, Effect::EffectClass EClass
) throw();

//////////////////////////////////////////////////////////////////////////////
// Ư�� ��ġ���� ������ ���� ����� ũ���ĸ� �߰��� �� �ִ��� �˻��Ѵ�.
//
// Zone*              pZone : ���� ���� ������
// ZoneCoord_t        x     : ���ο��ϰ��� �ϴ� ��ǥ x
// ZoneCoord_t        y     : ���ο��ϰ��� �ϴ� ��ǥ y
// Creature::MoveMode MMode : ũ������ ���� ���
//////////////////////////////////////////////////////////////////////////////
bool canAddCreature
(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature::MoveMode MMode
) throw();


//////////////////////////////////////////////////////////////////////////////
// Ư�� ��ġ�� ���ο찡 �������� üũ�� �Ѵ�. 
//
// Zone* pZone   : ���� ���� ������
// ZoneCoord_t x : ���ο��ϰ��� �ϴ� ��ǥ x
// ZoneCoord_t y : ���ο��ϰ��� �ϴ� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
bool canBurrow
(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y
) throw();


//////////////////////////////////////////////////////////////////////////////
// Ư�� ��ġ�� ����ο찡 �������� üũ�� �Ѵ�.
//
// Zone* pZone   : ���� ���� ������
// ZoneCoord_t x : ���ο��ϰ��� �ϴ� ��ǥ x
// ZoneCoord_t y : ���ο��ϰ��� �ϴ� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
bool canUnburrow
(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y
) throw();


//////////////////////////////////////////////////////////////////////////////
// ũ���ĸ� �ڷ� �������� �Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : �������� �� ũ����
// ZoneCoord_t originX   : pCreature�� �������� �� ������ ��ǥ x
// ZoneCoord_t originY   : pCreature�� �������� �� ������ ��ǥ y
//////////////////////////////////////////////////////////////////////////////
Dir_t knockbackCreature
(
	Zone* pZone, Creature* pCreature, 
	ZoneCoord_t originX, ZoneCoord_t originY
) throw(ProtocolException, Error);


//////////////////////////////////////////////////////////////////////////////
// ���̵带 �� ũ���ĸ� ������ �߰��Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : ���̵带 �� ũ����
// ZoneCoord_t cx        : ũ������ ���� ��ǥ x 
// ZoneCoord_t cy        : ũ������ ���� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
void addBurrowingCreature
(
	Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy
) throw(EmptyTileNotExistException, Error);


//////////////////////////////////////////////////////////////////////////////
// ���̵带 Ǭ ũ���ĸ� ������ �߰��Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : ���̵带 Ǭ ũ����
// ZoneCoord_t cx        : ũ������ ���� ��ǥ x
// ZoneCoord_t cy        : ũ������ ���� ��ǥ y
// Dir_t       dir       : ���� ũ���İ� ���� ����
//////////////////////////////////////////////////////////////////////////////
void addUnburrowCreature
(
	Zone* pZone, Creature* pCreature, 
	ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir 
) throw(EmptyTileNotExistException, Error);


//////////////////////////////////////////////////////////////////////////////
// ������ Ǭ ũ���ĸ� ������ �߰��Ѵ�.
//
// Zone*     pZone     : ���� ���� ������
// Creature* pCreature : ������ Ǭ ũ����
// bool      bForce    : ����Ʈ�� duration�� ���Ⱑ ���� �ʾҴµ�,
//                       ������ Ǫ�� ���ΰ�?
//////////////////////////////////////////////////////////////////////////////
void addUntransformCreature 
(
	Zone* pZone, Creature* pCreature, bool bForce
) throw();


//////////////////////////////////////////////////////////////////////////////
// �� ���̴� ũ���ĸ� �߰��Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : �� ���̴� ũ����
// ZoneCoord_t cx        : ũ������ ���� ��ǥ x
// ZoneCoord_t cy        : ũ������ ���� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
void addInvisibleCreature
(
	Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy
) throw();


//////////////////////////////////////////////////////////////////////////////
// �� ���̴� ũ���İ� ���� ���, �� ũ���ĸ� �߰��Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : �� ���̴� ũ����
// bool        bForce    : ������ visible ���°� �Ǿ���?
//////////////////////////////////////////////////////////////////////////////
void addVisibleCreature
(
	Zone* pZone, Creature* pCreature, bool bForced
) throw();


//////////////////////////////////////////////////////////////////////////////
// �������� ����� ũ���ĸ� �߰��Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : �� ���̴� ũ����
// ZoneCoord_t cx        : ũ������ ���� ��ǥ x
// ZoneCoord_t cy        : ũ������ ���� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
void addSnipingModeCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy) throw();


//////////////////////////////////////////////////////////////////////////////
// �� ���̴� ũ���İ� ���� ���, �� ũ���ĸ� �߰��Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : �� ���̴� ũ����
// bool        bForce    : ������ visible ���°� �Ǿ���?
//////////////////////////////////////////////////////////////////////////////
void addUnSnipingModeCreature(Zone* pZone, Creature* pCreature, bool bForced) throw();


//////////////////////////////////////////////////////////////////////////////
// ������ ���ڸ� ���Ѵ�.
//
// Zone*       pZone : ���� ���� ������
// Mine*       pMine : ���� ��ü�� ���� ������
// ZoneCoord_t cx    : ���ڸ� ���� ��ǥ x
// ZoneCoord_t cy    : ���ڸ� ���� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
void addInstalledMine(Zone* pZone, Mine* pMine, ZoneCoord_t cx, ZoneCoord_t cy) throw();


//////////////////////////////////////////////////////////////////////////////
// Ư�� ũ���İ� ���ڸ� ���� �ʾҴ��� üũ�Ѵ�.
//
// Zone*       pZone     : ���� ���� ������
// Creature*   pCreature : �˻��� ũ����
// ZoneCoord_t X         : �˻��� ��ǥ x
// ZoneCoord_t Y         : �˻��� ��ǥ y
//////////////////////////////////////////////////////////////////////////////
bool checkMine(Zone* pZone, Creature* pCreature, ZoneCoord_t X, ZoneCoord_t Y) throw();
bool checkMine(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y ) throw();

bool checkTrap(Zone* pZone, Creature* pCreature);

//////////////////////////////////////////////////////////////////////////////
// Ư�� ũ���ĸ� �ٸ� ������ �̵���Ų��.
//
// Creature*   pCreature    : �̵��� ũ����
// ZoneID_t    TargetZoneID : �̵��� �� ID
// ZoneCoord_t TargetX      : �̵��� �� ��ǥ X
// ZoneCoord_t TargetY      : �̵��� �� ��ǥ Y
// bool        bSendMoveOK  : GCMoveOK�� �����ִ°��� ���� ����
//////////////////////////////////////////////////////////////////////////////
void transportCreature(
	Creature* pCreature, ZoneID_t TargetZoneID, ZoneCoord_t TX, ZoneCoord_t TY, bool bSendMoveOK = true
) throw();


//////////////////////////////////////////////////////////////////////////////
// Ư�� ��ID�� ���� ���� ã�Ƽ� �����͸� �����Ѵ�.
// ZoneID_t ZID : ã���� �ϴ� �� ID
//////////////////////////////////////////////////////////////////////////////
Zone* getZoneByZoneID(ZoneID_t ZID) throw(Error);

//////////////////////////////////////////////////////////////////////////////
// ��� ��ɾ�μ�, Ư�� Ÿ���� ���͸� ������ �߰��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void addMonstersToZone(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, SpriteType_t SType, MonsterType_t MType, int num, const SUMMON_INFO& summonInfo, list<Monster*>* pSummonedMonsters=NULL
) throw();

void addMonstersToZone(
	Zone* pZone, const SUMMON_INFO2& summonInfo, list<Monster*>* pSummonedMonsters=NULL
) throw();

//////////////////////////////////////////////////////////////////////////////
// Ư�� ũ���İ� ���� ���� ���� ���ο� �ִ°��� �˻��ϴ� �Լ�
// ��ȯ�� �� ���δ�. 
//////////////////////////////////////////////////////////////////////////////
bool isInSafeZone(Creature* pCreature);

//////////////////////////////////////////////////////////////////////////////
// ��ǥ�� ���� ���� �������� üũ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
bool isValidZoneCoord(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, int offset=0);

//////////////////////////////////////////////////////////////////////////////
// master lair ��  pCreature�� �� �� �ִ°�?
//////////////////////////////////////////////////////////////////////////////
bool enterMasterLair(Zone* pZone, Creature* pCreature) throw (Error);

// ������ɺο��� �ʺ��ڵ��� �ٸ� ������ ������.. ��ǥ ���� ����
void checkNewbieTransportToGuild(Slayer* pSlayer);
void getNewbieTransportZoneInfo(Slayer* pSlayer, ZONE_COORD& zoneInfo);

// Corpse�� Zone�� �߰��Ѵ�.
bool addCorpseToZone(Corpse* pCorpse, Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy) throw (Error);

// ���� �ȿ� Ư���� ���� ��ü�� �ִ��� Ȯ���Ѵ�. 
// ������ true, ������ false
bool checkCorpse( Zone* pZone, MonsterType_t MType, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2 ) throw();

void makeZoneIDList(const string& zoneIDs, list<ZoneID_t>& zoneIDList ) throw(Error);

uint getZoneTimeband( Zone* pZone );

bool createBulletinBoard( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, MonsterType_t type, const string& msg, const VSDateTime& timeLimit );
void loadBulletinBoard( Zone* pZone );

void forbidDarkness( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, int range );

#endif
