//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDeleteandPickUpOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DELETE_AND_PICKUP_OK_H__
#define __GC_DELETE_AND_PICKUP_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOK;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOK : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_DELETE_AND_PICKUP_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCDeleteandPickUpOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

	// get packet name
	string getPacketName() const throw() { return "GCDeleteandPickUpOK"; }
	
	// get packet's debug string
	string toString() const throw();
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOKFactory;
//
// Factory for GCDeleteandPickUpOK
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDeleteandPickUpOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCDeleteandPickUpOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_DELETE_AND_PICKUP_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCDeleteandPickUpOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteandPickUpOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteandPickUpOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCDeleteandPickUpOK* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
