//----------------------------------------------------------------------
// 
// Filename    : GLKickVerify.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GL_KICK_VERIFY_H__
#define __GL_KICK_VERIFY_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GLKickVerify;
//
// '�̹� ���� ��' ������ �ذ��ϱ� ����...
// LGKickCharacter�� �����ϴ� ��� ��Ŷ�̴�.
//
//----------------------------------------------------------------------

class GLKickVerify : public DatagramPacket {

public :
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GL_KICK_VERIFY; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + szBYTE + m_PCName.size() + szuint;
	}

	// get packet name
	string getPacketName()  { return "GLKickVerify"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set playerID
	bool isKicked()  { return m_bKicked; }
	void setKicked(bool bKicked=true) throw() { m_bKicked = bKicked; }

  	// get/set pcName
    string getPCName()  { return m_PCName; }
    void setPCName(const string& pcName) throw() { m_PCName = pcName; }

    uint getID()  { return m_ID; }
    void setID(uint id) throw() { m_ID = id; }

	
private :

	// Player ID
	bool   m_bKicked;

	string m_PCName;

	uint   m_ID;
};


//////////////////////////////////////////////////////////////////////
//
// class GLKickVerifyFactory;
//
// Factory for GLKickVerify
//
//////////////////////////////////////////////////////////////////////

class GLKickVerifyFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GLKickVerify(); }

	// get packet name
	string getPacketName()  { return "GLKickVerify"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GL_KICK_VERIFY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLKickVerifyPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + szBYTE + 20 + szuint;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GLKickVerifyHandler;
//
//////////////////////////////////////////////////////////////////////

class GLKickVerifyHandler {
	
public :

	// execute packet's handler
	static void execute(GLKickVerify* pPacket) throw(ProtocolException, Error);

};

#endif
