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
	GCMakeItemFail() throw();
	
	// destructor
	~GCMakeItemFail() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_MAKE_ITEM_FAIL; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return GCChangeInventoryItemNum::getPacketSize() + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName() const throw() { return "GCMakeItemFail"; }
	
	// get packet's debug string
	string toString() const throw();
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
	GCMakeItemFailFactory() throw() {}
	
	// destructor
	virtual ~GCMakeItemFailFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMakeItemFail(); }

	// get packet name
	string getPacketName() const throw() { return "GCMakeItemFail"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MAKE_ITEM_FAIL; }

	// get Packet Max Size
	// PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szCEffectID + szDuration + szBYTE + szBYTE* m_ListNum* 2 ; }
	PacketSize_t getPacketMaxSize() const throw() { return 255 + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCMakeItemFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMakeItemFailHandler {

public :

	// execute packet's handler
	static void execute(GCMakeItemFail* pGCMakeItemFail, Player* pPlayer) throw(Error);

};

#endif
