//--------------------------------------------------------------------------------
// 
// Filename    : CGRequestInfo.h 
// Written By  : �輺��
// 
//--------------------------------------------------------------------------------

#ifndef __CG_REQUEST_INFO_H__
#define __CG_REQUEST_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"



//--------------------------------------------------------------------------------
//
// class CGRequestInfo;
//
//--------------------------------------------------------------------------------

class CGRequestInfo : public Packet {

public :
	enum REQUEST_INFO_CODE
	{
		REQUEST_CHARACTER_INFO,
		
		REQUEST_INFO_MAX
	};

public:
	
	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_INFO; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGRequestInfoPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szBYTE + szuint; }

	// get packet name
	string getPacketName()  { return "CGRequestInfo"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get / set Code
	BYTE getCode()  { return m_Code; }
	void setCode(BYTE code) throw() { m_Code = code; }

	// get / set Code
	uint getValue()  { return m_Value; }
	void setValue(uint value) throw() { m_Value = value; }

private :
	
	// Code
	BYTE    m_Code;
	uint    m_Value;

};


//--------------------------------------------------------------------------------
//
// class CGRequestInfoFactory;
//
// Factory for CGRequestInfo
//
//--------------------------------------------------------------------------------

class CGRequestInfoFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestInfo(); }

	// get packet name
	string getPacketName()  { return "CGRequestInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGRequestInfoPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + szuint; }

};


//--------------------------------------------------------------------------------
//
// class CGRequestInfoHandler;
//
//--------------------------------------------------------------------------------

class CGRequestInfoHandler {
	
public:

	// execute packet's handler
	static void execute(CGRequestInfo* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
