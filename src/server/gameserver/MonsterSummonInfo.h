//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterSummonInfo.h
// Written By  : ��
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTER_SUMMON_INFO_H__
#define __MONSTER_SUMMON_INFO_H__

#include "Types.h"
#include "MonsterInfoTypes.h"
#include <list>
#include <vector>

struct MonsterCollection;

// ��ȯ�ɶ��� ����
struct SUMMON_INFO
{
	enum ClanType
	{
		CLAN_TYPE_DEFAULT,			// default = 1
		CLAN_TYPE_RANDOM_EACH,		// �̹��� �����Ǵ� �ֵ� ���� �ٸ���
		CLAN_TYPE_RANDOM_GROUP,		// �̹��� �����Ǵ� �ֵ� ���� ����
		CLAN_TYPE_GROUP,			// �̹��� �����Ǵ� �ֵ� ���� ����. clanID����
	};

	SUMMON_INFO()
	{
		scanEnemy = false;
		canScanEnemy = false;
		clanType = CLAN_TYPE_DEFAULT;
		clanID = 0;
		hasItem = true;
		regenType = REGENTYPE_MAX;
		initHPPercent = 0;
	}

	bool 		canScanEnemy;		// ��(����? -_-;)�� ������ scan�ϴ°�?
	ClanType 	clanType;
	int 	 	clanID;
	bool	 	hasItem;			// ��ȯ�� ���Ͱ� �������� �����°�?
	RegenType   regenType;
	bool 		scanEnemy;			// �����ɶ� ��(����? -_-;)��  scan�ϴ°�?
	int 		initHPPercent;
};

// ��ȯ�ɶ��� ����: ���������� �Ѳ����� ��ȯ
struct SUMMON_INFO2 : public SUMMON_INFO
{
	ZoneCoord_t   		X;
	ZoneCoord_t   		Y; 
	MonsterCollection*	pMonsters;
};

// ���� �� ����
struct MonsterCollectionInfo
{
	SpriteType_t	SpriteType;
	MonsterType_t	MonsterType;
	int             Num;

	void parseString(const string& infoString);

	string toString() const;
};

// ���� ���� ����
struct MonsterCollection
{
	list<MonsterCollectionInfo> Infos;

	void parseString(const string& collectionString);

	string toString() const;
};

// ��ȯ �ܰ�
struct MonsterSummonStep
{
	vector<MonsterCollection>  Collections;

	const MonsterCollection* getRandomMonsterCollection() const;

	void parseString(const string& summonStepsString);

	string toString() const;
};

// ��ȯ ����
struct MonsterSummonInfo
{
	vector<MonsterSummonStep>  Steps;
	
	const MonsterCollection* getRandomMonsterCollection(int step) const;
	bool hasNextMonsterCollection(int step) const;

	void parseString(const string& summonInfoString);

	string toString() const;
};

#endif
