//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK4.h 
// Written By  : elca@ewestsoft.com
// Description : ��� �����ڴ� �� �� �ְ�, ����ڴ� �� �� ���� ������� ������ ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_ARMS_OK_4_H__
#define __GC_ATTACK_ARMS_OK_4_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK4;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK4 : public Packet {

public :
	
	// constructor
	GCAttackArmsOK4() throw();
	
	// destructor
	~GCAttackArmsOK4() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ATTACK_ARMS_OK_4; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
//	PacketSize_t getPacketSize() const throw() { return szObjectID + szObjectID + szbool; }
	PacketSize_t getPacketSize() const throw() { return szSkillType + szObjectID; }

	// get packet's name
	string getPacketName() const throw() { return "GCAttackArmsOK4"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID
//	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
//	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t skillType ) { m_SkillType = skillType ; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }
//	Coord_t getTargetX() const throw() { return m_X;}
//	Coord_t getTargetY() const throw() { return m_Y;}
//	void setTargetXY(Coord_t X, Coord_t Y) throw() { m_X = X; m_Y = Y;}

	// get / set success
//	bool getSkillSuccess() const throw() { return m_bSuccess;}
//	void setSkillSuccess(bool bSuccess) throw() { m_bSuccess = bSuccess;}

private :
	
	// ObjectID
//	ObjectID_t m_ObjectID;
//	Coord_t m_X, m_Y;

	SkillType_t m_SkillType;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

	// bool
//	bool m_bSuccess;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK4Factory;
//
// Factory for GCAttackArmsOK4
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK4Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackArmsOK4Factory() throw() {}
	
	// destructor
	virtual ~GCAttackArmsOK4Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAttackArmsOK4(); }

	// get packet name
	string getPacketName() const throw() { return "GCAttackArmsOK4"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ATTACK_ARMS_OK_4; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK4Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK4Handler {

public :

	// execute packet's handler
	static void execute(GCAttackArmsOK4* pGCAttackArmsOK4, Player* pPlayer) throw(Error);

};

#endif
