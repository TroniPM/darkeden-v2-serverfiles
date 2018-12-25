#ifndef __CASTLE_INFO_MANAGER_H__
#define __CASTLE_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "PlayerCreature.h"

class Zone;
class NPC;

class CastleInfo
{
public:
	enum ResurrectPriority
	{
		CASTLE_RESURRECT_PRIORITY_FIRST,
		CASTLE_RESURRECT_PRIORITY_SECOND,
		CASTLE_RESURRECT_PRIORITY_THIRD,

		CASTLE_RESURRECT_PRIORITY_MAX
	};

public:
	CastleInfo();
	~CastleInfo();

public:
	ZoneID_t getZoneID() const { return m_ZoneID; }
	void	 setZoneID(const ZoneID_t zoneID) { m_ZoneID = zoneID; }

	ShrineID_t getShrineID() const { return m_ShrineID; }
	void   setShrineID( const ShrineID_t id ) { m_ShrineID = id; }

	GuildID_t getGuildID() const { return m_GuildID; }
	void	  setGuildID( const GuildID_t guildID ) { m_GuildID = guildID; }

	const string& getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	int	getItemTaxRatio() const { return m_ItemTaxRatio; }
	void setItemTaxRatio( const int itemTaxRatio ) { m_ItemTaxRatio = itemTaxRatio; }

	Gold_t getEntranceFee() const { return m_EntranceFee; }
	void   setEntranceFee( const Gold_t entranceFee ) { m_EntranceFee = entranceFee; }

	Gold_t getTaxBalance() const { return m_TaxBalance; }
	void   setTaxBalance( const Gold_t balance ) { m_TaxBalance = balance; }

	Gold_t increaseTaxBalance( Gold_t tax );
	Gold_t decreaseTaxBalance( Gold_t tax );

	Gold_t increaseTaxBalanceEx( Gold_t tax );
	Gold_t decreaseTaxBalanceEx( Gold_t tax );

	const list<OptionType_t>& getOptionTypeList()  { return m_BonusOptionList; }
	void setOptionTypeList( const string& options ) throw();

	bool isCastleZone(ZoneID_t targetZoneID) ;
	const list<ZoneID_t>& getZoneIDList()  { return m_CastleZoneIDList; }
	void setZoneIDList( const string& zoneIDs ) throw();

	Race_t getRace() const { return m_Race; }
	void   setRace( Race_t race ) { m_Race = race; }

	void setResurrectPosition( ResurrectPriority resurrectPriority, const ZONE_COORD& zoneCoord );
	void getResurrectPosition( ResurrectPriority resurrectPriority, ZONE_COORD& zoneCoord );

	bool isCommon() const { return ( m_GuildID == SlayerCommon || m_GuildID == VampireCommon || m_GuildID == OustersCommon ); }

	void	broadcast(Packet* pPacket) ;

	string toString() ;

private:
	ZoneID_t 	m_ZoneID;		// ��ID
	ShrineID_t 	m_ShrineID;		// �� ��¡�� ShrineID
	GuildID_t 	m_GuildID;	// ���� ��� ID
	string 		m_Name;			// �� �̸�
	int 		m_ItemTaxRatio;		// ������ �� �� ���� (%)
	Gold_t 		m_EntranceFee;	// �����
	Gold_t 		m_TaxBalance;	// ���� �׿��ִ°�
	Race_t 		m_Race;			// ��� ������ ���ΰ�

	list<OptionType_t> 	m_BonusOptionList;	// ���� ���ʽ�
	list<ZoneID_t> 		m_CastleZoneIDList;

	ZONE_COORD m_ResurrectPosition[ CASTLE_RESURRECT_PRIORITY_MAX ];		// ���� ��Ȱ ��ġ
};

class CastleInfoManager
{
public:
	CastleInfoManager();
	~CastleInfoManager();
public:
	void init();
	void load();
	void save(ZoneID_t zoneID);

	void addCastleInfo( CastleInfo* pCastleInfo );
	void deleteCastleInfo( ZoneID_t zoneID );
	CastleInfo* getCastleInfo( ZoneID_t zoneID ) ;
	int  size() const { return m_CastleInfos.size(); }

	bool modifyCastleOwner(ZoneID_t zoneID, PlayerCreature* pPC );
	bool modifyCastleOwner(ZoneID_t zoneID, Race_t race, GuildID_t guildID );
	bool tinysave( ZoneID_t zoneID, const string& query );
	bool increaseTaxBalance( ZoneID_t zoneID, Gold_t tax );
	bool decreaseTaxBalance( ZoneID_t zoneID, Gold_t tax );

	bool setItemTaxRatio( Zone* pZone, int itemTaxRatio );
	const hash_map<ZoneID_t, CastleInfo*>& getCastleInfos() const 	{ return m_CastleInfos; }

	int getItemTaxRatio( const PlayerCreature* pPC, const NPC* pNPC = NULL ) ;
	Gold_t getEntranceFee( ZoneID_t zoneID, PlayerCreature* pPC ) const  throw(Error);

	bool isCastleMember( PlayerCreature* pPC ) ;
	bool isCastleMember( ZoneID_t zoneID, PlayerCreature* pPC ) ;
	bool isPossibleEnter( ZoneID_t zoneID, PlayerCreature* pPC ) ;
	bool canPortalActivate( ZoneID_t zoneID, PlayerCreature* pPC ) ;
	bool hasOtherBloodBible( ZoneID_t zoneID, PlayerCreature* pPC ) ;

	CastleInfo* getGuildCastleInfo( GuildID_t guildID ) ;
	list<CastleInfo*> getGuildCastleInfos( GuildID_t guildID ) ;

	bool getResurrectPosition( PlayerCreature* pPC, ZONE_COORD& zoneCoord );

	//----------------------------------------------------------------------
	// CastleZoneID ����
	//----------------------------------------------------------------------
	bool 		isCastleZone(ZoneID_t castleZoneID, ZoneID_t targetZoneID) ;
	bool		isCastleZone(ZoneID_t zoneID) const;
	void		clearCastleZoneIDs();
	bool	 	getCastleZoneID(ZoneID_t zoneID, ZoneID_t &castleZoneID) ;
	void 		setCastleZoneID(ZoneID_t zoneID, ZoneID_t castleZoneID);
	bool		isSameCastleZone(ZoneID_t zoneID1, ZoneID_t zoneID2) ;

	//----------------------------------------------------------------------
	// ��� ���� ���� �Ǵ� �͵�
	//----------------------------------------------------------------------
	void	releaseAllSafeZone();
	void    resetAllSafeZone();

	void	deleteAllNPCs();
	void	loadAllNPCs();

	void	transportAllOtherRace();

	ZoneID_t 	getCastleZoneID(ShrineID_t shrineID) ;
	void		broadcastShrinePacket(ShrineID_t shrineID, Packet* pPacket) ;

	SkillType_t getCastleSkillType( ZoneID_t zoneID, GuildID_t guildID ) ;

	string toString() ;

private:
	hash_map<ZoneID_t, CastleInfo*> m_CastleInfos;
	hash_map<ZoneID_t, ZoneID_t> 	m_CastleZoneIDs;
};

extern CastleInfoManager* g_pCastleInfoManager;

#endif // __CASTlE_INFO_MANAGER_H__
