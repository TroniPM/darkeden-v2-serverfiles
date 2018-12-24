//--------------------------------------------------------------------------------
// 
// Filename    : GCAddMonsterCorpse.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_MONSTER_CORPSE_H__
#define __GC_ADD_MONSTER_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCAddMonsterCorpse;
//
//--------------------------------------------------------------------------------

class GCAddMonsterCorpse : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_MONSTER_CORPSE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddMonsterCorpsePacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID + 
			szMonsterType + 
			szBYTE +
			m_MonsterName.size() +
			szCoord + 
			szCoord + 
			szDir + 
			szbool +
			szBYTE +
			szObjectID +  
			szLevel;			//  Level
	}

	// get packet's name
	string getPacketName() const throw() { return "GCAddMonsterCorpse"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set creature ID 
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set monster type
	MonsterType_t getMonsterType() const throw() { return m_MonsterType; }
	void setMonsterType(MonsterType_t monsterType) throw() { m_MonsterType = monsterType; }

	// get/set monster name
	string getMonsterName() const throw() { return m_MonsterName; }
	void setMonsterName(string name) throw() { m_MonsterName = name; }

	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	// get/set Dir
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }

	bool gethasHead() const throw() { return m_bhasHead; }
	void sethasHead(bool bhasHead) throw() { m_bhasHead = bhasHead; }

	// get/set Treasure Count
	BYTE getTreasureCount() const throw() { return m_TreasureCount; }
	void setTreasureCount(BYTE Count) throw() { m_TreasureCount = Count; }

	ObjectID_t getLastKiller() const { return m_LastKiller; }
	void setLastKiller( ObjectID_t id ) { m_LastKiller = id; }

	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t CLevel) throw() { m_Level = CLevel; }


private :
	
    ObjectID_t m_ObjectID;			// OID

	MonsterType_t m_MonsterType; 	// ���� Ÿ��

	string m_MonsterName;

   	Coord_t m_X;					// X ��ǥ
	Coord_t m_Y;					// Y ��ǥ
	Dir_t m_Dir;					// ����
	bool m_bhasHead;				// �Ӹ��� �ִ°�?
	
	BYTE m_TreasureCount;

	ObjectID_t m_LastKiller;

	Level_t	m_Level;	// Level

};


//--------------------------------------------------------------------------------
//
// class GCAddMonsterCorpseFactory;
//
// Factory for GCAddMonsterCorpse
//
//--------------------------------------------------------------------------------

class GCAddMonsterCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddMonsterCorpse(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddMonsterCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_MONSTER_CORPSE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddMonsterCorpsePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID + 
			szMonsterType + 
			szBYTE + 
			128 +
			szCoord + 
			szCoord + 
			szDir + 
			szbool +
 			szBYTE +
			szObjectID +  
			szLevel;			//  Level
	}

};


//--------------------------------------------------------------------------------
//
// class GCAddMonsterCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddMonsterCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddMonsterCorpse* pPacket, Player* pPlayer) throw(Error);

};

#endif
