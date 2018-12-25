//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestPowerPoint.h 
// Written By  : bezz
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_POWER_POINT_H__
#define __CG_REQUEST_POWER_POINT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPoint;
//////////////////////////////////////////////////////////////////////////////

class CGRequestPowerPoint : public Packet
{
public:
	CGRequestPowerPoint ();
	~CGRequestPowerPoint ();
	
public:
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
    void write ( SocketOutputStream & oStream ) ;
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
    PacketID_t getPacketID ()  { return PACKET_CG_REQUEST_POWER_POINT; }
	PacketSize_t getPacketSize ()  { return szBYTE + m_CellNum.size(); }
	string getPacketName ()  { return "CGRequestPowerPoint"; }
	string toString () ;

public:
	// get / set cell number
	const string& getCellNum() const { return m_CellNum; }
	void setCellNum( const string& cellnum ) { m_CellNum = cellnum; }

protected:
	string			m_CellNum;
};

//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPointFactory;
//////////////////////////////////////////////////////////////////////////////

class CGRequestPowerPointFactory : public PacketFactory 
{
public:
	Packet * createPacket () throw () { return new CGRequestPowerPoint(); }
	string getPacketName ()  { return "CGRequestPowerPoint"; }
	PacketID_t getPacketID ()  { return Packet::PACKET_CG_REQUEST_POWER_POINT; }
	PacketSize_t getPacketMaxSize ()  { return szBYTE + 12;}
};

//////////////////////////////////////////////////////////////////////////////
// class CGRequestPowerPointHandler;
//////////////////////////////////////////////////////////////////////////////

class CGRequestPowerPointHandler 
{
public:
	static void execute ( CGRequestPowerPoint * pCGRequestPowerPoint , Player * pPlayer );
};


#endif

