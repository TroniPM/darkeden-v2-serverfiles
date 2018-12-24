//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillUtil.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILLUTIL_H__
#define __SKILLUTIL_H__

#include "ModifyInfo.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

//////////////////////////////////////////////////////////////////////////////
// ��ũ��, ���
//////////////////////////////////////////////////////////////////////////////

// decreaseMana�� ȣ������ ���, 
// MP�� ������� CONSUME_MP��, HP�� ����� ��쿡�� CONSUME_HP��,
// �� �� �Ҹ�Ǿ��� ��쿡��, BOTH�� �����Ѵ�.
#define CONSUME_MP    0
#define CONSUME_HP    1
#define CONSUME_BOTH  2

#define ATTACK_BURST_MAX 3000
#define DEFENSE_BURST_MAX 2000
#define PARTY_BURST_MAX 20000

#define MAKEWORD(U,D) (WORD)((WORD)(U)<<8  |(WORD)(D))
#define MAKEDWORD(U,D)(DWORD)((DWORD)(U)<<16 |(DWORD)(D))

//#define VAMPIRE_MAX_LEVEL	150

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;
class Monster;
class SkillInfo;
class SkillSlot;
class VampireSkillSlot;
class Item;
class Zone;

//////////////////////////////////////////////////////////////////////////////
// ������ ��� �Լ�
//////////////////////////////////////////////////////////////////////////////

// �����ڿ� �ǰ����� ������ �Ķ���͸� ����� ���� �������� �����Ѵ�.
Damage_t computeDamage(Creature* pCreature, Creature* pTargetCreature);

// �������� ���� �������� ����Ѵ�.
Damage_t computePureDamage(Creature* pCreature);

// �����ڿ� �ǰ����� ������ �Ķ���͸� ����� ���� �������� �����Ѵ�.
// ���� �Լ��� ������, �� �Լ��� �θ� ��쿡�� ���������� ũ��Ƽ�� ��Ʈ�� ���õ� �κ��� ó���ȴ�.
Damage_t computeDamage(Creature* pCreature, Creature* pTargetCreature, int CriticalBonus, bool& bCritical);

// ��??���������� �����ؼ��� ������ ���� �������� �����Ѵ�.
double computeFinalDamage(Damage_t minDamage, Damage_t maxDamage, Damage_t realDamage, Protection_t Protection, bool bCritical);

// �����̾� �����ڿ� �ǰ����� ������ �������� ����Ѵ�.
Damage_t computeSlayerDamage(Slayer* pSlayer, Creature* pTargetCreature, bool bCritical);

// �����̾� �����ڿ� �ǰ����� ������ �������� ����Ѵ�.
Damage_t computeVampireDamage(Vampire* pVampire, Creature* pTargetCreature, bool bCritical);

// �ƿ콺�ͽ� �����ڿ� �ǰ����� ������ �������� ����Ѵ�.
Damage_t computeOustersDamage(Ousters* pOusters, Creature* pTargetCreature, bool bCritical);

// ���� �����ڿ� �ǰ����� ������ �������� ����Ѵ�.
Damage_t computeMonsterDamage(Monster* pMonster, Creature* pTargetCreature, bool bCritical);

// �����̾� �������� ���� �������� ����Ѵ�.
Damage_t computePureSlayerDamage(Slayer* pSlayer);

// �����̾� �������� ���� �������� ����Ѵ�.
Damage_t computePureVampireDamage(Vampire* pVampire);

// �ƿ콺�ͽ� �������� ���� �������� ����Ѵ�.
Damage_t computePureOustersDamage(Ousters* pOusters);

// ���� �����ڿ� �ǰ����� ������ �������� ����Ѵ�.
Damage_t computePureMonsterDamage(Monster* pMonster);

// resistance�� ����� ���� �������� ����Ѵ�.
Damage_t computeMagicDamage(Creature* pTargetCreature, int Damage, SkillType_t SkillType, bool bVampire = false, Creature* pAttacker = NULL);

