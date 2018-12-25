//////////////////////////////////////////////////////////////////////////////
// Filename    : Creature.h
// Written By  : reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Object.h"
#include "EffectManager.h"
#include "Assert.h"
#include "Timeval.h"
#include <stdlib.h>
#include <algorithm>
#include <bitset>

//////////////////////////////////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////////////////////////////////

#define DEFAULT_SIGHT			13	// �����þ�
#define DARKNESS_SIGHT			0	// Darkness�� ���� �þ�
#define YELLOW_POISON_SIGHT		3	// Yellow Poison�� ���� �þ�
#define LIGHTNESS_SIGHT			13	// Lightness�� ���� �þ�
#define FLARE_SIGHT				3	// Flare�� ���� �þ�


const string MoveMode2String [] = 
{
	"MOVE_MODE_WALKING",
	"MOVE_MODE_FLYING",
	"MOVE_MODE_BURROWING"
};

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Zone;
class Player;
class Inventory;
class Stash;
class InventorySlot;
class Party;
class LocalPartyManager;

//////////////////////////////////////////////////////////////////////////////
// Class Creature;
//////////////////////////////////////////////////////////////////////////////

class Creature : public Object 
{
public:
	// Creature�� �ٷ� ��ӹ޴� Ŭ�������� ���⿡ �����Ѵ�.
	enum CreatureClass 
	{ 
		CREATURE_CLASS_SLAYER = 0,	// PC Slayer
		CREATURE_CLASS_VAMPIRE,		// PC Vampire
		CREATURE_CLASS_NPC,			// NPC
		CREATURE_CLASS_MONSTER,		// NPC Slayer, NPC Vampire
		CREATURE_CLASS_OUSTERS,		// PC Ousters
		CREATURE_CLASS_MAX
	};

	// Move Mode
	enum MoveMode 
	{
		MOVE_MODE_WALKING = 0,
		MOVE_MODE_FLYING,
		MOVE_MODE_BURROWING,
		MOVE_MODE_MAX
	};

public:
    Creature(ObjectID_t objectID = 0, Player* pPlayer = NULL) throw();
    virtual ~Creature() throw (Error);

public:
	virtual ObjectClass getObjectClass()  { return OBJECT_CLASS_CREATURE; }
	virtual ObjectPriority getObjectPriority() ;
	virtual string toString()  = 0;

public:
	virtual bool load() throw (InvalidProtocolException, Error) = 0; // load from DB
	virtual void save() const throw(Error) = 0; // save to DB
	
public:
	// ũ��ó���� �÷��̾�� �����Ѵ�.
	// ���� ũ��ó�� ���ؼ� isPC()�� üũ�غ��� true �� ��쿡�� ȣ���ؾ� �Ѵ�.
	Player* getPlayer() const throw(Error) { Assert(m_pPlayer != NULL); return m_pPlayer; }
	void setPlayer(Player* pPlayer) throw() { m_pPlayer = pPlayer; }

public:
	virtual const string& getName()  = 0;

	virtual CreatureClass getCreatureClass()  = 0;
	virtual string getCreatureClassString()  = 0;

	virtual Race_t getRace() const = 0;

	EffectManager* getEffectManager()  { return m_pEffectManager; }

	bool isSlayer()   { return getCreatureClass() == CREATURE_CLASS_SLAYER; }
	bool isVampire()  { return getCreatureClass() == CREATURE_CLASS_VAMPIRE; }
	bool isOusters()  { return getCreatureClass() == CREATURE_CLASS_OUSTERS; }
	bool isNPC()      { return getCreatureClass() == CREATURE_CLASS_NPC; }
	bool isMonster()  { return getCreatureClass() == CREATURE_CLASS_MONSTER; }
	bool isPC()       { return isSlayer() || isVampire() || isOusters(); }

	bool isGOD()      { return getCompetence() == GOD; }
	bool isDM()       { return getCompetence() == DM; }
	bool isHELPER()   { return getCompetence() == HELPER; }
	bool isPLAYER()   { return getCompetence() == PLAYER; }

	virtual BYTE getCompetence()  { return PLAYER; }
	virtual BYTE getCompetenceShape()  { return 1; }

	virtual bool isDead()  = 0;
	virtual bool isAlive()  = 0;
	void recoverHP(HP_t recoverAmount) throw();

	void setFlag(Effect::EffectClass Flag) throw() { m_Flag.set(Flag); }
	void removeFlag(Effect::EffectClass Flag) throw() { m_Flag.reset(Flag); }
	bool isFlag(Effect::EffectClass Flag)  { return m_Flag.test(Flag); } 

