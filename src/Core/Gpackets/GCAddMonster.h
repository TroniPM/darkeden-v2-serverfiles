//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddMonster.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_MONSTER_H__
#define __GC_ADD_MONSTER_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddMonster;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonster : public Packet 
{
public:
	GCAddMonster();
	virtual ~GCAddMonster();

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_MONSTER; }
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID +            // object id
			szMonsterType +            // monster type
			szBYTE +                   // monster name length
			m_MonsterName.size() +     // monster name
			szColor +                  // monster main color
			szColor +                  // sub color
			szCoord +                  // x coord.
			szCoord +                  // y coord.
			szDir +                    // monster direction
			m_pEffectInfo->getSize() + // effects info on monster
			szHP +                     // current hp
			szHP +                      // max hp
			szLevel +			//  Level
			szBYTE;						// from Flag
	}
	string getPacketName()  { return "GCAddMonster"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	MonsterType_t getMonsterType()  { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType) throw() { m_MonsterType = monsterType; }

	string getMonsterName()  { return m_MonsterName; }
	void setMonsterName(string name) throw() { m_MonsterName = name; }

	Color_t getMainColor()  { return m_MainColor; }
	void setMainColor(Color_t color) throw() { m_MainColor = color; }

	Color_t getSubColor()  { return m_SubColor; }
	void setSubColor(Color_t color) throw() { m_SubColor = color; }

	Coord_t getX()  { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }

	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	HP_t getMaxHP()  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) throw() { m_MaxHP = MaxHP; }

	HP_t getCurrentHP()  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t CLevel) throw() { m_Level = CLevel; }

	BYTE getFromFlag(void) const { return m_FromFlag; }
	void setFromFlag(BYTE flag) { m_FromFlag = flag; }

private:
    ObjectID_t    m_ObjectID;     // object id
	MonsterType_t m_MonsterType;  // monster type
	string        m_MonsterName;  // monster name
	Color_t       m_MainColor;    // monster main color
	Color_t       m_SubColor;     // sub color
   	Coord_t       m_X;            // x coord.
	Coord_t       m_Y;            // y coord.
	Dir_t         m_Dir;          // monster direction
	EffectInfo*   m_pEffectInfo;  // effects info on monster
	HP_t          m_CurrentHP;    // current hp
	HP_t          m_MaxHP;        // max hp
	Level_t	m_Level;	// Level
	BYTE           m_FromFlag;    // ���κ����ΰ�? ������ ��쿡�� 0, ��Ż�� ������ ��쿡�� 1
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddMonster(); }

	// get packet name
	string getPacketName()  { return "GCAddMonster"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_MONSTER; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddMonsterPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szObjectID +            // object id
			szMonsterType +            // monster type
			szBYTE +                   // monster name length
			32 +                       // monster name max
			szColor +                  // monster main color
			szColor +                  // sub color
			szCoord +                  // x coord.
			szCoord +                  // y coord.
			szDir +                    // monster direction
			EffectInfo::getMaxSize() + // effects info on monster
			szHP +                     // current hp
			szHP +                      // max hp
			szLevel +			//  Level
			szBYTE;						// from Flag
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterHandler {

public :

	// execute packet's handler
	static void execute(GCAddMonster* pPacket, Player* pPlayer);

};

#endif
