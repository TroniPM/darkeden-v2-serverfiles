//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestStoreInfo.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_STORE_INFO_H__
#define __CG_REQUEST_STORE_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestStoreInfo;
//
//////////////////////////////////////////////////////////////////////

class CGRequestStoreInfo : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_STORE_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID; }

	// get packet name
	string getPacketName()  { return "CGRequestStoreInfo"; }

	// get packet's debug string
	string toString() ;

	ObjectID_t	getOwnerObjectID() const { return m_OwnerObjectID; }
	void		setOwnerObjectID(ObjectID_t oid) { m_OwnerObjectID = oid; }

private:
	ObjectID_t	m_OwnerObjectID;	// 0�̸� �ڱ� �ڽ��� ���� ����
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestStoreInfoFactory;
//
// Factory for CGRequestStoreInfo
//
//////////////////////////////////////////////////////////////////////

class CGRequestStoreInfoFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestStoreInfoFactory() throw() {}
	
	// destructor
	virtual ~CGRequestStoreInfoFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestStoreInfo(); }

	// get packet name
	string getPacketName()  { return "CGRequestStoreInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_STORE_INFO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestStoreInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestStoreInfoHandler {

public:

	// execute packet's handler
	static void execute(CGRequestStoreInfo* pCGRequestStoreInfo, Player* pPlayer);

};

#endif
