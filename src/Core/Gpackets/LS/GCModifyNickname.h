//////////////////////////////////////////////////////////////////////////////
// Filename    : GCModifyNickname.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_NICKNAME_H__
#define __GC_MODIFY_NICKNAME_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "Types.h"

#include "NicknameInfo.h"

class GCModifyNickname : public Packet
{
public:
	GCModifyNickname() ;
	virtual ~GCModifyNickname() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_MODIFY_NICKNAME; }
	PacketSize_t getPacketSize()  { return szObjectID + m_pNicknameInfo->getSize(); }
	string getPacketName()  { return "GCModifyNickname"; }
	string toString() ;

public:
	void		setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }
	ObjectID_t	getObjectID() const { return m_ObjectID; }

//	NicknameInfo&	getNicknameInfo() { return m_NicknameInfo; }
	NicknameInfo*	getNicknameInfo() const { return m_pNicknameInfo; }
	void			setNicknameInfo(NicknameInfo* pNicknameInfo) { m_pNicknameInfo = pNicknameInfo; }
private:
	ObjectID_t		m_ObjectID;
	NicknameInfo*	m_pNicknameInfo;
};

class GCModifyNicknameFactory : public PacketFactory {

public :
	
	Packet* createPacket()  { return new GCModifyNickname(); }
	string getPacketName()  { return "GCModifyNickname"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MODIFY_NICKNAME; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + NicknameInfo::getMaxSize(); }
};

class GCModifyNicknameHandler {
	
public :
	static void execute(GCModifyNickname* pPacket, Player* pPlayer) ;

};

#endif // __GC_MODIFY_NICKNAME_H__

