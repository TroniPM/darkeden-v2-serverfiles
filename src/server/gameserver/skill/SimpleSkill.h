//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleSkill.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLESKILL__
#define __SIMPLESKILL__

#include "SkillHandler.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class TILE_MASK
{
public:
	TILE_MASK()
	{
		x       = 0;
		y       = 0;
		penalty = 100;
	}
	TILE_MASK(int _x, int _y, int _penalty=100)
	{
		x       = _x;
		y       = _y;
		penalty = _penalty;
	}

public:
	int x;        // �߽��� �Ǵ� ��ǥ�κ����� x offset
	int y;        // �߽��� �Ǵ� ��ǥ�κ����� y offset
	int penalty;  // ������ ���� ���� ���Ƽ
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class SIMPLE_SKILL_INPUT
{
public:
	SIMPLE_SKILL_INPUT()
	{
		SkillType     = SKILL_MAX;
		SkillDamage   = 0;
		Delay         = 0;
		ItemClass     = Item::ITEM_CLASS_MAX;
		STRMultiplier = 0;
		DEXMultiplier = 0;
		INTMultiplier = 0;
		Level         = 0;
		bMagicHitRoll = false;
		bMagicDamage  = false;
		bAdd          = false;
		bExpForTotalDamage = false;
		Grade		  = 0;
	}

	~SIMPLE_SKILL_INPUT()
	{
		MaskList.clear();
	}

public:
	void addMask(const TILE_MASK& mask)
	{
		MaskList.push_back(mask);
	}
	void addMask(int x, int y, int penalty)
	{
		MaskList.push_back(TILE_MASK(x, y, penalty));
	}

public:
	SkillType_t     SkillType;     // ��ų Ÿ��
	Damage_t        SkillDamage;   // ��ų�� ȿ��ġ
	Turn_t          Delay;         // ��ų�� ������
	Item::ItemClass ItemClass;     // ����� ����ϱ� ���� �ʿ��� ������
	int             STRMultiplier; // �����̾� �ɷ�ġ ����ġ ����ġ
	int             DEXMultiplier; // �����̾� �ɷ�ġ ����ġ ����ġ
	int             INTMultiplier; // �����̾� �ɷ�ġ ����ġ ����ġ
	int             Level;         // ���� ���� �������� ���̴� ����
	bool            bMagicHitRoll; // ���� ���߷� �����ΰ�, �Ϲ� ���� �����ΰ�...
	bool            bMagicDamage;  // ��ų�� �������� ���� �������ΰ�...
	bool            bAdd;          // SkillDamage�� ���ؾ� �ϳ�, �׳� ��� �ϳ�...
	list<TILE_MASK> MaskList;      // Ÿ�� ��ų�� ���, ����ũ ����Ʈ
	bool			bExpForTotalDamage;	// ��ü damage�� ���ؼ� ����ġ�� �÷��ش�.
	BYTE			Grade;		   // ��ų ���
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class SIMPLE_SKILL_OUTPUT
{
public:
	SIMPLE_SKILL_OUTPUT()
	{
		bSuccess = false;
		pTargetCreature = NULL;
	}

public:
	bool      bSuccess;
	Creature* pTargetCreature;
	list<Creature*> targetCreatures;
};

#endif
