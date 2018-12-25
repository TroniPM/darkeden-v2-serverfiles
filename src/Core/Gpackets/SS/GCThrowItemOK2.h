//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowItemOK2.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_ITEM_OK_2_H__
#define __GC_THROW_ITEM_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK2;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK2 : public ModifyInfo {

public :
	
	// constructor
	GCThrowItemOK2() throw();
	
	// destructor
	~GCThrowItemOK2() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_THROW_ITEM_OK_2; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCThrowItemOK2"; }
	
	// get packet's debug string
	string toString() ;

	// get / set TargetObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// TargetObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK2Factory;
//
// Factory for GCThrowItemOK2
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowItemOK2Factory() throw() {}
	
	// destructor
	virtual ~GCThrowItemOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCThrowItemOK2(); }

	// get packet name
	string getPacketName()  { return "GCThrowItemOK2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_THROW_ITEM_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowItemOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowItemOK2Handler {

public :

	// execute packet's handler
	static void execute(GCThrowItemOK2* pGCThrowItemOK2, Player* pPlayer) throw(Error);

};

#endif
