//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherModifyInfo.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_MODIFY_INFO_H__
#define __GC_OTHER_MODIFY_INFO_H__

#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfo;
//////////////////////////////////////////////////////////////////////////////

class GCOtherModifyInfo : public ModifyInfo 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_OTHER_MODIFY_INFO; }
	PacketSize_t getPacketSize()  { return szObjectID + ModifyInfo::getPacketSize(); }
	string getPacketName()  { return "GCOtherModifyInfo"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private:
	ObjectID_t m_ObjectID;
};


//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCOtherModifyInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCOtherModifyInfo(); }
	string getPacketName()  { return "GCOtherModifyInfo"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_OTHER_MODIFY_INFO; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCOtherModifyInfoHandler 
{
public:
	static void execute(GCOtherModifyInfo* pGCOtherModifyInfo, Player* pPlayer);
};

#endif
