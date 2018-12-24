//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectWayPoint.h 
// Written By  : excel96
// Description : 
// �����̾ ���ο� ��Ż�� �̿��� �ٸ� ������ �̵��ϰ��� �� �� ������ ��Ŷ
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_WAYPOINT_H__
#define __CG_SELECT_WAYPOINT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectWayPoint;
//////////////////////////////////////////////////////////////////////////////

class CGSelectWayPoint : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_SELECT_WAYPOINT; }
	PacketSize_t getPacketSize() const throw() { return szZoneID + szCoord*2; }
	string getPacketName() const throw() { return "CGSelectWayPoint"; }
	string toString() const throw();

public:
	ZoneID_t getZoneID() const throw()  { return m_ZoneID; }
	void setZoneID(ZoneID_t ZoneID) throw() { m_ZoneID = ZoneID; }

	Coord_t getX(void) const { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY(void) const { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

private:
	ZoneID_t   m_ZoneID;       // ������ �ϴ� ���� ID
	Coord_t    m_X;            // ������ �ϴ� ���� ��ǥ X
	Coord_t    m_Y;            // ������ �ϴ� ���� ��ǥ Y

};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectWayPointFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSelectWayPointFactory : public PacketFactory 
{
	Packet* createPacket() throw() { return new CGSelectWayPoint(); }
	string getPacketName() const throw() { return "CGSelectWayPoint"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SELECT_WAYPOINT; }
	PacketSize_t getPacketMaxSize() const throw() { return szZoneID + szCoord*2; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectWayPointHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSelectWayPointHandler 
{
public:
	static void execute(CGSelectWayPoint* pCGSelectWayPoint, Player* pPlayer) throw(Error);
	static void executeEnterQuestZone(CGSelectWayPoint* pCGSelectWayPoint, Player* pPlayer, int targetDynamicZoneType ) throw(Error);
};

#endif
