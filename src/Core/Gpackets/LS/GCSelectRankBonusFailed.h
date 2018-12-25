//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCSelectRankBonusFailed.h 
// Written By  :  elca@ewestsoft.com
// Description :  �
//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SELECT_RANK_BONUS_FAILED_H__
#define __GC_SELECT_RANK_BONUS_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusFailed;
//
//////////////////////////////////////////////////////////////////////

class GCSelectRankBonusFailed : public Packet 
{

public: 

	GCSelectRankBonusFailed() throw();
	virtual ~GCSelectRankBonusFailed() throw();

	
public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) ;
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SELECT_RANK_BONUS_FAILED; }
	
	// get packet size
	PacketSize_t getPacketSize()  { return szDWORD + szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "GCSelectRankBonusFailed"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set skill type
	DWORD getRankBonusType()  { return m_RankBonusType; }
	void setRankBonusType(DWORD rankBonusType) throw() { m_RankBonusType = rankBonusType; }

	// get/set description
	BYTE getDesc(void)  { return m_Desc;}
	void setDesc(BYTE desc) throw() { m_Desc = desc;}

private:

	DWORD 		m_RankBonusType;
	BYTE        m_Desc;       // �����ڵ�

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusFailedFactory;
//
// Factory for  GCSelectRankBonusFailed
//
//////////////////////////////////////////////////////////////////////

class  GCSelectRankBonusFailedFactory : public PacketFactory {

public :
	
	// constructor
	 GCSelectRankBonusFailedFactory() throw() {}
	
	// destructor
	virtual ~GCSelectRankBonusFailedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSelectRankBonusFailed(); }

	// get packet name
	string getPacketName()  { return "GCSelectRankBonusFailed"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SELECT_RANK_BONUS_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szDWORD + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSelectRankBonusFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCSelectRankBonusFailedHandler {

public :

	// execute packet's handler
	static void execute( GCSelectRankBonusFailed* pGCSelectRankBonusFailed, Player* pPlayer) throw(Error);

};

#endif	// __GC_LEARN_SKILL_FAILED_H__
