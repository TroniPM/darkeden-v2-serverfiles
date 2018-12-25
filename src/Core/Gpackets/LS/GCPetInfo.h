//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetInfo.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_PET_INFO_H__
#define __GC_PET_INFO_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

#include "PetInfo.h"

class GCPetInfo : public Packet
{
public:
	GCPetInfo() throw();
	virtual ~GCPetInfo() throw();

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_PET_INFO; }
	PacketSize_t getPacketSize()  { return szObjectID + ((m_pPetInfo!=NULL)?(m_pPetInfo->getSize()):szPetType); }
	string getPacketName()  { return "GCPetInfo"; }
	string toString() ;

public:
	void		setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	ObjectID_t	getObjectID() const { return m_ObjectID; }

	BYTE		isSummonInfo() const { return m_IsSummonInfo; }
	void		setSummonInfo( BYTE isSummon ) { m_IsSummonInfo = isSummon; }

	void		setPetInfo(PetInfo* pPetInfo) { m_pPetInfo = pPetInfo; }
	PetInfo*	getPetInfo() const { return m_pPetInfo; }
private:
	ObjectID_t	m_ObjectID;
	PetInfo*	m_pPetInfo;
	BYTE		m_IsSummonInfo;
};

class GCPetInfoFactory : public PacketFactory {

public :
	
	Packet* createPacket() throw() { return new GCPetInfo(); }
	string getPacketName()  { return "GCPetInfo"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_PET_INFO; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + PetInfo::getMaxSize(); }
};

class GCPetInfoHandler {
	
public :
	static void execute(GCPetInfo* pPacket, Player* pPlayer) ;

};

#endif // __GC_PET_INFO_H__

