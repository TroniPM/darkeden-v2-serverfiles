//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseBonusPointOK.h 
// Written By  : crazydog
// Description : vamp�� bonus����� �㰡 �޴�.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_BONUS_POINT_OK_H__
#define __GC_USE_BONUS_POINT_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointOK : public ModifyInfo {

public :

	// Constructor
	GCUseBonusPointOK() throw();

	// Desctructor
	~GCUseBonusPointOK() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_USE_BONUS_POINT_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCUseBonusPointOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return ModifyInfo::getPacketSize(); }

	// get packet name
	string getPacketName() const throw() { return "GCUseBonusPointOK"; }
	
	// get packet's debug string
	string toString() const throw();

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointOKFactory;
//
// Factory for GCUseBonusPointOK
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUseBonusPointOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCUseBonusPointOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_USE_BONUS_POINT_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUseBonusPointOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCUseBonusPointOK* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
