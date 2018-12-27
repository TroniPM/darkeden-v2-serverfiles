//////////////////////////////////////////////////////////////////////////////
// Filename    : GCRequestedIP.h 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_REQUESTED_IP_H__
#define __GC_REQUESTED_IP_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCRequestedIP;
//////////////////////////////////////////////////////////////////////////////

class GCRequestedIP : public Packet
{
public:
	GCRequestedIP ();
	~GCRequestedIP ();
	
public:
    void read ( SocketInputStream & iStream ) ;
    void write ( SocketOutputStream & oStream ) ;
	void execute ( Player * pPlayer ) ;
    PacketID_t getPacketID ()  { return PACKET_GC_REQUESTED_IP; }
	string getPacketName ()  { return "GCRequestedIP"; }
	PacketSize_t getPacketSize ()  { return szBYTE + szuint + m_Name.size() + 4; }
	string toString () ;

public:
	string getName()  { return m_Name;}
	void setName( const char* pName)  { m_Name = pName;}

	void setIP(IP_t ip)  { m_IP = ip; }
	IP_t getIP()  { return m_IP; }

	void setPort(uint port)  { m_Port = port; }
	uint getPort()  { return m_Port; }

protected:
	string m_Name;
	IP_t   m_IP;
	uint   m_Port;
};

//////////////////////////////////////////////////////////////////////////////
// class GCRequestedIPFactory;
//////////////////////////////////////////////////////////////////////////////

class GCRequestedIPFactory : public PacketFactory 
{
public:
	Packet * createPacket ()  { return new GCRequestedIP(); }
	string getPacketName ()  { return "GCRequestedIP"; }
	PacketID_t getPacketID ()  { return Packet::PACKET_GC_REQUESTED_IP; }
	PacketSize_t getPacketMaxSize ()  { return szBYTE + szuint + 10 + 4;}
};

//////////////////////////////////////////////////////////////////////////////
// class GCRequestedIPHandler;
//////////////////////////////////////////////////////////////////////////////

class GCRequestedIPHandler 
{
public:
	static void execute ( GCRequestedIP * pGCRequestedIP , Player * pPlayer );
};

#endif
