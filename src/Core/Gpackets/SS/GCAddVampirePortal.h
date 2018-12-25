//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddVampirePortal.h 
// Written By  : excel96
// Description :
// �����̾� ��Ż�� ���� ����Ʈ�� �������μ� �����Ǵµ�, �� ��Ŷ��
// Ŭ���̾�Ʈ���� �ٴڿ��� �����̾� ��Ż ����Ʈ�� ���̶�� ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_VAMPIRE_PORTAL_H__
#define __GC_ADD_VAMPIRE_PORTAL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampirePortal;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampirePortal : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_ADD_VAMPIRE_PORTAL; }
	PacketSize_t getPacketSize()  
	{ 
		return szObjectID + szBYTE + m_OwnerID.size() + szDuration 
			+ szCoord*2 + szZoneID + szCoord*2 + szBYTE;
	}
	string getPacketName()  { return "GCAddVampirePortal"; }
	string toString() ;

public:
	ObjectID_t getObjectID(void) const { return m_ObjectID; }
	void setObjectID(ObjectID_t d) { m_ObjectID = d; }

	string getOwnerID(void) const { return m_OwnerID; }
	void setOwnerID(string ownerID) { m_OwnerID = ownerID; }

	Duration_t getDuration() const { return m_Duration; }
	void setDuration(Duration_t d) { m_Duration = d; }

	Coord_t getX(void) const { return m_X; }
	void setX(Coord_t x) { m_X = x; }
	
	Coord_t getY(void) const { return m_Y; }
	void setY(Coord_t x) { m_Y = x; }

	ZoneID_t getTargetZoneID(void) const { return m_TargetZoneID; }
	void setTargetZoneID(ZoneID_t id) { m_TargetZoneID = id; }

	Coord_t getTargetX(void) const { return m_TargetX; }
	void setTargetX(Coord_t x) { m_TargetX = x; }
	
	Coord_t getTargetY(void) const { return m_TargetY; }
	void setTargetY(Coord_t x) { m_TargetY = x; }

	BYTE getCreateFlag(void) const { return m_CreateFlag; }
	void setCreateFlag(BYTE flag) { m_CreateFlag = flag; }

	
private:
	ObjectID_t  m_ObjectID;       // ����Ʈ�� OID
	string      m_OwnerID;        // ��Ż ����
	Duration_t	m_Duration;       // ��Ż�� ���� �ð�
	Coord_t     m_X;              // ��Ż�� �پ��ִ� Ÿ���� ��ǥ x
	Coord_t     m_Y;              // ��Ż�� �پ��ִ� Ÿ���� ��ǥ y
	ZoneID_t    m_TargetZoneID;   // ��Ż�� ��ǥ �� ID
	Coord_t     m_TargetX;        // ��Ż�� ��ǥ ��ǥ x
	Coord_t     m_TargetY;        // ��Ż�� ��ǥ ��ǥ y
	BYTE        m_CreateFlag;     // ��� �����Ǿ��°�? (0�̸� �������� �ð��� �� ���� ��...)
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampirePortalFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampirePortalFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddVampirePortal(); }
	string getPacketName()  { return "GCAddVampirePortal"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_VAMPIRE_PORTAL; }
	PacketSize_t getPacketMaxSize() 
	{ 
		return szObjectID + szBYTE + 20 + szDuration 
			+ szCoord*2 + szZoneID + szCoord*2 + szBYTE;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampirePortalHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampirePortalHandler 
{
public:
	static void execute(GCAddVampirePortal* pGCAddVampirePortal, Player* pPlayer) throw(Error);
};

#endif
