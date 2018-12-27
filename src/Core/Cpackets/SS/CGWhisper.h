//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGWhisper.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_WHISPER_H__
#define __CG_WHISPER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGWhisper;
//
// 클라이언트가 서버에게 보내는 Whisper 패킷이다.
// 내부에 Whisper String 만을 데이타 필드로 가진다.
//
//////////////////////////////////////////////////////////////////////

class CGWhisper : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_WHISPER; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_Name.size() + szuint + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "CGWhisper"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Name
	string getName()  { return m_Name; }
	void setName(const string & Name)  { m_Name = Name; }

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color )  { m_Color = color; }

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg)  { m_Message = msg; }
	

private :

	string m_Name;
	
	// text color
	uint m_Color;

	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGWhisperFactory;
//
// Factory for CGWhisper
//
//////////////////////////////////////////////////////////////////////

class CGWhisperFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGWhisper(); }

	// get packet name
	string getPacketName()  { return "CGWhisper"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_WHISPER; }

	// get packet's max body size
	// message 의 최대 크기에 대한 설정이 필요하다.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 10 + szuint + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGWhisperHandler;
//
//////////////////////////////////////////////////////////////////////

class CGWhisperHandler {

public:

	// execute packet's handler
	static void execute(CGWhisper* pPacket, Player* pPlayer) ;

};

#endif
