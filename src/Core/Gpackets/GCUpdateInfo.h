//--------------------------------------------------------------------------------
// 
// Filename    : GCUpdateInfo.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_UPDATE_INFO_H__
#define __GC_UPDATE_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "GameTime.h"
#include "PCSlayerInfo2.h"
#include "PCSlayerInfo3.h"
#include "PCVampireInfo2.h"
#include "InventoryInfo.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "EffectInfo.h"
#include "Assert.h"
#include "RideMotorcycleInfo.h"
#include "NPCInfo.h"
#include "NicknameInfo.h"
#include "BloodBibleSignInfo.h"

#define FLAG_PREMIUM_ZONE			0x10	// premium���� ������ ���̴�.
#define FLAG_PREMIUM_PLAY			0x01	// premium play�� �ϴ� ���ΰ�?

//--------------------------------------------------------------------------------
//
// class GCUpdateInfo;
//
// Ŭ���̾�Ʈ�� ���� ������ �����ؼ� CGConnect ��Ŷ�� ������, ���� ������ ũ��ó��
// ���� �������� �ε��ؼ� ���� �� �غ� �ϰ� �ȴ�. �״��� PC�� ������ ����,
// �׸��� �� ������ GCUpdateInfo�� ��Ƽ� Ŭ���̾�Ʈ�� �����ϰ� �ȴ�.
//
//--------------------------------------------------------------------------------

class GCUpdateInfo : public Packet {

public :

	enum
	{
		UNION_MASTER = 0,		// ��忬���� ���ո����ʹ�
		UNION_GUILD_MASTER,		// ��忬���� ���ո����Ͱ� �ƴ����� �Ҽӵ� ����� �����ʹ�
		UNION_NOTHING,			// �ƹ��͵� �ƴϴ�.
		UNION_MAX
	};
	
	// constructor
	GCUpdateInfo() throw();

	// destructor
	~GCUpdateInfo() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_UPDATE_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		// [PCType][PCInfo]
		// [GameTime][Weather][WeatherLevel][DarkLevel][LightLevel]
		// [#NPCTypes][NPCType1]...[NPCTypeN]
		// [#MonsterTypes][MonsterType1]...[MonsterTypeM]
		PacketSize_t size = 0;

		WORD MotorcycleSize = 0;
		if(m_hasMotorcycle) 
		{
			MotorcycleSize = m_pRideMotorcycleInfo->getSize();
		}

		size += szBYTE;
		size += m_pPCInfo->getSize();
		//size += m_pInventoryInfo->getSize();
		size += m_pGearInfo->getSize();
		size += m_pExtraInfo->getSize();
		size += szBYTE;
		size += MotorcycleSize;
		size += m_pEffectInfo->getSize();
		size += szZoneID;
		size += szCoord;
		size += szCoord;
		size += m_GameTime.getSize();
		size += szWeather;
		size += szWeatherLevel;
		size += szDarkLevel;
		size += szLightLevel;
		size += szBYTE;
		size += szNPCType* m_nNPCs;
		size += szBYTE;
		size += szMonsterType* m_nMonsters;

		size += szBYTE;
		list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
		for(; itr != m_NPCInfos.end(); itr++)
		{
			NPCInfo* pInfo = *itr;
			size += pInfo->getSize();
		}
		// ���� ����
		size += szBYTE;
		// �����̾�
		size += szBYTE;
		// SMS
		size += szDWORD;

		if ( m_pNicknameInfo == NULL )
		{
			NicknameInfo noNick;
			noNick.setNicknameType( NicknameInfo::NICK_NONE );
			size += noNick.getSize();
		}
		else
		{
			size += m_pNicknameInfo->getSize();
		}

		size += szBYTE;

		// GuildUnion
		size += sizeof(uint);
		size += szBYTE;

		size += m_pBloodBibleSign->getSize();

		// �Ŀ�¯ ����Ʈ
		size += sizeof(uint);

		return size;
	}

	// get packet name
	string getPacketName()  { return "GCUpdateInfo"; }
	
	// get packet's debug string
	string toString() ;

