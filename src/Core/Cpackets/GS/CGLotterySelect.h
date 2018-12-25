//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGLotterySelect.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_LOTTERY_SELECT_H__
#define __CG_LOTTERY_SELECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

enum
{
	TYPE_SELECT_LOTTERY = 0,					// ���� ����
	TYPE_FINISH_SCRATCH,				// ���� ���� �Ϸ�
	TYPE_OVER_ENDING,					// ���� ����

	TYPE_MAX,
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelect;
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelect : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_LOTTERY_SELECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + szDWORD + szDWORD; }

	// get packet name
	string getPacketName()  { return "CGLotterySelect"; }

	// get packet's debug string
	string toString() ;

	BYTE getType()  { return m_Type; }
	void setType( BYTE type ) { m_Type = type; }

	DWORD getGiftID()  { return m_GiftID; }
	void setGiftID( DWORD GiftID ) throw() { m_GiftID = GiftID; }

	DWORD getQuestLevel()  { return m_QuestLevel; }
	void setQuestLevel( DWORD QuestLevel ) throw() { m_QuestLevel = QuestLevel; }

private :

	BYTE	m_Type;
	DWORD	m_QuestLevel;
	DWORD	m_GiftID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelectFactory;
//
// Factory for CGLotterySelect
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelectFactory : public PacketFactory {

public:
	
	// constructor
	CGLotterySelectFactory() throw() {}
	
	// destructor
	virtual ~CGLotterySelectFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGLotterySelect(); }

	// get packet name
	string getPacketName()  { return "CGLotterySelect"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_LOTTERY_SELECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szBYTE + szDWORD + szDWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGLotterySelectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGLotterySelectHandler {

public:

	// execute packet's handler
	static void execute(CGLotterySelect* pCGLotterySelect, Player* pPlayer) throw(Error);

};

#endif
