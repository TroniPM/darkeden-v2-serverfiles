//////////////////////////////////////////////////////////////////////////////
// Filename    : ObjectManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class ObjectManager;
// ���� ���� ��ü���� �Ŵ����� �����ϴ� ���� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

class ObjectManager 
{
public:
	ObjectManager() throw(Error);
	~ObjectManager() throw(Error);

public:
	void init() throw(Error);
	void load() throw(Error);
	void save() throw(Error);
};

// global variable declaration
extern ObjectManager* g_pObjectManager;

#endif