	bool hasRelicItem() const;

public:
    virtual PhoneNumber_t getPhoneNumber()  { return 0; }

public:
	virtual void act(const Timeval& currentTime) throw(Error) = 0; // for monster & npc

public:

	////////////////////////////////////////////////////////////
	// Creature�� ������ �ִ� �����۵� ���� Zone�� ��ϵǾ�� �Ѵ�. 
	// �̸� ���ؼ��� ���� �����۵��� Zone�������� visible�ؾ� �ϴµ�, 
	// �׷��� ���ϴ�. �׷��ٰ�, Zone���� Creature�� ���� �����۵��� 
	// iteration �ϴ� �޽�带 �����ϴ� �͵� ����ϴ�. 
	// ����, Creature�� ��� �޽�带 �ΰ� ���⼭ Zone�� �����ؼ� 
	// �����θ� ����ϵ��� �� ���̴�. 
	////////////////////////////////////////////////////////////
	virtual void registerObject() throw(Error) = 0;

	// ũ��ó�� ���� Ư�� ��ǥ�� �þ� ���¸� �����Ѵ�.
	VisionState getVisionState(ZoneCoord_t x, ZoneCoord_t y) throw(Error); 
	VisionState getVisionState(Coord_t x, Coord_t y, Sight_t sight) throw(Error);

	// get/set zone
	Zone* getZone()  { return m_pZone; }
	void setZone(Zone* pZone) throw() { m_pZone = pZone; }

	// get/set zone id
	ZoneID_t getZoneID() ;
	void setZoneID(ZoneID_t zoneID) throw(Error);

	// get/set(x,y,dir)
	ZoneCoord_t getX()  { return m_X; }
	void setX(ZoneCoord_t x) throw() { m_X = x; }

	ZoneCoord_t getY()  { return m_Y; }
	void setY(ZoneCoord_t y) throw() { m_Y = y; }

	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }

	ZoneCoord_t getViewportWidth()  { return m_ViewportWidth; }
	ZoneCoord_t getViewportUpperHeight()  { return m_ViewportUpperHeight; }
	ZoneCoord_t getViewportLowerHeight()  { return m_ViewportLowerHeight; }

	////////////////////////////////////////////////////////////
	// *CAUTION*
	// ���� ����� ������ ��, 2�� �̻��� ���� ���ÿ� �����ϴ� set �޽��� ������� �� ��!
	//(�Լ� ȣ���� �ڿ��� ���� �̷�����ٴ� ����� ������ ��!)
	//  ex> setXY(pResult->getInt(++i), pResult->getInt(++i)); �� ������ setXY(y,x)
	//      �� �����ϰ� �ȴ�... -_-;
	////////////////////////////////////////////////////////////
	void setXY(ZoneCoord_t x, ZoneCoord_t y) throw() { m_X = x; m_Y = y; }
	void setXYDir(ZoneCoord_t x, ZoneCoord_t y, Dir_t dir) throw() { m_X = x; m_Y = y; m_Dir = dir; }

	//(nx,ny)�� ������ �� �ִ°�?
	bool canMove(ZoneCoord_t nx, ZoneCoord_t ny) ;
	bool isBlockedByCreature(ZoneCoord_t nx , ZoneCoord_t ny) ;

	// get/set sight level
	Sight_t getSight()  { return m_Sight; }
	void setSight(Sight_t sight) throw(Error) { m_Sight = sight; Assert(m_Sight <= maxSight); }

	virtual Sight_t getEffectedSight() throw();

	// get/set/test move mode
	MoveMode getMoveMode()  { return m_MoveMode; }
	void setMoveMode(MoveMode moveMode) throw() { m_MoveMode = moveMode; }

	bool isWalking()  { return m_MoveMode == MOVE_MODE_WALKING; }
	bool isFlying()  { return m_MoveMode == MOVE_MODE_FLYING; }
	bool isBurrowing()  { return m_MoveMode == MOVE_MODE_BURROWING; }
	
	// get distance
	Distance_t getDistance(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2) ;

	// P(x1,y1)�� ���� ��ġ������ �Ÿ��� �����Ѵ�.
	Distance_t getDistance(ZoneCoord_t x1, ZoneCoord_t y1) ;

	// get/set EffectInfo
	virtual EffectInfo* getEffectInfo()  { return m_pEffectManager->getEffectInfo(); }

