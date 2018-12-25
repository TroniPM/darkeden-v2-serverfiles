//////////////////////////////////////////////////////////////////////////////
// Filename    : ShopTemplate.h
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHOPTEMPLATE_H__
#define __SHOPTEMPLATE_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class ShopTemplate
// �������� �������� �ڵ����� �����ϱ� ���ؼ� DB���� ������
// ������ Ʋ�� �о���µ�, �� Ʋ�� ĸ��ȭ�� Ŭ�����̴�.
// ���� ����ü�� ����� Ŭ�����̸� ��ü������ Ư���� �ϴ� ����
// ����, �׳� �����͸� �ӽ������� �����ϴ� ���Ҹ��� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class ShopTemplate
{

///// Member methods /////
	
public:
	ShopTemplate() throw();
	virtual ~ShopTemplate() throw();

public:
	ShopTemplateID_t getID(void)  { return m_ID; }
	void setID(ShopTemplateID_t id) throw() { m_ID = id; }
	
	ShopRackType_t getShopType(void)  { return m_RackType; }
	void setShopType(const ShopRackType_t type) throw() { m_RackType = type; }

	int getItemClass(void)  { return m_ItemClass; }
	void setItemClass(int iclass) throw() { m_ItemClass = iclass; }
	
	ItemType_t getMinItemType(void)  { return m_MinItemType; }
	void setMinItemType(ItemType_t t) { m_MinItemType = t; }

	ItemType_t getMaxItemType(void)  { return m_MaxItemType; }
	void setMaxItemType(ItemType_t t) { m_MaxItemType = t; }

	uint getMinOptionLevel(void)  { return m_MinOptionLevel; }
	void setMinOptionLevel(uint o) { m_MinOptionLevel = o; }

	uint getMaxOptionLevel(void)  { return m_MaxOptionLevel;}
	void setMaxOptionLevel(uint o) { m_MaxOptionLevel = o; }

	string toString() ;


///// Member data /////

private:
	ShopTemplateID_t m_ID;            // DB entry id
	ShopRackType_t   m_RackType;      // rack type(normal, special, ...)
	int              m_ItemClass;     // item class(sword, armor, ...)
	ItemType_t       m_MinItemType;   // item type(1~5 now)
	ItemType_t       m_MaxItemType;   
	uint             m_MinOptionLevel;
	uint             m_MaxOptionLevel;

};

//////////////////////////////////////////////////////////////////////////////
// class ShopTemplateManager
// ShopTemplate Ŭ������ �ؽ����� ������ �ִ� Ŭ�����̴�.
// id�� �ָ� �׿� �ش��ϴ� ShopTemplate�� �ǵ����ִ� ������ �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class ShopTemplateManager
{

///// Member methods /////
	
public:
	ShopTemplateManager() throw();
	~ShopTemplateManager() throw();

public:
	void init() throw(Error);
	void load() throw(Error);

public:
	ShopTemplate* getTemplate(ShopTemplateID_t id) ;
	void setTemplate(ShopTemplateID_t id, ShopTemplate* pEntry) throw();

	string toString() ;


///// Member data ///// 

private:
	hash_map<ShopTemplateID_t, ShopTemplate*> m_Entries; // hash map of script

};

// global variable declaration
extern ShopTemplateManager* g_pShopTemplateManager;

#endif
