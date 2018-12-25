
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectBloodBible.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_BLOOD_BIBLE_H__
#define __CG_SELECT_BLOOD_BIBLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBible;
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBible : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SELECT_BLOOD_BIBLE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szItemType; }

	// get packet name
	string getPacketName()  { return "CGSelectBloodBible"; }

	// get packet's debug string
	string toString() ;

	// get/set BloodBibleID
	ItemType_t getBloodBibleID()  { return m_BloodBibleID; }
	void setBloodBibleID( ItemType_t BloodBibleID ) throw() { m_BloodBibleID = BloodBibleID; }


private :

	// BloodBible ID
	ItemType_t m_BloodBibleID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBibleFactory;
//
// Factory for CGSelectBloodBible
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBibleFactory : public PacketFactory {

public:
	
	// constructor
	CGSelectBloodBibleFactory() throw() {}
	
	// destructor
	virtual ~CGSelectBloodBibleFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSelectBloodBible(); }

	// get packet name
	string getPacketName()  { return "CGSelectBloodBible"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SELECT_BLOOD_BIBLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szItemType; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGSelectBloodBibleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectBloodBibleHandler {

public:

	// execute packet's handler
	static void execute(CGSelectBloodBible* pCGSelectBloodBible, Player* pPlayer);

};

#endif
