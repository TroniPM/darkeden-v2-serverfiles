////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeFinish.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_FINISH_H__
#define __GC_TRADE_FINISH_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� ����� �� ������ �ڵ�
	GC_TRADE_FINISH_ACCEPT = 0,

	// ��ȯ�� �ź��� �� ������ �ڵ�
	GC_TRADE_FINISH_REJECT,

	// ��ȯ�� ������ �� ������ �ڵ�
	GC_TRADE_FINISH_RECONSIDER,

	// ��ȯ�� ���������� �϶�� �ڵ�
	GC_TRADE_FINISH_EXECUTE,

	GC_TRADE_FINISH_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeFinish;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeFinish : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_TRADE_FINISH; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE; }
	string getPacketName()  { return "GCTradeFinish"; }
	string toString() ;

public:
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode()  { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	BYTE       m_Code;           // ��ȯ �ڵ�


};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeFinishFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeFinishFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeFinish(); }
	string getPacketName()  { return "GCTradeFinish"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_TRADE_FINISH; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeFinishHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeFinishHandler 
{
public:
	static void execute(GCTradeFinish* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