// ����Ʋ���� ����� �ƿ콺���� ���� �������� ����Ѵ�.
Damage_t computeOustersMagicDamage(Ousters* pOusters, Creature* pTargetCreature, int Damage, SkillType_t SkillType);

// Ÿ�ٿ��� ��ġ�� �� �������� ����Ѵ�.
Damage_t computeSlayerSilverDamage(Creature* pCreature, int Damage, ModifyInfo* pMI);

// Critical Magic �� ���� �нú� ��ų�� ���� ������ ��ȭ�� ũ��Ƽ�� ��ȭ�� ����Ѵ�.
void computeCriticalBonus(Ousters* pOusters, SkillType_t skillType, Damage_t& Damage, bool& bCriticalHit);

//////////////////////////////////////////////////////////////////////////////
// ������ ����, ������ ����߸��� ���...
//////////////////////////////////////////////////////////////////////////////

// ���������� �������� �����Ѵ�.
HP_t setDamage(Creature* pTargetCreature, Damage_t Damage, Creature* pAttacker, SkillType_t SkillType = 0, ModifyInfo* pMI = NULL, ModifyInfo* pAttackerMI = NULL, bool canKillTarget = true, bool canSteal = true );

// ������ �������� ����߸���.
void decreaseDurability(Creature* pCreature, Creature* pTargetCreature, SkillInfo* pSkillInfo, ModifyInfo*, ModifyInfo*);

// Ÿ���� ���� ���ɼ��� �ִ°�?
bool canHit(Creature* pAttacker, Creature* pDefender, SkillType_t SkillType, SkillLevel_t SkillLevel=0);


//////////////////////////////////////////////////////////////////////////////
// ���� ���� �Լ���...
//////////////////////////////////////////////////////////////////////////////

// ��Ʈ�� ���� ���� �Ҹ��� ���ϴ� �����̾� ������ ���� �Ҹ��� ����Ѵ�.
MP_t decreaseConsumeMP(Vampire* pVampire, SkillInfo* pSkillInfo);

// ����� ����ϱ� ���� ����� ������ ������ �ִ°�?
bool hasEnoughMana(Creature* pCaster, int RequiredMP);

// ������ ���δ�.
int decreaseMana(Creature* pCaster, int MP, ModifyInfo& modifyinfo);


//////////////////////////////////////////////////////////////////////////////
// �����Ÿ�, ���ӽð�, �ð�üũ ���� ���� �Լ���...
//////////////////////////////////////////////////////////////////////////////

// �����̾�� ��ų�� �����Ÿ��� ���Ѵ�.
Range_t computeSkillRange(SkillSlot* pSkillSlot, SkillInfo* pSkillInfo);

//(OX,OY)��(TX,TY) ������ �Ÿ��� ���Ѵ�.
Range_t getDistance(ZoneCoord_t OX, ZoneCoord_t OY, ZoneCoord_t TX, ZoneCoord_t TY);

// ��ų�� �� �� �ִ� ������ �Ÿ��ΰ��� ����
bool verifyDistance(Creature* pCreature, ZoneCoord_t X, ZoneCoord_t Y, Range_t Distance);

// ��ų�� �� �� �ִ� ������ �Ÿ��ΰ��� ����
bool verifyDistance(Creature* pCreature, Creature* pTargetCreature, Range_t Distance);

// �����̾�� ��ų�� ���� �ð��� �����Ѵ�.
bool verifyRunTime(SkillSlot* pSkillSlot);

// �����̾�� ��ų�� ���� �ð��� �����Ѵ�.
bool verifyRunTime(VampireSkillSlot* pSkillSlot);

// �ƿ콺�ͽ��� ��ų�� ���� �ð��� �����Ѵ�.
bool verifyRunTime(OustersSkillSlot* pSkillSlot);

// �� ���� PK ��å�� ����, PK�� �Ǵ��� �� �Ǵ��ĸ� ���Ѵ�.
bool verifyPK(Creature* pAttacker, Creature* pDefender);

// ����� ����� �� �ִ� ���ΰ�?
// (���� ����� ���, �� ������ üũ�ϴ� �Լ���...)
bool checkZoneLevelToUseSkill(Creature* pCaster);

