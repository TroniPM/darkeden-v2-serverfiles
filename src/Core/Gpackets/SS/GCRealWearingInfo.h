//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRealWearingInfo.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REAL_WEARING_INFO_H__
#define __GC_REAL_WEARING_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCRealWearingInfo;
//
//////////////////////////////////////////////////////////////////////

class GCRealWearingInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_REAL_WEARING_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szDWORD; }

	// get packet name
	string getPacketName()  { return "GCRealWearingInfo"; }
	
	// get packet's debug string
	string toString() ;
	
public :

	DWORD getInfo(void)  { return m_Info;}
	void setInfo(DWORD info) throw() { m_Info = info;}

private :
	
	DWORD m_Info;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRealWearingInfoFactory;
//
// Factory for GCRealWearingInfo
//
//////////////////////////////////////////////////////////////////////

class GCRealWearingInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRealWearingInfo(); }

	// get packet name
	string getPacketName()  { return "GCRealWearingInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_REAL_WEARING_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRealWearingInfoPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szDWORD; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRealWearingInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRealWearingInfoHandler {
	
public :

	// execute packet's handler
	static void execute(GCRealWearingInfo* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
