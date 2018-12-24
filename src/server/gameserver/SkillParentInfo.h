//----------------------------------------------------------------------
//
// Filename    : SkillParentInfo.h
// Written By  : Elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SKILL_PARENT_INFO_H__
#define __SKILL_PARENT_INFO_H__

#include "Types.h"
#include "Exception.h"

//----------------------------------------------------------------------
//
// Class SkillParentInfo;
//
// �� ��ų�� �θ� �������� �� �� �ִ� �޼ҵ���� ������ �ִ� Ŭ�����̴�
//
//----------------------------------------------------------------------

class SkillParentInfo {

//--------------------------------------------------
// constructor/destructor
//--------------------------------------------------
public:

	// constructor
	SkillParentInfo(SkillType_t SkillType) throw();

	// destructor
	~SkillParentInfo() throw();
	
	void load() throw(SQLQueryException, Error) {}
	void save() const throw(SQLQueryException, Error) {}

//--------------------------------------------------
// AI specific methods
//--------------------------------------------------
public:

	// SkillParentInfoType �� ����ؼ�, SkillParentInfoInfo �κ��� �ʱ�ȭ�ϱ�
	void init() throw(Error);

	// enemy specific methods
	void addParents(SkillType_t SkillType) throw(DuplicatedException, Error) {
		m_Parents.push_back(SkillType);
	}
	void deleteParents(SkillType_t SkillType) throw(NoSuchElementException, Error);

	SkillType_t getParents(SkillType_t SkillType) const throw(NoSuchElementException, Error);


	bool hasParent(SkillType_t ParentSkillType) throw(NoSuchElementException, Error);
	bool hasParent() const throw(NoSuchElementException, Error) { return m_Parents.size() > 0; }

//--------------------------------------------------
// get monster-class-level attributes
//--------------------------------------------------
public:

	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }
	SkillType_t getSkillType() const throw() { return m_SkillType; }

	string toString() const throw();

//--------------------------------------------------
// data members
//--------------------------------------------------
private:

	SkillType_t m_SkillType;

	list< SkillType_t > m_Parents;

};



//--------------------------------------------------------------------
//
// Class SkillParentInfoManager
//
//--------------------------------------------------------------------
class SkillParentInfoManager {

public:

	// constructor
	SkillParentInfoManager() throw();

	// destructor
	~SkillParentInfoManager() throw();

	// initialize Manager
	void init() throw(Error);

	// void load() throw();
	// Loading from Database to ParentInfoClass
	void load() throw(Error);
	
	// Save to DB
	void save() throw(Error);

	// get SkillParentInfo
	SkillParentInfo* getSkillParentInfo(SkillType_t SkillType) const throw(NoSuchElementException, OutOfBoundException, Error);

	// add SkillParentInfo
	void addSkillParentInfo(SkillParentInfo* pSkillParentInfo) throw(DuplicatedException, Error);

	// get SkillCount
	uint getSkillCount() const throw() { return m_SkillCount; }

	// toString for Debug
	string toString() const throw();

private:

	uint m_SkillCount;

	SkillParentInfo ** m_SkillParentInfoList;
		
};

// Global Variable Definition
extern SkillParentInfoManager* g_pSkillParentInfoManager;

#endif	// __SKILL_PARENT_INFO_MANAGER_H__
