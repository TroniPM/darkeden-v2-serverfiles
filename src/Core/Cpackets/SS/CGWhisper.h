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
// Ŭ���̾�Ʈ�� �������� ������ Whisper ��Ŷ�̴�.
// ���ο� Whisper String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class CGWhisper : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

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
	void setName(const string & Name) throw() { m_Name = Name; }

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	

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
	Packet* createPacket() throw() { return new CGWhisper(); }

	// get packet name
	string getPacketName()  { return "CGWhisper"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_WHISPER; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
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
	static void execute(CGWhisper* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
