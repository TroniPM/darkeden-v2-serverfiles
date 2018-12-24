////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradePrepare.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_PREPARE_H__
#define __GC_TRADE_PREPARE_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ��ȯ �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ���� ó�� ��ȯ�� ��û���� �÷��̾�� �����ִ� �ڵ�
	GC_TRADE_PREPARE_CODE_REQUEST = 0,

	// ���� ó�� ��ȯ�� ��û���� �÷��̾ ������� ��쿡 �����ִ� �ڵ�
	GC_TRADE_PREPARE_CODE_CANCEL,

	// ��ȯ�� ��û���� �÷��̾ ������ ��쿡, ��û�ڿ��� �����ش�.
	GC_TRADE_PREPARE_CODE_ACCEPT,

	// ��ȯ�� ��û���� �÷��̾ �ź����� ��쿡, ��û�ڿ��� �����ش�.
	GC_TRADE_PREPARE_CODE_REJECT,

	// ��ȯ�� ��û���� �÷��̾ ���� ��ȯ ���̴�.
	GC_TRADE_PREPARE_CODE_BUSY,

	GC_TRADE_PREPARE_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepare;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepare : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_PREPARE; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }
	string getPacketName() const throw() { return "GCTradePrepare"; }
	string toString() const throw();

public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

private :
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ OID
	BYTE       m_Code;           // ��ȯ �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradePrepare(); }
	string getPacketName() const throw() { return "GCTradePrepare"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_PREPARE; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradePrepareHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradePrepareHandler 
{
public:
	static void execute(GCTradePrepare* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
