//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGlobalChat.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GLOBAL_CHAT_H__
#define __CG_GLOBAL_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChat;
//
// Ŭ���̾�Ʈ�� �������� ������ GlobalChat ��Ŷ�̴�.
// ���ο� GlobalChat String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChat : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_GLOBAL_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szuint + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "CGGlobalChat"; }
	
	// get packet's debug string
	string toString() ;

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	

private :
	
	// text color
	uint m_Color;

	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChatFactory;
//
// Factory for CGGlobalChat
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChatFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGGlobalChat(); }

	// get packet name
	string getPacketName()  { return "CGGlobalChat"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_GLOBAL_CHAT; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize()  { return szuint + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGGlobalChatHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGlobalChatHandler {

public:

	// execute packet's handler
	static void execute(CGGlobalChat* pPacket, Player* pPlayer) ;

};

#endif
