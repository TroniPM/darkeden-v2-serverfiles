//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPartySay.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_SAY_H__
#define __GC_PARTY_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPartySay;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPartySay : public Packet
{
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_PARTY_SAY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCPartySayPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szBYTE + m_Name.size() + szDWORD + szBYTE + m_Message.size(); }

	// get packet's name
	string getPacketName()  { return "GCPartySay"; }
	
	// get packet's debug string
	string toString() ;


public :
	string	getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	DWORD	getColor() const { return m_Color; }
	void	setColor(DWORD color) { m_Color = color; }

	string	getMessage() const { return m_Message; }
	void	setMessage( const string& msg ) { m_Message = msg; }

private :
	string	m_Name;
	DWORD	m_Color;
	string	m_Message;
};


//////////////////////////////////////////////////////////////////////
//
// class GCPartySayFactory;
//
// Factory for GCPartySay
//
//////////////////////////////////////////////////////////////////////

class GCPartySayFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCPartySay(); }

	// get packet name
	string getPacketName()  { return "GCPartySay"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_PARTY_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPartySayPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 20 + szDWORD + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPartySayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPartySayHandler {

public :

	// execute packet's handler
	static void execute(GCPartySay* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
