//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCRegisterPlayerOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_REGISTER_PLAYER_OK_H__
#define __LC_REGISTER_PLAYER_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOK;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOK : public Packet {

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_REGISTER_PLAYER_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCRegisterPlayerOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szBYTE + m_GroupName.size() + szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "LCRegisterPlayerOK"; }

    // get / set Groupname
	string getGroupName()  { return m_GroupName; }
	void setGroupName(const string & GroupName)  { m_GroupName = GroupName; }
	
	// get / set GoreLevel
	bool isAdult()  { return m_isAdult; }
	void setAdult(bool isAdult)  { m_isAdult = isAdult; }
	
	
	// get packet's debug string
	string toString()  { return "LCRegisterPlayerOK"; }

private :
	// ���� �׷� �̸�.
	string m_GroupName;
	
	// ��� ���� : ���� �÷��̾ �̼����� �ΰ�?
	// true�� ��� ����
	// false �� ��� �̼�����
	bool m_isAdult;
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOKFactory;
//
// Factory for LCRegisterPlayerOK
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new LCRegisterPlayerOK(); }

	// get packet name
	string getPacketName()  { return "LCRegisterPlayerOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_REGISTER_PLAYER_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szBYTE + 20 + szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerOKHandler {

public:

	// execute packet's handler
	static void execute(LCRegisterPlayerOK* pPacket, Player* pPlayer) ;

};

#endif
