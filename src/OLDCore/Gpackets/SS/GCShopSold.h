//--------------------------------------------------------------------------------
// 
// Filename    : GCShopSold.h 
// Written By  : �輺��
// Description : �� �÷��̾ ���� NPC���� ������ �����ߴµ�,
//               �ٸ� �÷��̾ ���� ���� NPC�� ��ȭ ���̾��ٸ�,
//               �� �÷��̾�� ������ ����� ����ȭ�����־�� �Ѵ�.
//               �� ��Ŷ�� �׸� ���� ��Ŷ�̴�.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SHOP_SOLD_H__
#define __GC_SHOP_SOLD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCShopSold;
//
//--------------------------------------------------------------------------------

class GCShopSold : public Packet 
{

public :

	GCShopSold() throw();
	virtual ~GCShopSold() throw();
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOP_SOLD; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szShopVersion + szShopRackType + szBYTE;}

	// get packet name
	string getPacketName() const throw() { return "GCShopSold"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set NPC's object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set shop version	
	ShopVersion_t getShopVersion(void) const throw() { return m_Version;}
	void setShopVersion(const ShopVersion_t ver) throw() { m_Version = ver;}

	// get/set rack type
	ShopRackType_t getShopType(void) const throw() { return m_RackType;}
	void setShopType(ShopRackType_t type) throw() { m_RackType = type;}
	
	// get/set rack index
	BYTE getShopIndex(void) const throw() { return m_RackIndex;}
	void setShopIndex(BYTE index) throw() { m_RackIndex = index;}

private :
	
	// NPC's object id
	ObjectID_t m_ObjectID;
	
	// ���� ����
	ShopVersion_t m_Version;

	// ������ ����	
	ShopRackType_t m_RackType;
	
	// ������ �ε���
	BYTE m_RackIndex;
	
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSoldFactory;
//
// Factory for GCShopSold
//
//////////////////////////////////////////////////////////////////////

class GCShopSoldFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShopSold(); }

	// get packet name
	string getPacketName() const throw() { return "GCShopSold"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOP_SOLD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCShopSoldPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szShopVersion + szShopRackType + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCShopSoldHandler;
//
//////////////////////////////////////////////////////////////////////

class GCShopSoldHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCShopSold* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
