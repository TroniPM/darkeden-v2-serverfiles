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
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_FINISH; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }
	string getPacketName() const throw() { return "GCTradeFinish"; }
	string toString() const throw();

public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode() const throw() { return m_Code; }
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
	string getPacketName() const throw() { return "GCTradeFinish"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_FINISH; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }

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