// X, Y�� �� �ִ� ũ���İ� ������ ����� ������ �޴��� üũ�ϴ� �Լ���.
bool checkZoneLevelToHitTarget(Creature* pTargetCreature);

// ����� �и� �����ΰ�? - 2003. 1. 1. Sequoia
//bool isMeleeSkill(SkillType_t SkillType);

// Magic ����ΰ�?
//bool isMagicSkill(SkillType_t SkillType);
// Physic ����ΰ�?
//bool isPhysicSkill(SkillType_t SkillType);

//////////////////////////////////////////////////////////////////////////////
// ���� ���� �Լ���...
//////////////////////////////////////////////////////////////////////////////

// ������ �����Ѵ�.
// ����� ����ϰų�, PK�� �� �� ����� ���� ��ȭ�� ����ϴ� �Լ���.
void computeAlignmentChange(Creature* pTargetCreature, Damage_t Damage, Creature* pAttacker, ModifyInfo* pMI = NULL, ModifyInfo* pAttackerMI = NULL);

// �����̾� �� �����̾ ���� ���� �� ������ �ణ�� ȸ����Ų��.
// ���� ���� �ý��� ���� �Ͱ��� ���� ����, �׳� Ÿ������ ������ �� 
// �ణ�� ������ ȸ�������ִ� �Լ��̴�.
void increaseAlignment(Creature* pCreature, Creature* pEnemy, ModifyInfo& mi);

//////////////////////////////////////////////////////////////////////////////
// ����ġ ���� �Լ���...
//////////////////////////////////////////////////////////////////////////////

// ��Ƽ ���� �����̾� ����ġ ��� �Լ�
void shareAttrExp(Slayer* pSlayer, Damage_t Damage, BYTE STRMultiplier, BYTE DEXMultiplier, BYTE INTMultiplier, ModifyInfo &);

// ��Ƽ ���� �����̾� ����ġ ��� �Լ�
void shareVampExp(Vampire*, Exp_t, ModifyInfo&);

// ��Ƽ ���� �ƿ콺�ͽ� ����ġ ��� �Լ�
void shareOustersExp(Ousters*, Exp_t, ModifyInfo&);

// �����̾� �ɷ�ġ(STR,DEX,INT) ����ġ�� ����Ѵ�.
void divideAttrExp(Slayer* pSlayer, Damage_t Damage, BYTE STRMultiplier, BYTE DEXMultiplier, BYTE INTMultiplier, ModifyInfo &, int numPartyMember=-1);

// �����̾� ��� ����ġ�� ����Ѵ�.
void increaseSkillExp(Slayer* pSlayer, SkillDomainType_t DomainType, SkillSlot* pSkillSlot, SkillInfo* pSkillInfo, ModifyInfo&);

// �����̾� �迭 ����ġ�� ����Ѵ�.
bool increaseDomainExp(Slayer* pSlayer, SkillDomainType_t Domain, Exp_t Exp, ModifyInfo &, Level_t EnemyLevel = 0, int TargetNum = -1);

// �����̾� ����ġ�� ����Ѵ�.
void increaseVampExp(Vampire*, Exp_t, ModifyInfo&);

// �ƿ콺�ͽ� ����ġ�� ����Ѵ�.
void increaseOustersExp(Ousters*, Exp_t, ModifyInfo&);

// �����̾� �� �����̾� ���� ����Ѵ�.
void increaseFame(Creature* pAttackee, uint amount);

// �ƿ콺�ͽ� ����ġ�� ����Ѵ�.
void increaseAttackBurstPoint(Creature* pAttacker, Creature* pTargetCreature, Attr_t amout);
void increaseDefenseBurstPoint(Creature* pAttacker, Creature* pTargetCreature, Attr_t amout);
void increaseAttackPartyBurstPoint(Creature* pAttacker, Creature* pTargetCreature, Attr_t amout);
void increaseDefensePartyBurstPoint(Creature* pAttacker, Creature* pTargetCreature, Attr_t amout);
// �׿������� ó��
RankExp_t computeRankExp(int myLevel, int otherLevel);
RankExp_t computeRankExp2(int myLevel, int otherLevel);
void affectKillCount(Creature* pAttacker, Creature* pDeadCreature);

