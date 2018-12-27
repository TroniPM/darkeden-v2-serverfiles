//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddMonsterFromTransformation.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_MONSTER_FROM_TRANSFORMATION_H__
#define __GC_ADD_MONSTER_FROM_TRANSFORMATION_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromTransformation;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromTransformation : public Packet 
{
public:
	GCAddMonsterFromTransformation();
	virtual ~GCAddMonsterFromTransformation();
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_MONSTER_FROM_TRANSFORMATION; }
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID + // object id
			szMonsterType + // monster type
			szBYTE + // monster name length
			m_MonsterName.size() + // monster name
			szColor + // monster main color
			szColor +  // monster sub color
			szCoord + // x coord
			szCoord + // y coord
			szDir +  // direction
			m_pEffectInfo->getSize() + // effects info on monster
			szHP* 2 + // current & max hp
			szLevel;			//  Level
	}
	string getPacketName()  { return "GCAddMonsterFromTransformation"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	MonsterType_t getMonsterType()  { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType)  { m_MonsterType = monsterType; }

	string getMonsterName()  { return m_MonsterName; }
	void setMonsterName(string name)  { m_MonsterName = name; }

	Color_t getMainColor()  { return m_MainColor; }
	void setMainColor(Color_t color)  { m_MainColor = color; }

	Color_t getSubColor()  { return m_SubColor; }
	void setSubColor(Color_t color)  { m_SubColor = color; }

	Coord_t getX()  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }

	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo)  { m_pEffectInfo = pEffectInfo; }

	HP_t getMaxHP()  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP)  { m_MaxHP = MaxHP; }

	HP_t getCurrentHP()  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP)  { m_CurrentHP = CurrentHP; }

	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t CLevel)  { m_Level = CLevel; }

private :
    ObjectID_t    m_ObjectID;    // object id
	MonsterType_t m_MonsterType; // monster type
	string        m_MonsterName; // monster name
	Color_t       m_MainColor;   // monster main color
	Color_t       m_SubColor;    // monster sub color
   	Coord_t       m_X;           // x coord.
	Coord_t       m_Y;           // y coord.
	Dir_t         m_Dir;         // monster direction
	EffectInfo*   m_pEffectInfo; // effects info on monster
	HP_t          m_CurrentHP;   // current hp
	HP_t          m_MaxHP;       // maximum hp
	Level_t	m_Level;	// Level
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromTransformationFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromTransformationFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddMonsterFromTransformation(); }
	string getPacketName()  { return "GCAddMonsterFromTransformation"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_MONSTER_FROM_TRANSFORMATION; }
	PacketSize_t getPacketMaxSize()  
	{ 
		return szObjectID               // object id
			+ szMonsterType             // monster type
			+ szBYTE                    // monster name length
			+ 32                        // monster namx max
			+ szColor + szColor         // monster main & sub color 
			+ szCoord + szCoord + szDir // monster x, y coord & direction
			+ EffectInfo::getMaxSize()  // effects info on monster
			+ szHP* 2 + szLevel;                 // current & max hp
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromTransformationHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromTransformationHandler 
{
public:
	static void execute(GCAddMonsterFromTransformation* pPacket, Player* pPlayer);

};

#endif
