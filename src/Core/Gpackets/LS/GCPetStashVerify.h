//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetStashVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PET_STASH_VERIFY_H__
#define __GC_PET_STASH_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

enum
{
	PET_STASH_OK,
	PET_STASH_NOT_ENOUGH_MONEY,
	PET_STASH_NO_INVENTORY_SPACE,
	PET_STASH_RACK_IS_NOT_EMPTY,	// �ش� ��ġ�� �̹� �ٸ� �� �������� �ֽ��ϴ�.
	PET_STASH_RACK_IS_EMPTY,		// ã������ �� ��ġ�� �������� �����ϴ�.
	PET_STASH_INVALID_OID,			// ObjectID �� ���� �ʽ��ϴ�.
	PET_STASH_INVALID_INDEX,		// Index�� ���� �ʽ��ϴ�.
};

//////////////////////////////////////////////////////////////////////////////
// class GCPetStashVerify
//////////////////////////////////////////////////////////////////////////////

class GCPetStashVerify : public Packet 
{
public:
	GCPetStashVerify() throw() { m_Code = PET_STASH_OK; }
	virtual ~GCPetStashVerify() throw() {}

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t getPacketID()  { return PACKET_GC_PET_STASH_VERIFY; }
	PacketSize_t getPacketSize()  { return szBYTE; }
	string getPacketName()  { return "GCPetStashVerify"; }
	string toString() ;
	
public:
	BYTE getCode(void)  { return m_Code;}
	void setCode(BYTE code) throw() { m_Code = code;}

private: 
	BYTE m_Code;
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetStashVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCPetStashVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCPetStashVerify(); }
	string getPacketName()  { return "GCPetStashVerify"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_PET_STASH_VERIFY; }
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCPetStashVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCPetStashVerifyHandler 
{
public:
	static void execute( GCPetStashVerify* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
