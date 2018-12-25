//----------------------------------------------------------------------
// 
// Filename    : GCAddOustersCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_OUSTERS_CORPSE_H__
#define __GC_ADD_OUSTERS_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCOustersInfo3.h"


//----------------------------------------------------------------------
//
// class GCAddOustersCorpse;
//
//----------------------------------------------------------------------

class GCAddOustersCorpse : public Packet {

public :

	// constructor
	GCAddOustersCorpse() throw() { m_TreasureCount = 0; }
	GCAddOustersCorpse(const PCOustersInfo3 & oustersInfo) throw() : m_OustersInfo(oustersInfo) {}

	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_ADD_OUSTERS_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return m_OustersInfo.getSize() + szBYTE; }

	// get packet's name
	string getPacketName()  { return "GCAddOustersCorpse"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get ousters info
	PCOustersInfo3 & getOustersInfo() throw() { return m_OustersInfo; }
	const PCOustersInfo3 & getOustersInfo()  { return m_OustersInfo; }
	void setOustersInfo(const PCOustersInfo3 & oustersInfo) throw() { m_OustersInfo = oustersInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount()  { return m_TreasureCount; }
	void setTreasureCount(BYTE Count) throw() { m_TreasureCount = Count; }
	
private :
	
	PCOustersInfo3 m_OustersInfo;

	BYTE m_TreasureCount;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddOustersCorpseFactory;
//
// Factory for GCAddOustersCorpse
//
//--------------------------------------------------------------------------------

class GCAddOustersCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddOustersCorpse(); }

	// get packet name
	string getPacketName()  { return "GCAddOustersCorpse"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_OUSTERS_CORPSE; }

	// get packet's body size
	PacketSize_t getPacketMaxSize()  { return PCOustersInfo3::getMaxSize() + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class GCAddOustersCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddOustersCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddOustersCorpse* pPacket, Player* pPlayer) throw(Error);

};

#endif
