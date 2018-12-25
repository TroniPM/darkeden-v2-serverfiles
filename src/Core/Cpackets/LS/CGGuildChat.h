//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGuildChat.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GUILD_CHAT_H__
#define __CG_GUILD_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGuildChat;
//
//////////////////////////////////////////////////////////////////////

class CGGuildChat : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_GUILD_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() 
	{
		return szBYTE +
			   szuint +				// text color
			   szBYTE +				// message size
			   m_Message.size();	// chatting message
	}

	// get packet name
	string getPacketName()  { return "CGGuildChat"; }
	
	// get packet's debug string
	string toString() ;

	BYTE getType()  { return m_Type; }
	void setType( BYTE type ) throw() { m_Type = type; }

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	

private :

	BYTE m_Type;
	// text color
	uint m_Color;

	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGGuildChatFactory;
//
// Factory for CGGuildChat
//
//////////////////////////////////////////////////////////////////////

class CGGuildChatFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGGuildChat(); }

	// get packet name
	string getPacketName()  { return "CGGuildChat"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_GUILD_CHAT; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() 
	{
		return szBYTE +
			   szuint +			// text color
			   szBYTE +			// message size
			   128;				// chatting message
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CGGuildChatHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGuildChatHandler {

public:

	// execute packet's handler
	static void execute(CGGuildChat* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
