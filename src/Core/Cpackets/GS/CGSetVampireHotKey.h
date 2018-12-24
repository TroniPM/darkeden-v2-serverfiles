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
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_SET_VAMPIRE_HOT_KEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGSetVampireHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szSkillType* 8; }

	// get packet name
	string getPacketName() const throw() { return "CGSetVampireHotKey"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get/set X Coordicate
	SkillType_t getHotKey(BYTE pos) const throw() { return m_HotKey[pos]; }
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
	string getPacketName() const throw() { return "CGSetVampireHotKey"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SET_VAMPIRE_HOT_KEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGSetVampireHotKeyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType* 8; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSetVampireHotKeyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSetVampireHotKeyHandler {
	
public:

	// execute packet's handler
	static void execute(CGSetVampireHotKey* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
