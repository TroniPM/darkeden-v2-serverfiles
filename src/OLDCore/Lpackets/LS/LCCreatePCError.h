//////////////////////////////////////////////////////////////////////////////
// Filename    : LCCreatePCError.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __LC_CREATE_PC_ERROR_H__
#define __LC_CREATE_PC_ERROR_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class LCCreatePCError;
//
// PC Creation �� �������� ���, �α��� ������ Ŭ���̾�Ʈ���� �� ��Ŷ��
// ������.
//////////////////////////////////////////////////////////////////////////////

class LCCreatePCError : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_LC_CREATE_PC_ERROR; }
	PacketSize_t getPacketSize() const throw() { return szBYTE; }
	string getPacketName() const throw() { return "LCCreatePCError"; }
	string toString() const throw();

public:
	BYTE getErrorID() const throw() { return m_ErrorID; }
	void setErrorID(BYTE ErrorID) throw() { m_ErrorID = ErrorID; }

private: 
	BYTE m_ErrorID;
};

//////////////////////////////////////////////////////////////////////////////
// class LCCreatePCErrorFactory;
//////////////////////////////////////////////////////////////////////////////

class LCCreatePCErrorFactory : public PacketFactory 
{
public:
	
	// create packet
	Packet* createPacket() throw() { return new LCCreatePCError(); }

	// get packet name
	string getPacketName() const throw() { return "LCCreatePCError"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_LC_CREATE_PC_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCErrorHandler {

public:

	// execute packet's handler
	static void execute(LCCreatePCError* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
