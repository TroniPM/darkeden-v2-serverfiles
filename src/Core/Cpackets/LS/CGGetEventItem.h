////////////////////////////////////////////////////////////////////////////////
// Filename    : CGGetEventItem.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_GET_EVENT_ITEM_H__
#define __CG_GET_EVENT_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��� ����
////////////////////////////////////////////////////////////////////////////////
enum EventType
{
	EVENT_TYPE_200501_COMBACK_ITEM = 0,			// ���ƿ� ����� �� ������ �ֱ� �̺�Ʈ
	EVENT_TYPE_200501_COMBACK_PREMIUM_ITEM,		// ���ƿ� ����� ���� �� ������ �ֱ� �̺�Ʈ
	EVENT_TYPE_200501_COMBACK_RECOMMEND_ITEM,	// ���ƿ� ����� ���� �� ��õ ���� �� ������ �ֱ� �̺�Ʈ

	EVENT_TYPE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGGetEventItem
//
////////////////////////////////////////////////////////////////////////////////
class CGGetEventItem : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_GET_EVENT_ITEM; }
	PacketSize_t getPacketSize() const throw() { return szBYTE; }
	string getPacketName() const throw() { return "CGGetEventItem"; }
	string toString() const throw();
	
public:
	// get / set Event Type
	BYTE getEventType() const { return m_EventType; }
	void setEventType( BYTE eventType ) { m_EventType = eventType; }

private:
	BYTE		m_EventType;		// �̺�Ʈ ����
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGGetEventItemFactory
//
////////////////////////////////////////////////////////////////////////////////

class CGGetEventItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGGetEventItem(); }
	string getPacketName() const throw() { return "CGGetEventItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_GET_EVENT_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGGetEventItemHandler
//
////////////////////////////////////////////////////////////////////////////////
class CGGetEventItemHandler 
{
public:
	static void execute(CGGetEventItem* pPacket, Player* player) throw(ProtocolException, Error);

#ifdef __GAME_SERVER__
	static void executeCombackItem(CGGetEventItem* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeCombackPremiumItem(CGGetEventItem* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeCombackRecommendItem(CGGetEventItem* pPacket, Player* pPlayer) throw(ProtocolException, Error);
#endif
};

#endif

