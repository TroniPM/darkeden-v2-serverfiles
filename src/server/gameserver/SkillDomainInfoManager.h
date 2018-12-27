//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillDomainInfoManager.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOMAIN_INFO_MANAGER_H__
#define __SKILL_DOMAIN_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class DomainInfo
//////////////////////////////////////////////////////////////////////////////

class DomainInfo 
{
public:
	DomainInfo() ;
	~DomainInfo() ;

public:
	SkillDomainType_t getType()  { return m_Type; }
	void setType(SkillDomainType_t type)  { m_Type = type; }

	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t level)  { m_Level = level; }

	uint getGoalExp()  { return m_GoalExp; }
	void setGoalExp(Exp_t exp)  { m_GoalExp = exp ; }

	uint getAccumExp()  { return m_AccumExp; }
	void setAccumExp(Exp_t exp)  { m_AccumExp = exp ; }

	ItemType_t getBestItemType()  { return m_BestItemType; }
	void setBestItemType(ItemType_t it)  { m_BestItemType = it; }
	
	string toString() ;

private:

	// 스킬 도메인의 타입
	SkillDomainType_t m_Type;

	// 단계(스킬 트리에서 이 기술의 depth)
	Level_t m_Level;

	// 목표 경험치
	Exp_t m_GoalExp;

	// 누적 경험치
	Exp_t m_AccumExp;

	// 적절한 무기 단계
	ItemType_t m_BestItemType;
};

//--------------------------------------------------------------------
//
// Class DomainInfoManager
//
//--------------------------------------------------------------------
/*
class DomainInfoManager {

public:

	// constructor
	DomainInfoManager() ;

	// destructor
	~DomainInfoManager() ;

	// initialize manager
	void init();

	// get sub info class manager
	DomainInfoManager* getInfoManager(Domain DomainType) ;

	// get item info
	SkillDomainInfo* getSkillDomainInfo(Level_t Level) ;

	uint getDomainCount() ;

	// toString for debug
	string toString() ;

private:

	DomainInfo ** m_DomainInfoLists;

};
*/

//////////////////////////////////////////////////////////////////////////////
// Class SkillDomainInfoManager
//////////////////////////////////////////////////////////////////////////////

class SkillDomainInfoManager 
{
public:
	SkillDomainInfoManager() ;
	~SkillDomainInfoManager() ;

public:
	// initialize manager
	void init();

	// get item info
	DomainInfo* getDomainInfo(SkillDomain DomainType, Level_t Level) ;

	// addDomainInfo
	void addDomainInfo(DomainInfo* pDomainInfo) ;

	// toString for debug
	string toString() ;

private:
	DomainInfo ** m_DomainInfoLists[SKILL_DOMAIN_MAX];
};

extern SkillDomainInfoManager* g_pSkillDomainInfoManager;

#endif
