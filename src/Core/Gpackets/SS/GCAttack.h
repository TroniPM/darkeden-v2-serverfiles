//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttack.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_H__
#define __GC_ATTACK_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttack;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCAttack : public Packet {

public :
	
	// constructor
	GCAttack() throw();
	
	// destructor
	~GCAttack() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_ATTACK; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szCoord + szCoord + szDir ; }

	// get packet's name
	string getPacketName()  { return "GCAttack"; }
	
	// get packet's debug string
	string toString() ;

	// get Object ID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

	// get/set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	// get/set Dir
	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }


private :

	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_X;				// X ��ǥ
	Coord_t m_Y;				// Y ��ǥ
	Dir_t m_Dir;				// ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackFactory;
//
// Factory for GCAttack
//
//////////////////////////////////////////////////////////////////////

class GCAttackFactory : public PacketFactory {

public :
	
	// constructor
	GCAttackFactory() throw() {}
	
	// destructor
	virtual ~GCAttackFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAttack(); }

	// get packet name
	string getPacketName()  { return "GCAttack"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ATTACK; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord + szCoord + szDir ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackHandler {

public :

	// execute packet's handler
	static void execute(GCAttack* pGCAttack, Player* pPlayer) throw(Error);

};

#endif
