//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectRankBonus.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_RANK_BONUS_H__
#define __CG_SELECT_RANK_BONUS_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectRankBonus;
//////////////////////////////////////////////////////////////////////////////

class CGSelectRankBonus : public Packet 
{
public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) ;

    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SELECT_RANK_BONUS; }

	// get packet's body size
	PacketSize_t getPacketSize()  { return szDWORD; }

	// get packet name
	string getPacketName()  { return "CGSelectRankBonus"; }

	// get packet's debug string
	string toString() ;

public:
	DWORD getRankBonusType()  { return m_RankBonusType; }
	void setRankBonusType( DWORD rankBonusType )  { m_RankBonusType = rankBonusType; }

private:
	DWORD	m_RankBonusType;		// Rank Bonus Type
};

//////////////////////////////////////////////////////////////////////
// class CGSelectRankBonusFactory;
//////////////////////////////////////////////////////////////////////

class CGSelectRankBonusFactory : public PacketFactory 
{
public:
	// create packet
	Packet* createPacket()  { return new CGSelectRankBonus(); }

	// get packet name
	string getPacketName()  { return "CGSelectRankBonus"; }

	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SELECT_RANK_BONUS; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szDWORD; }
};


//////////////////////////////////////////////////////////////////////
// class CGSelectRankBonusHandler;
//////////////////////////////////////////////////////////////////////

class CGSelectRankBonusHandler 
{
public:
	// execute packet's handler
	static void execute(CGSelectRankBonus* pCGSelectRankBonus, Player* pPlayer) ;
};

#endif
