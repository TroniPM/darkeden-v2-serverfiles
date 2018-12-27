//////////////////////////////////////////////////////////////////////////////
// Filename    : FlagSet.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __FLAGSET_H__
#define __FLAGSET_H__

#include "Types.h"
#include "Exception.h"
#include <string>

#define FLAG_SIZE_MAX 3*8

enum FlagSetType
{
	FLAGSET_RECEIVE_NEWBIE_ITEM,				// 0 - �ʺ��ڿ� ������ ���� ���
	FLAGSET_RECEIVE_NEWBIE_ITEM_FIGHTER,		// 1 - sword, blade
	FLAGSET_RECEIVE_NEWBIE_ITEM_CLERIC,			// 2 - heal, enchant
	FLAGSET_RECEIVE_NEWBIE_ITEM_GUNNER,			// 3 - gun

	FLAGSET_TRADE_GIFT_BOX_2002_12,				// 4 - 2002.12 ũ�������� �̺�Ʈ ���� ���� ���� ��ȯ ����
	FLAGSET_RECEIVE_GREEN_GIFT_BOX,				// 5 - �ٸ� ������κ��� ��� ���� ���ڸ� �޾ҳ�

	FLAGSET_RECEIVE_NEWBIE_ITEM_AUTO,			// 6 - �ʺ��ڿ� �������� �ڵ����� �޾ƾ� �ϴ���

	FLAGSET_RECEIVE_PREMIUM_EVENT_ITEM_2003_3,	// 7 - 2003.3.1 �����̾� ����ڵ鿡�� ���� �ش�.

	FLAGSET_IS_COUPLE,							// 7 - �̹� Ŀ���ΰ�.
	FLAGSET_WAS_COUPLE,							// 8 - Ŀ�� �̾���.		- 2003.3 �� Ŀ���̺�Ʈ��

	FLAGSET_NOT_JUST_CREATED,					// 9 - �� ������ ĳ���Ͱ� �ƴѰ�.

	FLAGSET_CLEAR_RANK_BONUS_5,					// 10 - 5 ���� ��� ��ų�� �ʱ�ȭ �� ���� �ִ°�?
	FLAGSET_CLEAR_RANK_BONUS_10,				// 11 - 10 ���� ��� ��ų�� �ʱ�ȭ �� ���� �ִ°�?
	FLAGSET_CLEAR_RANK_BONUS_15,				// 12 - 15 ���� ��� ��ų�� �ʱ�ȭ �� ���� �ִ°�?
	FLAGSET_CLEAR_RANK_BONUS_20,				// 13 - 20 ���� ��� ��ų�� �ʱ�ȭ �� ���� �ִ°�?

	FLAGSET_GNOMES_HORN,						// 14 - ���������� �� ����� �ξ��°�

	FLAGSET_SWAP_COAT,							// 15 - �� ���Ǹ� �ٲ�°�
	FLAGSET_SWAP_TROUSER,						// 16 - �� ���Ǹ� �ٲ�°�
	FLAGSET_SWAP_WEAPON,						// 17 - ���⸦ �ٲ�°�

	FLAGSET_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class Flag
//////////////////////////////////////////////////////////////////////////////

class FlagSet
{

///// Member methods /////
	
public:
	FlagSet() ;
	~FlagSet() ;

public:
	void create(const string& owner) ;
	void load(const string& owner) ;
	void save(const string& owner) ;
	void destroy(const string& owner) ;

public:
	bool isOn(int index) ;
	bool turnOn(int index) ;
	bool turnOff(int index) ;

public:
	string toString(void) ;
	static FlagSet fromString(const string& text) ;

	static void initialize(void) ;

protected:
	bool isValidIndex(int index) ;
	BYTE* getData()  { return &m_pData[0]; }
	

///// Member data /////
	
protected:
	BYTE m_pData[FLAG_SIZE_MAX/8];

	static string m_pLookup[256];
	static bool   m_bInit;
};


#endif



