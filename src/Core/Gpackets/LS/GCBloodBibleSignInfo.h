//////////////////////////////////////////////////////////////////////////////
// Filename    : GCBloodBibleSignInfo.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_BIBLE_SIGN_INFO_H__
#define __GC_BLOOD_BIBLE_SIGN_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "BloodBibleSignInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleSignInfo;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleSignInfo : public Packet
{
public:
	GCBloodBibleSignInfo() throw() { }
	virtual ~GCBloodBibleSignInfo() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_BLOOD_BIBLE_SIGN_INFO; }
	PacketSize_t getPacketSize()  { return m_pInfo->getSize(); }
	string getPacketName()  { return "GCBloodBibleSignInfo"; }
	string toString() ;

public:
	BloodBibleSignInfo* getSignInfo() const { return m_pInfo; }
	void setSignInfo(BloodBibleSignInfo* pInfo) { m_pInfo = pInfo; }

private:
	BloodBibleSignInfo*	m_pInfo;
};

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleSignInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleSignInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCBloodBibleSignInfo(); }
	string getPacketName()  { return "GCBloodBibleSignInfo"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_BLOOD_BIBLE_SIGN_INFO; }
	PacketSize_t getPacketMaxSize() 
	{
		return BloodBibleSignInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCBloodBibleSignInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCBloodBibleSignInfoHandler 
{
public:
	static void execute(GCBloodBibleSignInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
