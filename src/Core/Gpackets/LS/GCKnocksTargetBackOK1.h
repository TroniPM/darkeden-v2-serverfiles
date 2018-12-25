//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_KNOCKS_TARGET_BACK_OK_1_H__
#define __GC_KNOCKS_TARGET_BACK_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"
#include "ModifyItemInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1 : public ModifyInfo {

public :
	
	// constructor
	GCKnocksTargetBackOK1() throw();
	
	// destructor
	~GCKnocksTargetBackOK1() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_KNOCKS_TARGET_BACK_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szSkillType + szDir + szCoord*2 + szObjectID + szBullet + szbool + ModifyInfo::getPacketSize() ;}

	// get packet's name
	string getPacketName()  { return "GCKnocksTargetBackOK1"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set Success
	bool getSkillSuccess()  { return m_bSuccess; }
	void setSkillSuccess(bool Success) throw() { m_bSuccess = Success; }
	
	// get / set Bullet Num
	Bullet_t getBullet()  { return m_BulletNum; }
	void setBulletNum(Bullet_t BulletNum) { m_BulletNum = BulletNum; }

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
	ObjectID_t m_ObjectID;

	// Bullet Num
	Bullet_t m_BulletNum;

	bool m_bSuccess;
	
	Coord_t m_X, m_Y;	// �̵��� ��ǥ.
	Dir_t m_dir;		// �з��� ����.
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1Factory;
//
// Factory for GCKnocksTargetBackOK1
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCKnocksTargetBackOK1Factory() throw() {}
	
	// destructor
	virtual ~GCKnocksTargetBackOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCKnocksTargetBackOK1(); }

	// get packet name
	string getPacketName()  { return "GCKnocksTargetBackOK1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_KNOCKS_TARGET_BACK_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szDir + szCoord*2 + szObjectID + szBullet + szbool + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1Handler {

public :

	// execute packet's handler
	static void execute(GCKnocksTargetBackOK1* pGCKnocksTargetBackOK1, Player* pPlayer);

};

#endif
