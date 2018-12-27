//--------------------------------------------------------------------------------
// 
// Filename    : GCMorph1.h 
// Written By  : crazydog
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_MORPH1_H__
#define __GC_MORPH1_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "GameTime.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
//
// class GCMorph1;
//
//	slayer���� vampire�� �����Ҷ�, �����Ͻô� �п��� ������ ��Ŷ.
//--------------------------------------------------------------------------------

class GCMorph1 : public Packet {

public :

	// constructor
	GCMorph1() ;

	// destructor
	~GCMorph1() ;
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MORPH_1; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		// [PCType][PCInfo]
		// [GameTime][Weather][WeatherLevel][DarkLevel][LightLevel]
		// [#NPCTypes][NPCType1]...[NPCTypeN]
		// [#MonsterTypes][MonsterType1]...[MonsterTypeM]
		return m_pPCInfo->getSize() 
			+ m_pInventoryInfo->getSize()
			+ m_pGearInfo->getSize()
			+ m_pExtraInfo->getSize();
	}

	// get packet name
	string getPacketName()  { return "GCMorph1"; }
	
	// get packet's debug string
	string toString() ;


//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get/set PC info
	PCInfo* getPCInfo2()  { return m_pPCInfo; }
	void setPCInfo2(PCInfo* pPCInfo)  { m_pPCInfo = pPCInfo; }

	// get/set Inventory Info
	InventoryInfo* getInventoryInfo()  { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo)  { m_pInventoryInfo = pInventoryInfo; }

	// get/set Gear Info
	GearInfo* getGearInfo()  { return m_pGearInfo; }
	void setGearInfo(GearInfo* pGearInfo)  { m_pGearInfo = pGearInfo; }

	// get/set ExtraInfo
	ExtraInfo* getExtraInfo()  { return m_pExtraInfo; }
	void setExtraInfo(ExtraInfo* pExtraInfo)  { m_pExtraInfo = pExtraInfo; }

//--------------------------------------------------
// data members
//--------------------------------------------------
private :

	//--------------------------------------------------------------------------------
	// PC Information
	//--------------------------------------------------------------------------------
	// PCSlayerInfo2 �Ǵ� PCVampireInfo2 �� ����Ѵ�.
	PCInfo* m_pPCInfo;

	//--------------------------------------------------------------------------------
	// Inventory Information
	//--------------------------------------------------------------------------------
	InventoryInfo* m_pInventoryInfo;

	//--------------------------------------------------------------------------------
	// Gear Information
	//--------------------------------------------------------------------------------
	GearInfo* m_pGearInfo;

	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	ExtraInfo* m_pExtraInfo;
	
	// inventory
	// quick item slot
	// gear

	// ����(PDA)
	// ���� ����Ʈ ����
	// ��������, �̺�Ʈ ����
	// ����.. ����� ó�� PDS�� �� �� �ٿ�����.. - -;


};


//--------------------------------------------------------------------------------
//
// class GCMorph1Factory;
//
// Factory for GCMorph1
//
//--------------------------------------------------------------------------------

class GCMorph1Factory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCMorph1(); }

	// get packet name
	string getPacketName()  { return "GCMorph1"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MORPH_1; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCMorph1PacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szBYTE + PCSlayerInfo2::getMaxSize() 
			+ InventoryInfo::getMaxSize()
			+ GearInfo::getMaxSize()
			+ ExtraInfo::getMaxSize()
			;
	}

};



//--------------------------------------------------------------------------------
//
// class GCMorph1Handler;
//
//--------------------------------------------------------------------------------

class GCMorph1Handler {

public :

	// execute packet's handler
	static void execute(GCMorph1* pPacket, Player* pPlayer) ;

};

#endif
