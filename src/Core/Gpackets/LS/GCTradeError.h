////////////////////////////////////////////////////////////////////////////////
// Filename    : GCTradeError.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GC_TRADE_ERROR_H__
#define __GC_TRADE_ERROR_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
// ���� �ڵ�
////////////////////////////////////////////////////////////////////////////////

enum
{
	// ��ȯ�� �䱸�� ����� �������� �ʴ´�
	GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST = 0,

	// ��ȯ�� �䱸�� ����� �ٸ� �����̴�
	GC_TRADE_ERROR_CODE_RACE_DIFFER,

	// ��ȯ�� �Ϸ��� �ϴ� ���� ���� ���밡 �ƴϴ�.
	GC_TRADE_ERROR_CODE_NOT_SAFE,

	// ���ͻ���Ŭ�� ź ä�� ��ȯ�� �õ��ϰ� �ִ�.
	GC_TRADE_ERROR_CODE_MOTORCYCLE,

	// ���볪 ���� ���¿����� ��ȯ�� �� �� ����.
	GC_TRADE_ERROR_CODE_BAT_OR_WOLF,

	// ��ȯ ���̸鼭 �ٽ� ��ȯ�� �Ϸ��� �Ѵ�
	GC_TRADE_ERROR_CODE_ALREADY_TRADING,

	// ��ȯ ���� �ƴѵ�, ��ȯ ���� ��Ŷ�� ���ƿԴ�.
	GC_TRADE_ERROR_CODE_NOT_TRADING,

	// ��ȯ ��� ���Ϸ��� �ϴ� �������� ������ ���� �ʴ�
	GC_TRADE_ERROR_CODE_ADD_ITEM,

	// ��ȯ ��󿡼� ������ �ϴ� �������� ������ ���� �ʴ�
	GC_TRADE_ERROR_CODE_REMOVE_ITEM,

	// ��ȯ ��� ���Ϸ��� �ϴ� ���� ������ ���� �ʴ�.
	GC_TRADE_ERROR_CODE_INCREASE_MONEY,

	// ��ȯ ��󿡼� ������ �ϴ� ���� ������ ���� �ʴ�.
	GC_TRADE_ERROR_CODE_DECREASE_MONEY,

	// ��ȯ�� �ߴµ�, �ڸ��� ���ڶ� �����ߴ�
	GC_TRADE_ERROR_CODE_NOT_ENOUGH_SPACE,

	// ��ȯ�� �ߴµ�, ���� ���� ��ȯ ���� ������ �����ߴ�
	GC_TRADE_ERROR_CODE_EVENT_GIFT_BOX,

	// �� �� ���� �����̴�...
	GC_TRADE_ERROR_CODE_UNKNOWN,

	GC_TRADE_ERROR_CODE_MAX
};

////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeError;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeError : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_TRADE_ERROR; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE ; }
	string getPacketName() const throw() { return "GCTradeError"; }
	string toString() const throw();

public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	BYTE getCode() const throw() { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ��� ���̵�
	BYTE       m_Code;           // �ڵ�

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeErrorFactory;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeErrorFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCTradeError(); }
	string getPacketName() const throw() { return "GCTradeError"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TRADE_ERROR; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }

};


////////////////////////////////////////////////////////////////////////////////
//
// class GCTradeErrorHandler;
//
////////////////////////////////////////////////////////////////////////////////

class GCTradeErrorHandler 
{
public:
	static void execute(GCTradeError* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
