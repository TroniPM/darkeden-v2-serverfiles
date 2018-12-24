//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCCannotUse.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_CANNOT_USE_H__
#define __GC_CANNOT_USE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCCannotUse;
//
//////////////////////////////////////////////////////////////////////

class GCCannotUse : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_CANNOT_USE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCCannotUsePacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

	// get packet name
	string getPacketName() const throw() { return "GCCannotUse"; }
	
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
// class GCCannotUseFactory;
//
// Factory for GCCannotUse
//
//////////////////////////////////////////////////////////////////////

class GCCannotUseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCCannotUse(); }

	// get packet name
	string getPacketName() const throw() { return "GCCannotUse"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CANNOT_USE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCCannotUsePacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCCannotUseHandler;
//
//////////////////////////////////////////////////////////////////////

class GCCannotUseHandler {
	
public :

	// execute packet's handler
	static void execute(GCCannotUse* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
