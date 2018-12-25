//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyError.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_ERROR_H__
#define __GC_PARTY_ERROR_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// ��Ƽ ���� ���� �ڵ�
//////////////////////////////////////////////////////////////////////////////
enum
{
	// ��Ƽ�� ���Խ�Ű�ų� Ż���ų ����� �������� �ʴ´�.
	GC_PARTY_ERROR_TARGET_NOT_EXIST = 0,

	// ��Ƽ�� ���Խ�Ű�ų� Ż���ų ����� �ٸ� �����̴�.
	GC_PARTY_ERROR_RACE_DIFFER,

	// �������밡 �ƴϴ�.
	GC_PARTY_ERROR_NOT_SAFE,

	// ���볪 ���� ���¿����� �� �� ����.
	GC_PARTY_ERROR_NOT_NORMAL_FORM,

	// �ʴ� ���̸鼭 �� �ʴ븦 �Ϸ��� �Ѵ�.
	GC_TRADE_ERROR_ALREADY_INVITING,

	// �ʴ� ���� �ƴϸ鼭 �ʴ뿡 ���� ������ �����Դ�.
	GC_PARTY_ERROR_NOT_INVITING,

	// ��Ƽ���� �߹��� �� �ִ� ������ ����.
	GC_PARTY_ERROR_NO_AUTHORITY,

	// �� �� ���� ������
	GC_TRADE_ERROR_UNKNOWN,

	GC_PARTY_ERROR_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCPartyError;
//////////////////////////////////////////////////////////////////////////////

class GCPartyError : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_PARTY_ERROR; }
	PacketSize_t getPacketSize()  { return szBYTE + szObjectID; }
	string getPacketName()  { return "GCPartyError"; }
	string toString() ;

public:
	BYTE getCode()  { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }

	ObjectID_t getTargetObjectID(void) const { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) { m_TargetObjectID = id; }

private :
	ObjectID_t m_TargetObjectID;
	BYTE       m_Code; // �ڵ�
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyErrorFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPartyErrorFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCPartyError(); }
	string getPacketName()  { return "GCPartyError"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_PARTY_ERROR; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + szObjectID; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPartyErrorHandler;
//////////////////////////////////////////////////////////////////////////////

class GCPartyErrorHandler 
{
public:
	static void execute(GCPartyError* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
