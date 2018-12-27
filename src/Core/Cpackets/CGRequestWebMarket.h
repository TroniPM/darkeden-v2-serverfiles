//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestWebMarket.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_WEB_MARKET_H__
#define __CG_REQUEST_WEB_MARKET_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestWebMarket;
//
//////////////////////////////////////////////////////////////////////

class CGRequestWebMarket : public Packet
{
public:
	enum REQUEST_CODE
	{
		REQUEST_WEB_MARKET = 0,
		REQUEST_BUY_COMPLETE,
		REQUEST_GOODS_LIST,
	};

public:
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_WEB_MARKET; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE; }

	// get packet name
	string getPacketName()  { return "CGRequestWebMarket"; }

	// get packet's debug string
	string toString() ;

	// get/set code
	BYTE getCode() const { return m_Code; }
	void setCode( BYTE code ) { m_Code = code; }

public:
	// Request Code
	BYTE m_Code;
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestWebMarketFactory;
//
// Factory for CGRequestWebMarket
//
//////////////////////////////////////////////////////////////////////

class CGRequestWebMarketFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestWebMarketFactory()  {}
	
	// destructor
	virtual ~CGRequestWebMarketFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGRequestWebMarket(); }

	// get packet name
	string getPacketName()  { return "CGRequestWebMarket"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_WEB_MARKET; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestWebMarketHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestWebMarketHandler {

public:

	// execute packet's handler
	static void execute(CGRequestWebMarket* pCGRequestWebMarket, Player* pPlayer);

};

#endif

