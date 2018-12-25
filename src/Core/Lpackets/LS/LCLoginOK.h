//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCLoginOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_LOGIN_OK_H__
#define __LC_LOGIN_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCLoginOK;
//
// �α��μ����� Ŭ���̾�Ʈ���� �α��� ������ �˷��ִ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class LCLoginOK : public Packet {

public:

	LCLoginOK() : m_LastDays(0xffff) { }

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_LOGIN_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCLoginOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szBYTE + szBYTE + szBYTE + szWORD; }
	
	// get packet's name
	string getPacketName()  { return "LCLoginOK"; }

	// get / set GoreLevel
	bool isAdult()  { return m_isAdult; }
	void setAdult(bool isAdult) throw() { m_isAdult = isAdult; }

	bool isFamily()  { return m_bFamily; }
	void setFamily(bool isFamily) throw() { m_bFamily = isFamily; }

	BYTE getStat()  { return m_Stat; }
	void setStat(BYTE Stat) throw() { m_Stat = Stat; }

	WORD getLastDays()  { return m_LastDays; }
	void setLastDays(WORD LastDays) throw() { m_LastDays = LastDays; }

	// get packet's debug string
	string toString()  { return "LCLoginOK"; }

private :

	// ��� ���� : ���� �÷��̾ �̼����� �ΰ�?
	// true�� ��� ����
	// false �� ��� �̼�����
	bool m_isAdult;

	// Family ������ΰ�
	bool m_bFamily;

	// ������ ����
	BYTE m_Stat;

	WORD m_LastDays;

};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginOKFactory;
//
// Factory for LCLoginOK
//
//////////////////////////////////////////////////////////////////////

class LCLoginOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCLoginOK(); }

	// get packet name
	string getPacketName()  { return "LCLoginOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_LOGIN_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szBYTE + szBYTE + szBYTE + szWORD; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCLoginOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCLoginOKHandler {

public:

	// execute packet's handler
	static void execute(LCLoginOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
