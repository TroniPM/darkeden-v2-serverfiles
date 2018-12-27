//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMakeItemFail.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MAKE_ITEM_FAIL_H__
#define __GC_MAKE_ITEM_FAIL_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "GCChangeInventoryItemNum.h"
#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemFail;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemFail : public GCChangeInventoryItemNum, public ModifyInfo {

public :
	
	// constructor
	GCMakeItemFail() ;
	
	// destructor
	~GCMakeItemFail() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MAKE_ITEM_FAIL; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return GCChangeInventoryItemNum::getPacketSize() + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCMakeItemFail"; }
	
	// get packet's debug string
	string toString() ;
private :
	

};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemFailFactory;
//
// Factory for GCMakeItemFail
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemFailFactory : public PacketFactory {

public :
	
	// constructor
	GCMakeItemFailFactory()  {}
	
	// destructor
	virtual ~GCMakeItemFailFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCMakeItemFail(); }

	// get packet name
	string getPacketName()  { return "GCMakeItemFail"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MAKE_ITEM_FAIL; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize()  { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE* m_ListNum* 2 ; }
	PacketSize_t getPacketMaxSize()  { return 255 + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemFailHandler {

public :

	// execute packet's handler
	static void execute(GCMakeItemFail* pGCMakeItemFail, Player* pPlayer);

};

#endif
