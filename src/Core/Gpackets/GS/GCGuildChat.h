//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGuildChat.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GUILD_CHAT_H__
#define __GC_GUILD_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCGuildChat;
//
//////////////////////////////////////////////////////////////////////

class GCGuildChat : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_GUILD_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() 
	{
		return ((m_Type==0)?(szBYTE):(szBYTE+szBYTE+m_SendGuildName.size())) +
			   szBYTE +					// sender size
			   m_Sender.size() +		// sender
			   szuint +					// text color
			   szBYTE +					// message size
			   m_Message.size();		// message
	}

	// get packet name
	string getPacketName()  { return "GCGuildChat"; }

	// get packet's debug string
	string toString() ;

	BYTE getType()  { return m_Type; }
	void setType( BYTE type )  { m_Type = type; }

	// get/set sender
	string getSendGuildName()  { return m_SendGuildName; }
	void setSendGuildName( const string& sender )  { m_SendGuildName = sender; }

	// get/set sender
	string getSender()  { return m_Sender; }
	void setSender( const string& sender )  { m_Sender = sender; }

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	
private :

	BYTE m_Type;
	string m_SendGuildName;
	// sender
	string m_Sender;

	// text color
	uint m_Color;
	
	// chatting message
	string m_Message;

};


//////////////////////////////////////////////////////////////////////
//
// class GCGuildChatFactory;
//
// Factory for GCGuildChat
//
//////////////////////////////////////////////////////////////////////

class GCGuildChatFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCGuildChat(); }

	// get packet name
	string getPacketName()  { return "GCGuildChat"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_GUILD_CHAT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCGuildChatPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() 
	{
		return szBYTE +
			   szBYTE +
			   20 +
			   szBYTE +				// sender size
			   10 +					// sender max size
			   szuint +				// text color size
			   szBYTE +				// message size
			   128;					// message
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCGuildChatHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGuildChatHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCGuildChat* pPacket, Player* pPlayer) ;

};

#endif
