
//----------------------------------------------------------------------
// 
// Filename    : GGServerChat.h 
// Written By  : inthesky
// Description : ������ Whisper Chat�����Ѵ�.   
// 
//----------------------------------------------------------------------

#ifndef __GG_SERVER_CHAT_H__
#define __GG_SERVER_CHAT_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GGServerChat;
//
//----------------------------------------------------------------------

class GGServerChat : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GG_SERVER_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_Sender.size() +		// Sender
			   szBYTE + m_Receiver.size() + 	// Receiver
			   szuint +							// Color
			   szBYTE + m_Message.size() +		// Message
			   szRace;							// Race
	}

	// get packet name
	string getPacketName()  { return "GGServerChat"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set Sender
	const string& getSender()  { return m_Sender; }
	void setSender( const string& sender )  { m_Sender = sender; }

	// get/set Receiver
	const string& getReceiver()  { return m_Receiver; }
    void setReceiver( const string& receiver)  { m_Receiver= receiver; }

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color )  { m_Color = color; }

	// get/set message
	const string& getMessage()  { return m_Message; }
	void setMessage( const string& message )  { m_Message = message; }

	// get/set race
	// 
	Race_t getRace()  { return m_Race; }
	void setRace(Race_t race)  { m_Race = race; }

private :

	
	// Sender
	string m_Sender;
	
	// Receiver
	string m_Receiver;
	
	// Message
	string m_Message;
	
	// Race
	Race_t m_Race;

	// Text Color
	uint m_Color;

};


//////////////////////////////////////////////////////////////////////
//
// class GGServerChatFactory;
//
// Factory for GGServerChat
//
//////////////////////////////////////////////////////////////////////

class GGServerChatFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GGServerChat(); }

	// get packet name
	string getPacketName()  { return "GGServerChat"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GG_SERVER_CHAT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GGServerChatPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + 10 +					// Sender
			   szBYTE + 10 + 					// Receiver
			   szuint +							// Color
			   szBYTE + 128 +					// Message
			   szRace;							// Race
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GGServerChatHandler;
//
//////////////////////////////////////////////////////////////////////

class GGServerChatHandler {
	
public :

	// execute packet's handler
	static void execute(GGServerChat* pPacket) ;

};

#endif
