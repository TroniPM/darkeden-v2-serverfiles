//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildRegist.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_REGIST_H__
#define __GC_SHOW_GUILD_REGIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegist;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegist : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SHOW_GUILD_REGIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGold; }

	// get packet name
	string getPacketName()  { return "GCShowGuildRegist"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Registration Fee
	Gold_t getRegistrationFee()  { return m_RegistrationFee; }
	void setRegistrationFee( Gold_t registrationFee ) throw() { m_RegistrationFee = registrationFee; }
	

private :
	
	// Registration Fee
	Gold_t m_RegistrationFee;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegistFactory;
//
// Factory for GCShowGuildRegist
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegistFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShowGuildRegist(); }

	// get packet name
	string getPacketName()  { return "GCShowGuildRegist"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SHOW_GUILD_REGIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szGold; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildRegist;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildRegistHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildRegist* pPacket, Player* pPlayer) ;

};

#endif
