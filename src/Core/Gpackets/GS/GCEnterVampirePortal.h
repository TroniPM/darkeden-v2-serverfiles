//////////////////////////////////////////////////////////////////////////////
// Filename    : GCEnterVampirePortal.h 
// Written By  : excel96
// Description : 
// �����̾ �����̾� ��Ż�� ���� ������� ���,
// ������ ��ε�ĳ���õǴ� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ENTER_VAMPIRE_PORTAL_H__
#define __GC_ENTER_VAMPIRE_PORTAL_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCEnterVampirePortal;
//////////////////////////////////////////////////////////////////////////////

class GCEnterVampirePortal : public Packet 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ENTER_VAMPIRE_PORTAL; }
	PacketSize_t getPacketSize()  { return szObjectID + szCoord*2; }
	string getPacketName()  { return "GCEnterVampirePortal"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID)  { m_ObjectID = creatureID; }

	Coord_t getX(void) const { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY(void) const { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

private:
	ObjectID_t m_ObjectID;
	Coord_t    m_X;
	Coord_t    m_Y;
};

//////////////////////////////////////////////////////////////////////////////
// class GCEnterVampirePortalFactory;
//////////////////////////////////////////////////////////////////////////////

class GCEnterVampirePortalFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCEnterVampirePortal(); }
	string getPacketName()  { return "GCEnterVampirePortal"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ENTER_VAMPIRE_PORTAL; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord*2; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCEnterVampirePortalHandler;
//////////////////////////////////////////////////////////////////////////////

class GCEnterVampirePortalHandler 
{
public:
	static void execute(GCEnterVampirePortal* pPacket, Player* pPlayer) ;
};

#endif
