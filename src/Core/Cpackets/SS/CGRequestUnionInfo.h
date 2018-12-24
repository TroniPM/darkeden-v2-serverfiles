
//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestUnionInfo.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUER_UNION_INFO_H__
#define __CG_REQUER_UNION_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionInfo;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionInfo : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_REQUEST_UNION_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return 0; }

	// get packet name
	string getPacketName() const throw() { return "CGRequestUnionInfo"; }

	// get packet's debug string
	string toString() const throw();


};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionInfoFactory;
//
// Factory for CGRequestUnionInfo
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionInfoFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestUnionInfoFactory() throw() {}
	
	// destructor
	virtual ~CGRequestUnionInfoFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestUnionInfo(); }

	// get packet name
	string getPacketName() const throw() { return "CGRequestUnionInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_REQUEST_UNION_INFO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionInfoHandler {

public:

	// execute packet's handler
	static void execute(CGRequestUnionInfo* pCGRequestUnionInfo, Player* pPlayer) throw(Error);

};

#endif
