//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK4.h 
// Written By  : elca@ewestsoft.com
// Description : ��� �����ڴ� �� �� �ְ�, ����ڴ� �� �� ���� ������� ������ ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_KNOCKS_TARGET_BACK_OK_4_H__
#define __GC_KNOCKS_TARGET_BACK_OK_4_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK4;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK4 : public Packet {

public :
	
	// constructor
	GCKnocksTargetBackOK4() throw();
	
	// destructor
	~GCKnocksTargetBackOK4() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_KNOCKS_TARGET_BACK_OK_4; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
//	PacketSize_t getPacketSize()  { return szObjectID + szObjectID + szbool; }
	PacketSize_t getPacketSize()  { return szObjectID + szSkillType 
		+ szCoord*2 + szDir; }

	// get packet's name
	string getPacketName()  { return "GCKnocksTargetBackOK4"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
//	ObjectID_t getObjectID()  { return m_ObjectID; }
//	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }
//	Coord_t getTargetX()  { return m_X;}
//	Coord_t getTargetY()  { return m_Y;}
//	void setTargetXY(Coord_t X, Coord_t Y) throw() { m_X = X; m_Y = Y;}

	// get / set success
//	bool getSkillSuccess()  { return m_bSuccess;}
//	void setSkillSuccess(bool bSuccess) throw() { m_bSuccess = bSuccess;}
//	
    void setXYDir(Coord_t x, Coord_t y, Coord_t dir) throw()
    {
        m_X = x; m_Y = y; m_dir = dir;
    }
    Coord_t getX()  { return m_X;}
    Coord_t getY()  { return m_Y;}
    Dir_t getDir()  { return m_dir;}
	SkillType_t getSkillType()  { return m_SkillType;}
	void setSkillType(SkillType_t s) throw() { m_SkillType = s;}

private :
	
	// ObjectID
//	ObjectID_t m_ObjectID;
//	Coord_t m_X, m_Y;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;
	
    Coord_t m_X, m_Y;   // �̵��� ��ǥ.
    Dir_t m_dir;        // �з��� ����.
    SkillType_t m_SkillType;
			
	// bool
//	bool m_bSuccess;

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK4Factory;
//
// Factory for GCKnocksTargetBackOK4
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK4Factory : public PacketFactory {

public :
	
	// constructor
	GCKnocksTargetBackOK4Factory() throw() {}
	
	// destructor
	virtual ~GCKnocksTargetBackOK4Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCKnocksTargetBackOK4(); }

	// get packet name
	string getPacketName()  { return "GCKnocksTargetBackOK4"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_KNOCKS_TARGET_BACK_OK_4; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSkillType + szDir + szCoord*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK4Handler;
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK4Handler {

public :

	// execute packet's handler
	static void execute(GCKnocksTargetBackOK4* pGCKnocksTargetBackOK4, Player* pPlayer) throw(Error);

};

#endif
