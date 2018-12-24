//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyLeave.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_LEAVE_H__
#define __GC_PARTY_LEAVE_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeave;
//////////////////////////////////////////////////////////////////////////////

class GCPartyLeave : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_PARTY_LEAVE; }
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE*2 + m_Expeller.size() + m_Expellee.size();
	}
	string getPacketName() const throw() { return "GCPartyLeave"; }
	string toString() const throw();

public:
	string getExpeller(void) const { return m_Expeller; }
	void setExpeller(const string& name) { m_Expeller = name; }

	string getExpellee(void) const { return m_Expellee; }
	void setExpellee(const string& name) { m_Expellee = name; }

private:
	// �������� ȥ�� ��Ƽ���� ������ ���������� ��쿡��
	// �߹����� �̸��� NULL�̴�.
	// �������� �ٸ� ����� ���ؼ� ���������� ��쿡��
	// �߹����� �̸��� NULL�� �ƴϴ�.
	// ��� ��쿡�� �߹���� ���� �̸��� NULL�� ���� ����.
	string m_Expeller; // �߹���
	string m_Expellee; // �߹���� ��
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeaveFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPartyLeaveFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCPartyLeave(); }
	string getPacketName() const throw() { return "GCPartyLeave"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_PARTY_LEAVE; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE*2 + 20; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyLeaveHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPartyLeaveHandler 
{
public:
	static void execute(GCPartyLeave* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
