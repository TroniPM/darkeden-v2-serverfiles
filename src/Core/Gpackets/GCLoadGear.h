//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddEffect.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_LOAD_GEAR_H__
#define __GC_LOAD_GEAR_H__

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
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCLoadGear : public Packet 
{
public:
	GCLoadGear() ;
	~GCLoadGear() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_LOAD_GEAR; }

	// ������ �� ������ ��Ģ �迭 ����
	PacketSize_t getPacketSize()  {
	return m_pGearInfo->getSize() + m_pBloodBibleSign->getSize();
	}

	string getPacketName()  { return "GCLoadGear"; }
	string toString() ;

public:
	uchar getType() { return m_Type; }
	void setType(uchar Type) { m_Type = Type; }

	// get/set Inventory Info
	InventoryInfo* getInventoryInfo()  { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo)  { m_pInventoryInfo = pInventoryInfo; }

	// get/set Gear Info
	GearInfo* getGearInfo()  { return m_pGearInfo; }
	void setGearInfo(GearInfo* pGearInfo)  { m_pGearInfo = pGearInfo; }

	// get/set ExtraInfo
	ExtraInfo* getExtraInfo()  { return m_pExtraInfo; }
	void setExtraInfo(ExtraInfo* pExtraInfo)  { m_pExtraInfo = pExtraInfo; }

	// get/set EffectInfo
	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo)  { m_pEffectInfo = pEffectInfo; }

	BloodBibleSignInfo*	getBloodBibleSignInfo() { return m_pBloodBibleSign; }
	void	setBloodBibleSignInfo( BloodBibleSignInfo* pInfo ) { m_pBloodBibleSign = pInfo; }
	
private :
	uchar m_Type;
	InventoryInfo* m_pInventoryInfo;
	GearInfo* m_pGearInfo;
	ExtraInfo* m_pExtraInfo;
	EffectInfo* m_pEffectInfo;
	BloodBibleSignInfo* m_pBloodBibleSign;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectFactory;
//////////////////////////////////////////////////////////////////////////////

class GCLoadGearFactory : public PacketFactory 
{
public :
	GCLoadGearFactory()  {}
	virtual ~GCLoadGearFactory()  {}
	
public:
	Packet* createPacket()  { return new GCLoadGear(); }
	string getPacketName()  { return "GCLoadGear"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_LOAD_GEAR; }

	PacketSize_t getPacketMaxSize()  { 
	return GearInfo::getMaxSize() + BloodBibleSignInfo::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectHandler;
//////////////////////////////////////////////////////////////////////////////

class GCLoadGearHandler 
{
public:
	static void execute(GCLoadGear* GCLoadGear, Player* pPlayer);

};

#endif
