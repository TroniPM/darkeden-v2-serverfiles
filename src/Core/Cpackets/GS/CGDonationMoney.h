////////////////////////////////////////////////////////////////////////////////
// Filename    : CGDonationMoney.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_DONATION_MONEY_H__
#define __CG_DONATION_MONEY_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��� ����
////////////////////////////////////////////////////////////////////////////////
enum DonationType
{
	DONATION_TYPE_200501_PERSONAL = 0,
	DONATION_TYPE_200501_GUILD,			// 1

	DONATION_TYPE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGDonationMoney
//
////////////////////////////////////////////////////////////////////////////////
class CGDonationMoney : public Packet 
{
public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_DONATION_MONEY; }
	PacketSize_t getPacketSize()  { return szGold + szBYTE; }
	string getPacketName()  { return "CGDonationMoney"; }
	string toString() ;
	
public:
	// get / set gold
	Gold_t getGold() const { return m_Gold; }
	void setGold( Gold_t gold ) { m_Gold = gold; }

	// get / set donation Type
	BYTE getDonationType() const { return m_DonationType; }
	void setDonationType( BYTE donationType ) { m_DonationType = donationType; }

private:
	Gold_t		m_Gold;				// ��� �ݾ�
	BYTE		m_DonationType;		// ��� ����
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDonationMoneyFactory
//
////////////////////////////////////////////////////////////////////////////////

class CGDonationMoneyFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGDonationMoney(); }
	string getPacketName()  { return "CGDonationMoney"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DONATION_MONEY; }
	PacketSize_t getPacketMaxSize()  { return szGold + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGDonationMoneyHandler
//
////////////////////////////////////////////////////////////////////////////////
class CGDonationMoneyHandler 
{
public:
	static void execute(CGDonationMoney* pPacket, Player* player) ;
};

#endif

