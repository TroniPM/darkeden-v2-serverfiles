//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddEffect.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_LOAD_INVENTORY_H__
#define __GC_LOAD_INVENTORY_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "EffectInfo.h"
#include "BloodBibleSignInfo.h"
//////////////////////////////////////////////////////////////////////////////
// class GCAddEffect;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCLoadInventory : public Packet 
{
public:
	GCLoadInventory() throw();
	~GCLoadInventory() throw();
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_LOAD_INVENTORY; }

	// 사이즈 재 정리와 규칙 계열 정리
	PacketSize_t getPacketSize()  {
	return m_pInventoryInfo->getSize();
	}

	string getPacketName()  { return "GCLoadInventory"; }
	string toString() ;

public:
	// get/set Inventory Info
	InventoryInfo* getInventoryInfo()  { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo) throw(Error) { m_pInventoryInfo = pInventoryInfo; }
	
private :
	InventoryInfo* m_pInventoryInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectFactory;
//////////////////////////////////////////////////////////////////////////////

class GCLoadInventoryFactory : public PacketFactory 
{
public :
	GCLoadInventoryFactory() throw() {}
	virtual ~GCLoadInventoryFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCLoadInventory(); }
	string getPacketName()  { return "GCLoadInventory"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_LOAD_INVENTORY; }

	PacketSize_t getPacketMaxSize()  { 
	return InventoryInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectHandler;
//////////////////////////////////////////////////////////////////////////////

class GCLoadInventoryHandler 
{
public:
	static void execute(GCLoadInventory* GCLoadInventory, Player* pPlayer);

};

#endif
