//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSetVampireHotKey.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SET_VAMPIRE_HOT_KEY_H__
#define __CG_SET_VAMPIRE_HOT_KEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKey;
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKey : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SET_VAMPIRE_HOT_KEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGSetVampireHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szSkillType* 8; }

	// get packet name
	string getPacketName()  { return "CGSetVampireHotKey"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get/set X Coordicate
	SkillType_t getHotKey(BYTE pos)  { return m_HotKey[pos]; }
	void setHotKey(BYTE pos, SkillType_t SkillType) throw() { m_HotKey[pos] = SkillType; }

private :

	SkillType_t m_HotKey[8];
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyFactory;
//
// Factory for CGSetVampireHotKey
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKeyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSetVampireHotKey(); }

	// get packet name
	string getPacketName()  { return "CGSetVampireHotKey"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SET_VAMPIRE_HOT_KEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGSetVampireHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szSkillType* 8; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKeyHandler {
	
public:

	// execute packet's handler
	static void execute(CGSetVampireHotKey* pPacket, Player* player) ;
};

#endif
