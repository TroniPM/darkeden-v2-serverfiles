//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMakeItemOK.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MAKE_ITEM_OK_H__
#define __GC_MAKE_ITEM_OK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "GCChangeInventoryItemNum.h"
#include "GCAddItemToInventory.h"
#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemOK;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemOK : public GCChangeInventoryItemNum, public GCAddItemToInventory, public ModifyInfo {

public :
	
	// constructor
	GCMakeItemOK() ;
	
	// destructor
	~GCMakeItemOK() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MAKE_ITEM_OK; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return GCChangeInventoryItemNum::getPacketSize() 
		+ GCAddItemToInventory::getPacketSize()
		+ ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCMakeItemOK"; }
	
	// get packet's debug string
	string toString() ;

private :

};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemOKFactory;
//
// Factory for GCMakeItemOK
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemOKFactory : public PacketFactory {

public :
	
	// constructor
	GCMakeItemOKFactory() throw() {}
	
	// destructor
	virtual ~GCMakeItemOKFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMakeItemOK(); }

	// get packet name
	string getPacketName()  { return "GCMakeItemOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MAKE_ITEM_OK; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize()  { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE* m_ListNum* 2 ; }
	PacketSize_t getPacketMaxSize()  { return  255 + 255 + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemOKHandler {

public :

	// execute packet's handler
	static void execute(GCMakeItemOK* pGCMakeItemOK, Player* pPlayer);

};

#endif
