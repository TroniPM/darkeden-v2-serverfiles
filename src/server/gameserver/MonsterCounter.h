//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterCounter.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_COUNTER_H__
#define __MONSTER_COUNTER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class MonsterCounter;
//////////////////////////////////////////////////////////////////////////////

class MonsterCounter 
{
public:
	MonsterCounter(SpriteType_t spriteType = 0, WORD maxMonsters = 0, WORD currentMonsters = 0) throw();

public:
	SpriteType_t getSpriteType() const throw() { return m_SpriteType; }
	void setSpriteType(SpriteType_t monsterType) throw() { m_SpriteType = monsterType; }

	WORD getMaxMonsters() const throw() { return m_MaxMonsters; }
	void setMaxMonsters(WORD n) throw() { m_MaxMonsters = n; }

	WORD getCurrentMonsters() const throw() { return m_CurrentMonsters; }
	void setCurrentMonsters(WORD n) throw() { m_CurrentMonsters = n; }

	void addMonster() throw(Error);
	void addMonster(WORD Count) throw();
	void deleteMonster() throw(Error);

	string toString() const throw();

private:
	SpriteType_t m_SpriteType;      // ��������Ʈ Ÿ��
	WORD         m_MaxMonsters;     // ������ �ִ� ������
	WORD         m_CurrentMonsters; // ������ ���� ������

	static DWORD	s_MonsterCounter;
};

#endif
