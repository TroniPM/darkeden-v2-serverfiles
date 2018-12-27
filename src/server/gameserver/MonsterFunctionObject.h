//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterFunctionObject.h
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_FUNCTION_OBJECT_H__
#define __MONSTER_FUNCTION_OBJECT_H__

#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"

//////////////////////////////////////////////////////////////////////////////
//
// class StrongerSlayer, WeakerSlayer, StrongerVampire, WeakerVampire;
//
// �� Ŭ��������, ���Ϳ��� enemy �� �߰��ϴ� Monster::addEnemy() �޽��
// ���� ���� ũ��ó �Ŵ������� �� enemy �� ������ ���� ��ġ�� ã�Ƴ� ��
// ����ϴ� function object �μ� ���ȴ�.
//
// ex> ���� ������ AttackOrder�� ATTACK_WEAKEST ��� ��������. �� 
// ������ m_Enemies �� ���� ������� ���ĵǾ� ���� ���̴�. �ϴ� 
// ������ ���忡�� �����̾� ���͸� �����ϱ� ������, �� ���͵���
// �����̾�� �����̾�� ������ ���� �ް� �Ǹ�, Ư�� ��Ȳ������
// �����̾ ���� �����ϰ� �ȴ�. ����, �� m_Enemies �� ���ʿ�
// �����̾���� OID�� ����Ǿ� ������, ���ʿ� �����̾���� OID��
// ����Ǿ� �ִ�. 
//
// ���� SkillDomainLevelSum == 5000 �� �����̾ �� ���͸� �����ؼ�
// ������ �����ɷ��� �ϴ� ������ �Ǿ��ٰ� ġ��. �� �����̾ ������
// ��ġ�� �����ϱ� ���ؼ���, ���� ���� �����̾��� ��ġ�� �˾Ƴ��� �Ѵ�.
// (�����̾ ���ٸ� ������ �����̾��� ��ġ�� �˾Ƴ��� �Ѵ�.)
//
// �̷� ���, STL�� find_if �˰����� ����ϸ� �ڵ尡 ������ ���µ�,
// ������ �Ķ���ͷ� WeakerSlayer(5000) �� �������ָ� �˾Ƽ� ã�� �ȴ�.
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// class StrongerSlayer;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, operator()�� �����̾ �ƴϰų� �ڽź��� ���� �����̾��� ���
// true�� �����ؾ� �Ѵ�. �׷���, �� ���� ��忡 �߰��ϸ� ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class StrongerSlayer 
{
public:
	StrongerSlayer (Zone* pZone , SkillLevel_t skillLevelSum) 
	{
		m_pZone = pZone;
		m_SkillDomainLevelSum = skillLevelSum;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isSlayer())
			return true;

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		return pSlayer->getSkillDomainLevelSum() > m_SkillDomainLevelSum;
	}

private:
	Zone*        m_pZone;
	SkillLevel_t m_SkillDomainLevelSum;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerSlayer;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, �����̾ �ƴϰų� �ڽź��� ���� �����̾��� ���
// true�� �����ؾ� �Ѵ�. �׷���, �� ���� ��忡 �߰��ϸ�
// ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class WeakerSlayer 
{
public :

	// constructor
	WeakerSlayer (Zone* pZone , SkillLevel_t skillLevelSum) 
	{
		m_pZone = pZone;
		m_SkillDomainLevelSum = skillLevelSum;
	}

	bool operator () (ObjectID_t objectID)
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isSlayer())
			return true;

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		return pSlayer->getSkillDomainLevelSum() < m_SkillDomainLevelSum;
	}

private:
	Zone*        m_pZone;
	SkillLevel_t m_SkillDomainLevelSum;

};


//////////////////////////////////////////////////////////////////////////////
// class StrongerVampire;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, �ڽź��� ���� �����̾��� ��쿡�� true�� �����ؾ� �Ѵ�. 
// �׷���, �� ���� ��忡 �߰��ϸ� ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class StrongerVampire 
{
public:
	StrongerVampire (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isVampire())
			return false;

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		return pVampire->getLevel() > m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerVampire;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, �ڽź��� ���� �����̾��� ��쿡�� true�� �����ؾ� �Ѵ�. 
// �׷���, �� ���� ��忡 �߰��ϸ� ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class WeakerVampire 
{
public:
	WeakerVampire (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isVampire())
			return false;

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		return pVampire->getLevel() < m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;

};

class StrongerOusters 
{
public:
	StrongerOusters (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isOusters())
			return false;

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		return pOusters->getLevel() > m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerOusters;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, �ڽź��� ���� �����̾��� ��쿡�� true�� �����ؾ� �Ѵ�. 
// �׷���, �� ���� ��忡 �߰��ϸ� ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class WeakerOusters 
{
public:
	WeakerOusters (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isOusters())
			return false;

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		return pOusters->getLevel() < m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;

};

//////////////////////////////////////////////////////////////////////////////
// class StrongerMonster;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, �ڽź��� ���� �����̾��� ��쿡�� true�� �����ؾ� �Ѵ�. 
// �׷���, �� ���� ��忡 �߰��ϸ� ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class StrongerMonster 
{
public:
	StrongerMonster (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isMonster())
			return false;

		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		return pMonster->getLevel() > m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;
};


//////////////////////////////////////////////////////////////////////////////
// class WeakerMonster;
// enemy list �� ���� ���� ������ ���ĵǾ� �ִ�.
// ����, �ڽź��� ���� �����̾��� ��쿡�� true�� �����ؾ� �Ѵ�. 
// �׷���, �� ���� ��忡 �߰��ϸ� ���� ������ �����ϰ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class WeakerMonster 
{
public:
	WeakerMonster (Zone* pZone , Level_t level) 
	{
		m_pZone = pZone;
		m_Level = level;
	}

	bool operator () (ObjectID_t objectID) 
	{
		Assert(m_pZone != NULL);	// by sigi

		Creature* pCreature = NULL;

		try
		{
			pCreature = m_pZone->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
			//cout << nsee.toString() << endl;
			pCreature = NULL;
		}

		if (pCreature == NULL) return false; // by sigi

		if (! pCreature->isMonster())
			return false;

		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		return pMonster->getLevel() < m_Level;
	}

private:
	Zone*   m_pZone;
	Level_t m_Level;

};



#endif
