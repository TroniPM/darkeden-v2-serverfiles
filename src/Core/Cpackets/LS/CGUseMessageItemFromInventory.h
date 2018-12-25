//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseMessageItemFromInventory.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_MESSAGE_ITEM_FROM_INVENTORY_H__
#define __CG_USE_MESSAGE_ITEM_FROM_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "CGUseItemFromInventory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventory : public CGUseItemFromInventory 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketSize()  
	{ 
		return CGUseItemFromInventory::getPacketSize() 
				+ szBYTE + m_Message.size(); 
	}
	string getPacketName()  { return "CGUseMessageItemFromInventory"; }
	string toString() ;
	
public:
	const string& getMessage()  { return m_Message; }
	void setMessage(const string& msg) throw() { m_Message = msg; }

private:
	string m_Message;
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventoryFactory;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventoryFactory : public CGUseItemFromInventoryFactory 
{
public:
	Packet* createPacket() throw() { return new CGUseMessageItemFromInventory(); }
	string getPacketName()  { return "CGUseMessageItemFromInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_USE_MESSAGE_ITEM_FROM_INVENTORY; }
	PacketSize_t getPacketMaxSize()  
	{ 
		return CGUseItemFromInventoryFactory::getPacketMaxSize() 
				+ szBYTE + 128; 
	}
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseMessageItemFromInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class CGUseMessageItemFromInventoryHandler 
{
public:
	static void execute(CGUseMessageItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);

protected:
	static void executeEventTree(CGUseMessageItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
	// add by Coffee
	static void executeEventFromMessage(CGUseMessageItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
