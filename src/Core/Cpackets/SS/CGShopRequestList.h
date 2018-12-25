//--------------------------------------------------------------------------------
// 
// Filename    : CGShopRequestList.h 
// Written By  : �輺��
// Description : �÷��̾ ������ �ִ� ���� ������ ������ ������ �ִ� ������
//               ������ �ٸ� ���, �÷��̾�� �������� ��ǰ�� ����Ʈ�� 
//               ��û�ϰ� �ȴ�. �� ��Ŷ�� �׶� ������ �Ǵ� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __CG_SHOP_REQUEST_LIST_H__
#define __CG_SHOP_REQUEST_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CGShopRequestList;
//
//--------------------------------------------------------------------------------

class CGShopRequestList : public Packet {

public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SHOP_REQUEST_LIST; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGShopRequestListPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szObjectID+szShopRackType; }

	// get packet name
	string getPacketName()  { return "CGShopRequestList"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	ShopRackType_t getRackType(void) throw() { return m_RackType; }
	void setRackType(ShopRackType_t type) throw() { m_RackType = type; }

private :
	
	// ObjectID
	ObjectID_t     m_ObjectID;
	ShopRackType_t m_RackType;

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListFactory;
//
// Factory for CGShopRequestList
//
//--------------------------------------------------------------------------------

class CGShopRequestListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGShopRequestList(); }

	// get packet name
	string getPacketName()  { return "CGShopRequestList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SHOP_REQUEST_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szObjectID+szShopRackType; }

};


//--------------------------------------------------------------------------------
//
// class CGShopRequestListHandler;
//
//--------------------------------------------------------------------------------

class CGShopRequestListHandler {
	
public:

	// execute packet's handler
	static void execute(CGShopRequestList* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
