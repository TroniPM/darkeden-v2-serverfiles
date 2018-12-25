//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSetSlayerHotKey.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SET_SLAYER_HOT_KEY_H__
#define __CG_SET_SLAYER_HOT_KEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGSetSlayerHotKey;
//
//////////////////////////////////////////////////////////////////////

class CGSetSlayerHotKey : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SET_SLAYER_HOT_KEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGSetSlayerHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szSkillType* 4; }

	// get packet name
	string getPacketName()  { return "CGSetSlayerHotKey"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get/set X Coordicate
	SkillType_t getHotKey(BYTE pos)  { return m_HotKey[pos]; }
	void setHotKey(BYTE pos, SkillType_t SkillType) throw() { m_HotKey[pos] = SkillType; }

private :

	SkillType_t m_HotKey[4];
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSetSlayerHotKeyFactory;
//
// Factory for CGSetSlayerHotKey
//
//////////////////////////////////////////////////////////////////////

class CGSetSlayerHotKeyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSetSlayerHotKey(); }

	// get packet name
	string getPacketName()  { return "CGSetSlayerHotKey"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SET_SLAYER_HOT_KEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGSetSlayerHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szSkillType* 4; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSetSlayerHotKeyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSetSlayerHotKeyHandler {
	
public:

	// execute packet's handler
	static void execute(CGSetSlayerHotKey* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
