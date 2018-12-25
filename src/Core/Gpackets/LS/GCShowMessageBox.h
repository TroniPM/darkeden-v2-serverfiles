//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowMessageBox.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_MESSAGE_BOX_H__
#define __GC_SHOW_MESSAGE_BOX_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBox;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBox : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SHOW_MESSAGE_BOX; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "GCShowMessageBox"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Message
	string getMessage()  { return m_Message; }
	void setMessage( const string& message ) throw() { m_Message = message; }
	

private :
	
	// Message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBoxFactory;
//
// Factory for GCShowMessageBox
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBoxFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShowMessageBox(); }

	// get packet name
	string getPacketName()  { return "GCShowMessageBox"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SHOW_MESSAGE_BOX; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 256; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowMessageBox;
//
//////////////////////////////////////////////////////////////////////

class GCShowMessageBoxHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowMessageBox* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
