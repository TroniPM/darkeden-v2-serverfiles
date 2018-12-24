////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeFinish.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_FINISH_H__
#define __CG_TRADE_FINISH_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� ����� �� ������ �ڵ�
	CG_TRADE_FINISH_ACCEPT = 0,
	
	// ��ȯ�� �ź��� �� ������ �ڵ�
	CG_TRADE_FINISH_REJECT,

	// ��ȯ�� ������ �� ������ �ڵ�
	CG_TRADE_FINISH_RECONSIDER,


	CG_TRADE_FINISH_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinish;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinish : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_TRADE_FINISH; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }
	string getPacketName() const throw() { return "CGTradeFinish"; }
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
// class CGTradeFinishFactory;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinishFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTradeFinish(); }
	string getPacketName() const throw() { return "CGTradeFinish"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_TRADE_FINISH; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeFinishHandler;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeFinishHandler 
{
public:
	static void execute(CGTradeFinish* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeSlayer(CGTradeFinish* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeVampire(CGTradeFinish* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeOusters(CGTradeFinish* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeError(CGTradeFinish* pPacket, Player* player, BYTE ErrorCode) throw(ProtocolException, Error);
};

#endif
