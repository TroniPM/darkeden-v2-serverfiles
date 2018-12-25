//////////////////////////////////////////////////////////////////////////////
// Filename    : Party.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PARTY_H__
#define __PARTY_H__

#include "Creature.h"
#include "Mutex.h"
#include "ModifyInfo.h"
#include "Mutex.h"
#include <hash_map>
#include <list>

// ��Ƽ�� �ִ� ũ��
const int PARTY_MAX_SIZE = 6;

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Packet;
class GCPartyJoined;
class Creature;
class MonsterCorpse;

//////////////////////////////////////////////////////////////////////////////
// class PartyInviteInfo
//////////////////////////////////////////////////////////////////////////////

class PartyInviteInfo
{
public:
	PartyInviteInfo() { m_HostName = ""; m_GuestName = ""; }
	~PartyInviteInfo() {}

public:
	string getHostName(void) const { return m_HostName; }
	void setHostName(const string& name) { m_HostName = name; }

	string getGuestName(void) const { return m_GuestName; }
	void setGuestName(const string& name) { m_GuestName = name; }

public:
	string toString(void) ;

protected:
	string m_HostName;
	string m_GuestName;
};


//////////////////////////////////////////////////////////////////////////////
// class PartyInviteInfoManager
//////////////////////////////////////////////////////////////////////////////

class PartyInviteInfoManager
{
public:
	PartyInviteInfoManager() throw();
	~PartyInviteInfoManager() throw();

public:
	bool hasInviteInfo(const string& HostName) throw (Error);
	bool canInvite(Creature* pHost, Creature* pGuest) throw (Error);
	bool isInviting(Creature* pHost, Creature* pGuest) throw (Error);
	void initInviteInfo(Creature* pHost, Creature* pGuest) throw (Error);
	void cancelInvite(Creature* pHost, Creature* pGuest) throw (Error);
	void cancelInvite(Creature* pCreature) throw (Error);

public:
	bool addInviteInfo(PartyInviteInfo* pInfo) throw (Error);
	void deleteInviteInfo(const string& HostName) throw (NoSuchElementException, Error);
	PartyInviteInfo* getInviteInfo(const string& HostName) throw (NoSuchElementException, Error);

protected:
	hash_map<string, PartyInviteInfo*> m_InfoMap;
	Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// class Party
//////////////////////////////////////////////////////////////////////////////

class Party
{
public:
	Party(Creature::CreatureClass CClass) throw();
	~Party() throw();

public:
	int getID(void) const { return m_ID; }
	void setID(int ID) { m_ID = ID; }

	Creature::CreatureClass getCreatureClass(void) const { return m_CreatureClass; }

public:
	Creature* getMember(const string& name) const throw (NoSuchElementException, Error);
	void addMember(Creature* pCreature) throw (DuplicatedException, Error);
	void deleteMember(const string& name) throw (NoSuchElementException, Error);
	bool hasMember(const string& name) ;

	// �۷ι� ��Ƽ �Ŵ��������� ����Ѵ�.
	// ��Ƽ�� ��ü�ϱ� ���� ��Ƽ ������� ��Ƽ ID�� 0���� �����,
	// ���� ��Ƽ �Ŵ������� �ش� ID�� ���� ��Ƽ�� �����Ѵ�.
	void destroyParty(void) throw();

public:
	// ��Ƽ ����鿡�� ��Ŷ�� ������.
	void broadcastPacket(Packet* pPacket, Creature* pOwner=NULL) throw (ProtocolException, Error);

	// ���ο� ��Ƽ���� �߰��Ǿ��� �� ��Ƽ���鿡�� ���ư���
	// GCPartyJoined ��Ŷ�� �����Ѵ�.
	void makeGCPartyJoined(GCPartyJoined* pGCPartyJoined) ;

public:
	int getSize(void) ;
	hash_map<string, Creature*> getMemberMap(void) throw();

	// ������ �Ÿ�(8Ÿ��) ���� �ִ� ������� ���ڸ� �����Ѵ�.
	int getAdjacentMemberSize(Creature* pLeader) ;
	int getAdjacentMemberSize_LOCKED(Creature* pLeader) ;

	// ����ġ�� ��Ǯ���� ������.
	int shareAttrExp(Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) ;
	int shareVampireExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) ;
	int shareOustersExp(Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) ;
	int shareAttackBloodBurst(Creature* pLeader, Creature* pTargetCreature, int amount) ;
	int shareDefenseBloodBurst(Creature* pLeader, Creature* pTargetCreature, int amount) ;
	// ���� ���� ���´�. �δ� �Ǵ� ��ȯ ���� óġ��.
	int shareGold(Creature* pLeader, int amount) ;

public:
	void shareRevealer(Creature* pCaster, int Duration) throw (Error);
	void shareDetectHidden(Creature* pCaster, int Duration) throw (Error);
	void shareDetectInvisibility(Creature* pCaster, int Duration) throw (Error);
	void shareExpansion(Creature* pCaster, int Duration, int percent) throw (Error);
	void shareActivation(Creature* pCaster, int Duration) throw (Error);
	void shareGnomesWhisper(Creature* pCaster, int Duration, int SkillLevel) throw (Error);
	void shareHolyArmor(Creature* pCaster, int DefBonus, int SkillLevel) throw (Error);
	void shareHolyArmor2(Creature* pCaster, int DefBonus, int SkillLevel) throw (Error);
	bool shareWaterElementalHeal(Creature* pCaster, int HealPoint) throw (Error);
	void shareGDRLairEnter(Creature* pLeader) throw(Error);