public :
	// get/set zone
	Zone* getNewZone()  { return m_pNewZone; }
	void setNewZone(Zone* pZone) throw() { m_pNewZone = pZone; }

	// get/set zone id
	ZoneID_t getNewZoneID() ;
	//void setNewZoneID(ZoneID_t zoneID) throw(Error);

	// get/set(x,y,dir)
	ZoneCoord_t getNewX()  { return m_NewX; }
	void setNewX(ZoneCoord_t x) throw() { m_NewX = x; }

	ZoneCoord_t getNewY()  { return m_NewY; }
	void setNewY(ZoneCoord_t y) throw() { m_NewY = y; }

	void setNewXY(ZoneCoord_t x, ZoneCoord_t y) throw() { m_NewX = x; m_NewY = y; }

public:
	bool isEffect(Effect::EffectClass EClass) throw (Error);
	void deleteEffect(Effect::EffectClass EClass) throw (Error);
	Effect* findEffect(Effect::EffectClass EClass) ;
	void addEffect(Effect* pEffect) throw (Error);

public:
	virtual Level_t getLevel()  = 0;
	virtual Steal_t getHPStealAmount(void) const { return 0; }
	virtual void setHPStealAmount(Steal_t steal) {}

	virtual Steal_t getMPStealAmount(void) const { return 0; }
	virtual void setMPStealAmount(Steal_t steal) {}

	virtual Steal_t getHPStealRatio(void) const { return 0; }
	virtual void setHPStealRatio(Steal_t steal) {}

	virtual Steal_t getMPStealRatio(void) const { return 0; }
	virtual void setMPStealRatio(Steal_t steal) {}

	virtual Regen_t getHPRegen(void) const { return 0; }
	virtual void setHPRegen(Regen_t regen) {}

	virtual Regen_t getMPRegen(void) const { return 0; }
	virtual void setMPRegen(Regen_t regen) {}

	virtual Luck_t getLuck(void) const { return 0; }
	virtual void setLuck(Luck_t luck) {}

	virtual int getCriticalRatio(void) const { return 0; }
	virtual void setCriticalRatio(int ratio) { }

	int getPartyID(void) const { return m_PartyID; }
	void setPartyID(int ID) { m_PartyID = ID; }

	LocalPartyManager* getLocalPartyManager(void) ;

	virtual ClanType_t getClanType(void) const { return 0; }
	virtual void setClanType(ClanType_t clan) { }

	Resist_t getResist(uint domain) { return m_Resist[domain]; }
	void setResist(uint domain, Resist_t value) { m_Resist[domain] = value; }

	ObjectID_t getLastTarget() { return m_LastTarget; }
	virtual void setLastTarget(ObjectID_t value) { m_LastTarget = value; }

protected:
	Player*                          m_pPlayer;                  // Player �� ���� ������(Mob �� NPC �� ��� NULL)
	MoveMode                         m_MoveMode;                 // Move Mode
	Zone*                            m_pZone;                    // ���� ���� ���� ������
	ZoneCoord_t                      m_X;                        // �� x ��ǥ
	ZoneCoord_t                      m_Y;                        // �� y ��ǥ
	Dir_t                            m_Dir;                      // ���� ����
	ZoneCoord_t                      m_ViewportWidth;            // �� ��Ʈ 
	ZoneCoord_t                      m_ViewportUpperHeight;      // �� ��Ʈ
	ZoneCoord_t                      m_ViewportLowerHeight;      // �� ��Ʈ
	EffectManager*                   m_pEffectManager;           // effect manager point
	bitset<Effect::EFFECT_CLASS_MAX> m_Flag;                     // effect flag
	Sight_t                          m_Sight;                    // current sight
	int                              m_PartyID;                  // partyid
	Resist_t                         m_Resist[MAGIC_DOMAIN_MAX]; // ���� ���׷�

	// ���� �� ��, ��Ȱ�� ��. by sigi. 2002.5.11
	Zone*                            m_pNewZone;           // ���� ���� ���� ������
	ZoneCoord_t                      m_NewX;               // �� x ��ǥ
	ZoneCoord_t                      m_NewY;               // �� y ��ǥ

	// ����׿�
	CreatureClass 					 m_CClass;
	string							 m_Owner;
	bool							 m_bDeriveDestructed;
	int								 m_Value;

	ObjectID_t						 m_LastTarget;

public:
	void setValue(int value) { m_Value = value; }
};

#endif
