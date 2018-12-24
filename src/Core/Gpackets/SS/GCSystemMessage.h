//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSystemMessage.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SYSTEM_MESSAGE_H__
#define __GC_SYSTEM_MESSAGE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


enum SystemMessageType
{
	SYSTEM_MESSAGE_NORMAL = 0,
	SYSTEM_MESSAGE_OPERATOR,	// ��� ����
	SYSTEM_MESSAGE_MASTER_LAIR,	// ������ ���� ����
	SYSTEM_MESSAGE_COMBAT,		// ���� ����
	SYSTEM_MESSAGE_INFO, 		// Ư���� ���� ����
	SYSTEM_MESSAGE_HOLY_LAND, 	// �ƴ��� ���� ����
	SYSTEM_MESSAGE_RANGER_SAY, 	// Ranger Say, DragonEye �� ���� Ranger�� �޽���
	SYSTEM_MESSAGE_PLAYER,      // ���ȫ��������Ϣ
	SYSTEM_MESSAGE_MAX
};

//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessage;
//
// ���� ������ Ư�� �÷��̾��� SystemMessage �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸�� SystemMessage ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessage : public Packet {

public :
	GCSystemMessage() 
	: m_Color(0x006040E8), m_Type(SYSTEM_MESSAGE_NORMAL)
	{
	}
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SYSTEM_MESSAGE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Message.size() + szuint + szBYTE; }

	// get packet name
	string getPacketName() const throw() { return "GCSystemMessage"; }
	
	// get packet's debug string
	string toString() const throw();

	// get/set chatting message
	string getMessage() const throw() { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }

	// get/set text color
	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	SystemMessageType getType() const throw() { return m_Type; }
	void setType( SystemMessageType Type ) throw() { m_Type = Type; }

	// get/set race
	Race_t getRace() const { return m_Race; }
	void setRace( Race_t race ) { m_Race = race; }

private :
	
	// chatting message
	string m_Message;

	// text color
	uint m_Color;
	
	SystemMessageType m_Type;

	// race
	Race_t m_Race;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessageFactory;
//
// Factory for GCSystemMessage
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessageFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSystemMessage(); }

	// get packet name
	string getPacketName() const throw() { return "GCSystemMessage"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SYSTEM_MESSAGE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 256 + szuint + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSystemMessageHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSystemMessageHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSystemMessage* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
