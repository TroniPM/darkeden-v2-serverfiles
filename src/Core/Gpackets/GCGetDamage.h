//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCGetDamage.h 
// Written By  :  elca@ewestsoft.com
// Description :  Ŭ���̾�Ʈ�� ���� CGMove ��Ŷ�� ���� ������ 
//                ���� Ŭ���̾�Ʈ���� �����ص� ���ٴ� �㰡�� ����
//                �����ִ� ��Ŷ Ŭ�����̴�.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_DAMAGE_H__
#define __GC_GET_DAMAGE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamage;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCGetDamage : public Packet {

public :
	
	// constructor
	GCGetDamage() throw();
	
	// destructor
	~GCGetDamage() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_GET_DAMAGE; }
	
	// get packet size
	PacketSize_t getPacketSize() const throw() { return szObjectID + szWORD; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCGetDamage"; }
	
	// get packet's debug string
	string toString() const throw();
	
	// get/set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get/set Damage
	WORD getDamage() const throw() { return m_GetDamage; }
	void setDamage(WORD GetDamage) throw() { m_GetDamage = GetDamage; }
	
private : 
	ObjectID_t m_ObjectID;  // ObjectID..
	WORD m_GetDamage;   		// Damage..

};


//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamageFactory;
//
// Factory for  GCGetDamage
//
//////////////////////////////////////////////////////////////////////

class  GCGetDamageFactory : public PacketFactory {

public :
	
	// constructor
	 GCGetDamageFactory() throw() {}
	
	// destructor
	virtual ~GCGetDamageFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCGetDamage(); }

	// get packet name
	string getPacketName() const throw() { return "GCGetDamage"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GET_DAMAGE; }
	
	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szWORD; }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCGetDamageHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCGetDamageHandler {

public :

	// execute packet's handler
	static void execute( GCGetDamage* pGCGetDamage, Player* pPlayer) throw(Error);

};

#endif
