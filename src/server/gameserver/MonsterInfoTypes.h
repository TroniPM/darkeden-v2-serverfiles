#ifndef __MONSTER_INFO_TYPES__
#define __MONSTER_INFO_TYPES__


//////////////////////////////////////////////////////////////////////////////
// Class Monster;
// AI �� ���ؼ� ������ ������, �ַ� PC ���� ���� ����� �Ǵ� ũ��ó���̴�.
//////////////////////////////////////////////////////////////////////////////
enum
{
	CLAN_NONE,							// ��𿡵� ������ �ʴ� �ִ�.. 0
	CLAN_VAMPIRE_MONSTER,				// ������ ���� ���� -_-;     1
	CLAN_VAMPIRE_BATHORY_MONSTER,		// ���丮 �Ҽ� ����          2
	CLAN_VAMPIRE_TEPEZ_MONSTER,			// ������ �Ҽ� ����          3
	CLAN_SLAYER_MONSTER,				// �����̾� ���� - -;;       4

	CLAN_MAX
};

extern int DefaultClanID[CLAN_MAX];

//////////////////////////////////////////////////////////////////////////////
// RegenType - ���Ͱ� ��Ÿ���� ���
//
// üũ�ϴ� ������ �ǹ̵� �ִµ�, 
// Hide�� default�� ���� ū ���̹Ƿ� ���� ���߿� üũ�ؾ��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
enum RegenType
{
	REGENTYPE_PORTAL,		// ��Ż�� Ÿ�� ��Ÿ���� ���
	REGENTYPE_INVISIBLE,	// invisible���·� ��Ÿ���� ���
	REGENTYPE_BAT,			// ���� ���·� ��Ÿ���� ���
	REGENTYPE_HIDE,			// �� �ӿ� ���� �ִ� ���·�
	
	REGENTYPE_MAX
};

#endif
