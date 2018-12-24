//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReloadOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RELOAD_OK_H__
#define __GC_RELOAD_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOK;
//
//////////////////////////////////////////////////////////////////////

class GCReloadOK : public Packet {

public :

	// Constructor
	GCReloadOK() throw();

	// Desctructor
	~GCReloadOK() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RELOAD_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCReloadOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szBullet; }

	// get packet name
	string getPacketName() const throw() { return "GCReloadOK"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set BulletNum
	Bullet_t getBulletNum() const throw() { return m_BulletNum; }
	void setBulletNum(Bullet_t BulletNum) throw() { m_BulletNum = BulletNum; }
	

private :
	
	// BulletNum
	Bullet_t m_BulletNum;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOKFactory;
//
// Factory for GCReloadOK
//
//////////////////////////////////////////////////////////////////////

class GCReloadOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCReloadOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCReloadOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RELOAD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReloadOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szBullet; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCReloadOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReloadOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCReloadOK* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
