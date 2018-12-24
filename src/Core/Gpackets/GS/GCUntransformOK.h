//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCUntransformOK.h 
// Written By  :  Elca
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNTRANSFORM_OK_H__
#define __GC_UNTRANSFORM_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformOK;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCUntransformOK : public Packet {

public :

	// constructor
	GCUntransformOK() throw() {}
	GCUntransformOK(Coord_t x, Coord_t y, Dir_t dir) throw() : m_X(x), m_Y(y), m_Dir(dir) {}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_UNTRANSFORM_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static GCUntransformOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() { return szCoord + szCoord + szDir; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCUntransformOK"; }
	
	// get packet's debug string
	string toString() const throw();
	

public :

	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y ; }

	// get/set Dir
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }
	

private : 

	Coord_t m_X;   // ��ǥ X ��ǥ
	Coord_t m_Y;   // ��ǥ Y ��ǥ
	Dir_t m_Dir;   // ��ǥ ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCUntransformOKFactory;
//
// Factory for GCUntransformOK
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUntransformOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCUntransformOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_UNTRANSFORM_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUntransformOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szCoord + szCoord + szDir; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformOKHandler {

public :

	// execute packet's handler
	static void execute( GCUntransformOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