	void shareRankExp(Creature* pLeader, int amount) throw ();
	void shareAdvancementExp(Creature* pLeader, int amount) throw();

	void dissectCorpse(Creature* pDissecter, MonsterCorpse* pCorpse) throw(Error);
	void eventPartyCrash() throw(Error);
	
	// �ν���Ʈ ������ �����Ѵ�.
	void shareInstant(Creature* pLeader, int ZoneID, int X, int Y) throw(Error);

public:
	bool isFamilyPay() const { return m_bFamilyPay; }
	void refreshFamilyPay();

public:
	string toString(void) ;

protected:
	int                          m_ID;            // ��Ƽ ID
	Creature::CreatureClass      m_CreatureClass; // ��Ƽ�� ����
	hash_map<string, Creature*>  m_MemberMap;     // ��Ƽ ���
	mutable Mutex                m_Mutex;         // ���ο��� ���� ��
	bool						 m_bFamilyPay;	  // �йи� ����� ���� ��Ƽ�ΰ�?
};


//////////////////////////////////////////////////////////////////////////////
// class PartyManager
//////////////////////////////////////////////////////////////////////////////

class PartyManager
{
public:
	PartyManager() throw();
	virtual ~PartyManager() throw();

public:
	virtual bool createParty(int ID, Creature::CreatureClass) throw (DuplicatedException, Error);
	virtual bool addPartyMember(int ID, Creature* pCreature) throw (NoSuchElementException, DuplicatedException, Error);
	virtual bool deletePartyMember(int ID, Creature* pCreature) throw (NoSuchElementException, Error);
	virtual Party* getParty(int ID) throw (NoSuchElementException, Error);

public:
	virtual string toString(void)  = 0;

protected:
	hash_map<int, Party*> m_PartyMap; // ��Ƽ ����
	mutable Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// class LocalPartyManager
//////////////////////////////////////////////////////////////////////////////

class LocalPartyManager : public PartyManager
{
public:
	LocalPartyManager() throw();
	virtual ~LocalPartyManager() throw();

public:
	void heartbeat(void) throw (Error);
	int getAdjacentMemberSize(int PartyID, Creature* pLeader) ;
	int shareAttrExp(int PartyID, Creature* pLeader, int amount, int STRMultiplier, int DEXMultiplier, int INTMultiplier, ModifyInfo& LeaderModifyInfo) ;
	int shareVampireExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) ;
	int shareOustersExp(int PartyID, Creature* pLeader, int amount, ModifyInfo& LeaderModifyInfo) ;
	int shareAttackBloodBurst(int PartyID, Creature* pLeader, Creature* pTargetCreature, int amount) ;
	int shareDefenseBloodBurst(int PartyID, Creature* pLeader, Creature* pTargetCreature, int amount) ;
	int shareGold(int PartyID, Creature* pLeader, int amount) ; // ���� ����������.
	void shareRevealer(int PartyID, Creature* pCaster, int Duration) throw (Error);
	void shareDetectHidden(int PartyID, Creature* pCaster, int Duration) throw (Error);
	void shareDetectInvisibility(int PartyID, Creature* pCaster, int Duration) throw (Error);
	void shareExpansion(int PartyID, Creature* pCaster, int Duration, int Percent) throw (Error);
	void shareActivation(int PartyID, Creature* pCaster, int Duration) throw (Error);
	void shareGnomesWhisper(int PartyID, Creature* pCaster, int Duration, int SkillLevel) throw (Error);
	void shareHolyArmor(int PartyID, Creature* pCaster, int DefBonus, int SkillLevel) throw (Error);
	void shareHolyArmor2(int PartyID, Creature* pCaster, int DefBonus, int SkillLevel) throw (Error);
	bool shareWaterElementalHeal(int PartyID, Creature* pCaster, int HealPoint) throw (Error);
	void shareGDRLairEnter(int PartyID, Creature* pLeader) throw(Error);
	
	int shareRankExp(int PartyID, Creature* pLeader, int amount) ;
	int shareAdvancementExp(int PartyID, Creature* pLeader, int amount) ;

	// �ν���Ʈ ������ �����Ѵ�.
	void shareInstant(int PartyID, Creature* pLeader, int ZoneID, int X, int Y) throw(Error);

public:
	virtual string toString(void) ;
};


//////////////////////////////////////////////////////////////////////////////
// class GlobalPartyManager
//////////////////////////////////////////////////////////////////////////////

class GlobalPartyManager : public PartyManager
{
public:
	GlobalPartyManager() throw();
	virtual ~GlobalPartyManager() throw();

public:
	bool canAddMember(int ID) throw (NoSuchElementException, Error);
	virtual bool addPartyMember(int ID, Creature* pCreature) throw (NoSuchElementException, DuplicatedException, Error);
	virtual bool deletePartyMember(int ID, Creature* pCreature) throw (NoSuchElementException, Error);
	virtual bool expelPartyMember(int ID, Creature* pExpeller, const string& ExpelleeName) throw (NoSuchElementException, Error);

	int registerParty(void) throw (Error);

	void refreshFamilyPay(int ID);

public:
	virtual string toString(void) ;

protected:
	int m_PartyIDRegistry; // ��Ƽ ID ������
};

extern GlobalPartyManager* g_pGlobalPartyManager;


//////////////////////////////////////////////////////////////////////////////
// ���Ǹ� ���� ���� �Լ���...
//////////////////////////////////////////////////////////////////////////////
void deleteAllPartyInfo(Creature* pCreature) throw();


#endif
