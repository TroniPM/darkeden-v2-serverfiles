//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRegenZoneStatus.h 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REGEN_ZONE_STATUS_H__
#define __GC_REGEN_ZONE_STATUS_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#include <vector>

//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatus;
//
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatus : public Packet {

public :
	GCRegenZoneStatus() { for( int i=0; i<8; ++i ) m_Statuses.push_back(0); }
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_REGEN_ZONE_STATUS; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE * 8; }

	// get packet name
	string getPacketName() const throw() { return "GCRegenZoneStatus"; }
	
	// get packet's debug string
	string toString() const throw();

	BYTE getStatus( uint index ) const { return m_Statuses[index]; }
	void setStatus( uint index, BYTE status ) { m_Statuses[index] = status; }

private :
	vector<BYTE>	m_Statuses;
};


//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatusFactory;
//
// Factory for GCRegenZoneStatus
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatusFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRegenZoneStatus(); }

	// get packet name
	string getPacketName() const throw() { return "GCRegenZoneStatus"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_REGEN_ZONE_STATUS; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRegenZoneStatusPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE * 8; } 
};


//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatusHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatusHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCRegenZoneStatus* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
