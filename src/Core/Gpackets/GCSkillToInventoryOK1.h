//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_INVENTORY_OK_1_H__
#define __GC_SKILL_TO_INVENTORY_OK_1_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK1 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToInventoryOK1() ;
	
	// destructor
	~GCSkillToInventoryOK1() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_INVENTORY_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize()  { return szSkillType + szObjectID + szItemType + szCEffectID + szCoordInven* 2
			+ szDuration + ModifyInfo::getPacketSize() + szItemClass; }

	// get packet's name
	string getPacketName()  { return "GCSkillToInventoryOK1"; }
	
	// get packet's debug string
	string toString() ;

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set ItemType
	ItemType_t getItemType()  { return m_ItemType; }
	void setItemType(ItemType_t ItemType)  { m_ItemType = ItemType; }

	// get / set CEffectID
	CEffectID_t getCEffectID()  { return m_CEffectID; }
	void setCEffectID(CEffectID_t CEffectID)  { m_CEffectID = CEffectID; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration)  { m_Duration = Duration; }

	// get / set X, Y
	CoordInven_t getX() { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	CoordInven_t getY() { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

	ItemClass_t getItemClass()  { return m_ItemClass;}
	void setItemClass( ItemClass_t c)  { m_ItemClass = c;}

private :
	
	// SkillType
	SkillType_t m_SkillType;

	// ObjectID
	ObjectID_t m_ObjectID;

	// ItemType
	ItemType_t m_ItemType;

	// CEffectID
	CEffectID_t m_CEffectID;

	// Duration
	Duration_t m_Duration;

	// Inventory X, Y Position
	CoordInven_t m_X;
	CoordInven_t m_Y;

	ItemClass_t	 m_ItemClass;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK1Factory;
//
// Factory for GCSkillToInventoryOK1
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToInventoryOK1Factory()  {}
	
	// destructor
	virtual ~GCSkillToInventoryOK1Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToInventoryOK1(); }

	// get packet name
	string getPacketName()  { return "GCSkillToInventoryOK1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_INVENTORY_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szObjectID + szItemType + szCEffectID + szCoord* 2
			+ szDuration + ModifyInfo::getPacketMaxSize() + szItemClass; }

};



//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK1Handler;
//
//////////////////////////////////////////////////////////////////////
class GCSkillToInventoryOK1Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToInventoryOK1* pGCSkillToInventoryOK1, Player* pPlayer);

};

#endif