//////////////////////////////////////////////////////////////////////////////
// ��Ÿ �Լ���...
//////////////////////////////////////////////////////////////////////////////

// �Ÿ��� ���� SG, SR�� ���ʽ��� ����Ѵ�.
int computeArmsWeaponSplashSize(Item* pWeapon, int ox, int oy, int tx, int ty);
int computeArmsWeaponDamageBonus(Item* pWeapon, int ox, int oy, int tx, int ty);
int computeArmsWeaponToHitBonus(Item* pWeapon, int ox, int oy, int tx, int ty);

// ������ ��ǥ ������ ���÷��� �������� ���� ũ���ĸ� �̾ƿ´�. 
int getSplashVictims(Zone* pZone, int cx, int cy, Creature::CreatureClass CClass, list<Creature*>& creatureList, int splash);
int getSplashVictims(Zone* pZone, int cx, int cy, Creature::CreatureClass CClass, list<Creature*>& creatureList, int splash, int range);
int getSplashVictims(Zone* pZone, int cx, int cy, list<Creature*>& creatureList, int splash);

// ������ �� HP�� MP�� �� ä���ش�.
void healCreatureForLevelUp(Slayer* pSlayer, ModifyInfo& _ModifyInfo, SLAYER_RECORD* prev);
void healCreatureForLevelUp(Vampire* pVampire, ModifyInfo& _ModifyInfo, VAMPIRE_RECORD* prev);
void healCreatureForLevelUp(Ousters* pOusters, ModifyInfo& _ModifyInfo, OUSTERS_RECORD* prev);

// ��� ���н� ��Ŷ�� ������.
void executeSkillFailNormal(Creature* pCreature, SkillType_t SkillType, Creature* pTargetCreature, BYTE Grade = 0);
void executeAbsorbSoulSkillFail(Creature* pCreature, SkillType_t SkillType, ObjectID_t TargetObjectID, bool bBroadcast, bool bSendTwice);
void executeSkillFailNormalWithGun(Creature* pCreature, SkillType_t SkillType, Creature* pTargetCreature, BYTE RemainBullet);
void executeSkillFailException(Creature* pCreature, SkillType_t SkillType, BYTE Grade = 0);

void decreaseHP(Zone* pZone, Creature* pCreature, int Damage, ObjectID_t attackerObjectID=0);

Dir_t getDirectionToPosition(int originX, int originY, int destX, int destY);

Exp_t computeSkillPointBonus(SkillDomainType_t Domain, SkillLevel_t DomainLevel, Item* pWeapon, Exp_t Point);


// ���� �����̸� �ɾ �� �� �ִ°�? ( ũ���ķ� ���� ���� ���� )
bool isPassLine( Zone* pZone, ZoneCoord_t sX, ZoneCoord_t sY, ZoneCoord_t eX, ZoneCoord_t eY, bool blockByCreature = false );

// �� �������� ������ �̷�� ������ ���Ѵ�.
void getLinePoint( ZoneCoord_t sX, ZoneCoord_t sY, ZoneCoord_t eX, ZoneCoord_t eY, list<TPOINT>& tpList );

ElementalType getElementalTypeFromString( const string& type );

Damage_t computeElementalCombatSkill( Ousters* pOusters, Creature* pTargetCreature, ModifyInfo& AttackerMI );

//////////////////////////////////////////////////////////////////////////////
// ������ �� �ִ°�?
// ���� ���³� non PK �� ���ؼ� ������ �� �ִ����� üũ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
bool canAttack( Creature* pAttacker, Creature* pDefender );

//////////////////////////////////////////////////////////////////////////
// add by Coffee 2007-6-9
// �����¼�������ʹ���¼��� �۳����ܿ���֤
//////////////////////////////////////////////////////////////////////////
bool useSkillCrad( Creature* pCreature);


#endif

