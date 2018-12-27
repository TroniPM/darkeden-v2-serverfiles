//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStatusCurrentHP.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_STATUS_CURRENT_HP_H__
#define __GC_STATUS_CURRENT_HP_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHP;
//
////////////////////////////////////////////////////////////////////

class GCStatusCurrentHP : public Packet {

public :

	GCStatusCurrentHP();

	virtual ~GCStatusCurrentHP();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_STATUS_CURRENT_HP; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCStatusCurrentHPPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID + szHP; 
	}

	// get packet's name
	string getPacketName()  { return "GCStatusCurrentHP"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set creature ID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	// get /set CurrentHP
	HP_t getCurrentHP()  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP)  { m_CurrentHP = CurrentHP; }

private :
	
    // �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
    ObjectID_t m_ObjectID;

	// ���� ���� ü��
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHPFactory;
//
// Factory for GCStatusCurrentHP
//
//////////////////////////////////////////////////////////////////////

class GCStatusCurrentHPFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCStatusCurrentHP(); }

	// get packet name
	string getPacketName()  { return "GCStatusCurrentHP"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_STATUS_CURRENT_HP; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCStatusCurrentHPPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szObjectID + szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCStatusCurrentHPHandler;
//
//////////////////////////////////////////////////////////////////////

class GCStatusCurrentHPHandler {

public :

	// execute packet's handler
	static void execute(GCStatusCurrentHP* pPacket, Player* pPlayer);

};

#endif
