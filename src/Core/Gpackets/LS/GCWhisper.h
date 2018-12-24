//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWhisper.h 
// Written By  : elca
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_WHISPER_H__
#define __GC_WHISPER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCWhisper;
//
// ���� ������ Ư�� �÷��̾��� Whisper �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸�� Whisper ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCWhisper : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_WHISPER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Name.size() + szuint + szBYTE + m_Message.size() + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "GCWhisper"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set sender's creature id
	string getName() const throw() { return m_Name ; }
	void setName(const string & Name) throw() { m_Name = Name ; }

	//get/set text color
	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	
	// get/set chatting message
	Race_t getRace() const throw() { return m_Race; }
	void setRace(Race_t race) throw() { m_Race = race; }

private :
	
	// character's creature Name
	string m_Name;
	
	// text color
	uint m_Color;

	// chatting message
	string m_Message;

	// Race
	Race_t m_Race;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFactory;
//
// Factory for GCWhisper
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCWhisper(); }

	// get packet name
	string getPacketName() const throw() { return "GCWhisper"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_WHISPER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCWhisperPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 10 + szuint + szBYTE + 128 + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperHandler;
//
//////////////////////////////////////////////////////////////////////

class GCWhisperHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCWhisper* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