//--------------------------------------------------
// methods
//--------------------------------------------------
public :

	// get/set PC info
	PCInfo* getPCInfo()  { return m_pPCInfo; }
	void setPCInfo(PCInfo* pPCInfo) throw(Error) { m_pPCInfo = pPCInfo; }

	// get/set Inventory Info
	InventoryInfo* getInventoryInfo()  { return m_pInventoryInfo; }
	void setInventoryInfo(InventoryInfo* pInventoryInfo) throw(Error) { m_pInventoryInfo = pInventoryInfo; }

	// get/set Gear Info
	GearInfo* getGearInfo()  { return m_pGearInfo; }
	void setGearInfo(GearInfo* pGearInfo) throw(Error) { m_pGearInfo = pGearInfo; }

	// get/set ExtraInfo
	ExtraInfo* getExtraInfo()  { return m_pExtraInfo; }
	void setExtraInfo(ExtraInfo* pExtraInfo) throw(Error) { m_pExtraInfo = pExtraInfo; }

	// get/set EffectInfo
	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw(Error) { m_pEffectInfo = pEffectInfo; }

	// get/set hasMotorcycle
	bool hasMotorcycle()  { return m_hasMotorcycle; }

	// get/set RideMotorcycleInfo
	RideMotorcycleInfo* getRideMotorcycleInfo()  { return m_pRideMotorcycleInfo; }
	void setRideMotorcycleInfo(RideMotorcycleInfo* pRideMotorcycleInfo) throw() {
		m_pRideMotorcycleInfo = pRideMotorcycleInfo;
		m_hasMotorcycle = true;
	}

	// get/set ZoneID
	ZoneID_t getZoneID()  { return m_ZoneID; }
	void setZoneID(const ZoneID_t & zoneID) throw() { m_ZoneID = zoneID; }

	// get / set ZoneX
	Coord_t getZoneX()  { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX) { m_ZoneX = ZoneX; }

	// get / set ZoneY
	Coord_t getZoneY()  { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY) { m_ZoneY = ZoneY; }

	// get/set GameTime
	GameTime getGameTime()  { return m_GameTime; }
	void setGameTime(const GameTime & gameTime) throw() { m_GameTime = gameTime; }

	// get/set weather
	Weather getWeather()  { return m_Weather; }
	void setWeather(Weather weather) throw() { m_Weather = weather; }

	// get/set weather level
	WeatherLevel_t getWeatherLevel()  { return m_WeatherLevel; }
	void setWeatherLevel(WeatherLevel_t weatherLevel) throw() { m_WeatherLevel = weatherLevel; }

	// get/set darklevel
	DarkLevel_t getDarkLevel()  { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	// get/set lightlevel
	LightLevel_t getLightLevel()  { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }

	// get/set # of NPC
	uint getNPCCount()  { return m_nNPCs; }
	void setNPCCount(uint n) throw(Error) { Assert(n <= maxNPCPerZone); m_nNPCs = n; }

	// get/set NPC type
	NPCType_t getNPCType(uint n)  { Assert(n < maxNPCPerZone); return m_NPCTypes[n]; }
	void setNPCType(uint n, NPCType_t npcType) throw() { Assert(n < maxNPCPerZone); m_NPCTypes[n] = npcType; }

	// get/set # of monster
	uint getMonsterCount()  { return m_nMonsters; }
	void setMonsterCount(uint n) throw(Error) { Assert(n <= maxMonsterPerZone); m_nMonsters = n; }

	// get/set Monster type
	MonsterType_t getMonsterType(uint n)  { Assert(n < maxMonsterPerZone); return m_MonsterTypes[n]; }
	void setMonsterType(uint n, MonsterType_t npcType) throw() { Assert(n < maxMonsterPerZone); m_MonsterTypes[n] = npcType; }

	// get/set npc info
	void addNPCInfo(NPCInfo* pInfo) { m_NPCInfos.push_back(pInfo);}
	NPCInfo* popNPCInfo(void) { if (m_NPCInfos.empty()) return NULL; NPCInfo* pInfo = m_NPCInfos.front(); m_NPCInfos.pop_front(); return pInfo; }

	// get/set ServerStat
	void setServerStat( BYTE ServerStat ) throw() { m_ServerStat = ServerStat; }
	BYTE getServerStat()  { return m_ServerStat; }

	// premium play ����
	void setPremiumZone() { m_fPremium |= FLAG_PREMIUM_ZONE; }
	void setPremiumPlay() { m_fPremium |= FLAG_PREMIUM_PLAY; }
	BYTE isPremiumZone() const { return m_fPremium & FLAG_PREMIUM_ZONE; }
	BYTE isPremiumPlay() const { return m_fPremium & FLAG_PREMIUM_PLAY; }

	DWORD	getSMSCharge() const { return m_SMSCharge; }
	void	setSMSCharge(DWORD charge) { m_SMSCharge = charge; }

	NicknameInfo* getNicknameInfo()  { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw(Error) { m_pNicknameInfo = pNicknameInfo; }

	BYTE	isNonPK() const { return m_NonPK; }
	void	setNonPK(BYTE pk) { m_NonPK = pk; }

		
	BYTE	getGuildUnionUserType() const { return m_GuildUnionUserType; }
	void	setGuildUnionUserType(BYTE type) { m_GuildUnionUserType= type; }

	uint	getGuildUnionID() const { return m_GuildUnionID; }
	void	setGuildUnionID(uint ID) { m_GuildUnionID = ID; }

	BloodBibleSignInfo*	getBloodBibleSignInfo() { return m_pBloodBibleSign; }
	void	setBloodBibleSignInfo( BloodBibleSignInfo* pInfo ) { m_pBloodBibleSign = pInfo; }

    // get / set PowerPoint
    int getPowerPoint() const { return m_PowerPoint; }
    void setPowerPoint( int powerpoint ) { m_PowerPoint = powerpoint; }

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

	//--------------------------------------------------------------------------------
	// Extra Information
	//--------------------------------------------------------------------------------
	EffectInfo* m_pEffectInfo;

	//--------------------------------------------------------------------------------
	// �������Ŭ�� �ֳ� ����.
	//--------------------------------------------------------------------------------
	bool m_hasMotorcycle;

	//--------------------------------------------------------------------------------
	// Motorcycle Information
	//--------------------------------------------------------------------------------
	RideMotorcycleInfo* m_pRideMotorcycleInfo;

	// inventory
	// quick item slot
	// gear

	// ����(PDA)
	// ���� ����Ʈ ����
	// ��������, �̺�Ʈ ����
	// ����.. ����� ó�� PDS�� �� �� �ٿ�����.. - -;

	//--------------------------------------------------------------------------------
	// Zone Information
	//--------------------------------------------------------------------------------
	// �� ���̵�
	ZoneID_t m_ZoneID;	

	// ��Ÿ�� ��ǥ�� �밭�� ��ġ
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

	// Game Time
	GameTime m_GameTime;
	
	// Weather(���� ����)
	Weather m_Weather;
	WeatherLevel_t m_WeatherLevel;

	// Dark/Light
	DarkLevel_t m_DarkLevel;
	LightLevel_t m_LightLevel;

	// ���� �����ϴ� NPC ��������Ʈ Ÿ���� ����, ��������Ʈ Ÿ�� �迭
	BYTE m_nNPCs;
	NPCType_t m_NPCTypes[ maxNPCPerZone ];

	// ���� �����ϴ� ���� ��������Ʈ Ÿ���� ����, ��������Ʈ Ÿ�� �迭
	BYTE m_nMonsters;
	MonsterType_t m_MonsterTypes[ maxMonsterPerZone ];

	// ���� ���� �����ϴ� NPC�鿡 ���� ����
	list<NPCInfo*> m_NPCInfos;

	// ���� ����
	BYTE m_ServerStat;

	// �����̾� ����
	BYTE m_fPremium;

	DWORD	m_SMSCharge;
	NicknameInfo*	m_pNicknameInfo;

	BYTE	m_NonPK;

	// ���ձ�� ����
	uint	m_GuildUnionID;
	BYTE	m_GuildUnionUserType;

	BloodBibleSignInfo* m_pBloodBibleSign;

    // �Ŀ�¯ ����Ʈ
    int    m_PowerPoint;
};


//--------------------------------------------------------------------------------
//
// class GCUpdateInfoFactory;
//
// Factory for GCUpdateInfo
//
//--------------------------------------------------------------------------------

class GCUpdateInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUpdateInfo(); }

	// get packet name
	string getPacketName()  { return "GCUpdateInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_UPDATE_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUpdateInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		PacketSize_t size = 0;

		size += szBYTE;
		size += PCSlayerInfo2::getMaxSize();
		//size += InventoryInfo::getMaxSize();
		size += GearInfo::getMaxSize();
		size += ExtraInfo::getMaxSize();
		size += EffectInfo::getMaxSize();
		size += szBYTE;
		size += RideMotorcycleInfo::getMaxSize();
		size += szZoneID;
		size += szCoord;
		size += szCoord;
		size += GameTime::getMaxSize();
		size += szWeather;
		size += szWeatherLevel;
		size += szDarkLevel;
		size += szLightLevel;
		size += szBYTE;
		size += szNPCType* maxNPCPerZone;
		size += szBYTE;
		size += szMonsterType* maxMonsterPerZone; 

		size += szBYTE;
		size += NPCInfo::getMaxSize()* 255;
		// ���� ����
		size += szBYTE;
		// �����̾�
		size += szBYTE;
		size += szDWORD;
		size += NicknameInfo::getMaxSize();

		size += szBYTE;

		// GuildUnion
		size += sizeof(uint);
		size += szBYTE;

		size += BloodBibleSignInfo::getMaxSize();

		// �Ŀ�¯ ����Ʈ
		size += sizeof(uint);

		return size;
	}

};



//--------------------------------------------------------------------------------
//
// class GCUpdateInfoHandler;
//
//--------------------------------------------------------------------------------

class GCUpdateInfoHandler {

public :

	// execute packet's handler
	static void execute(GCUpdateInfo* pPacket, Player* pPlayer) ;

};

#endif
