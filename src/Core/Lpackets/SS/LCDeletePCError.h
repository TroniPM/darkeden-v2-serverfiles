//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCDeletePCError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_DELETE_PC_ERROR_H__
#define __LC_DELETE_PC_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCDeletePCError;
//
//////////////////////////////////////////////////////////////////////

class LCDeletePCError : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_DELETE_PC_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "LCDeletePCError"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set error message
//	string getMessage()  { return m_Message; }
//	void setMessage(string message) throw() { m_Message = message; }
	// get /set ErrorID
	BYTE getErrorID()  { return m_ErrorID; }
	void setErrorID(BYTE ErrorID) throw() { m_ErrorID = ErrorID; }

private : 

	// ���� �޽���
	BYTE m_ErrorID;

};


//////////////////////////////////////////////////////////////////////
//
// class LCDeletePCErrorFactory;
//
// Factory for LCDeletePCError
//
//////////////////////////////////////////////////////////////////////

class LCDeletePCErrorFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCDeletePCError(); }

	// get packet name
	string getPacketName()  { return "LCDeletePCError"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_DELETE_PC_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCDeletePCErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCDeletePCErrorHandler {

public:

	// execute packet's handler
	static void execute(LCDeletePCError* pPacket, Player* pPlayer) ;

};

#endif
