//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSay.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SAY_H__
#define __GC_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCSay;
//
// ���� ������ Ư�� �÷��̾��� Say �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸�� Say ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCSay : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID + szuint + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "GCSay"; }
	
	// get packet's debug string
	string toString() ;

	// get/set sender's creature id
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID) throw() { m_ObjectID = creatureID; }

	//get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	

private :
	
	// character's creature id
	ObjectID_t m_ObjectID;

	// text color
	uint m_Color;
	
	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCSayFactory;
//
// Factory for GCSay
//
//////////////////////////////////////////////////////////////////////

class GCSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSay(); }

	// get packet name
	string getPacketName()  { return "GCSay"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSayPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID + szuint + szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSayHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSay* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
