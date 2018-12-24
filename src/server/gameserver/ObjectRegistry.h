//////////////////////////////////////////////////////////////////////////////
// Filename    : ObjectRegistry.h
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_REGISTERY_H__
#define __OBJECT_REGISTERY_H__

#include "Types.h"
#include "Exception.h"
#include "Object.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ObjectRegistry;
// ��ü���� ObjectID�� �Ҵ��Ѵ�. 
//////////////////////////////////////////////////////////////////////////////

class ObjectRegistry 
{
public:
	ObjectRegistry() throw();

public:
	void registerObject(Object* pObject) throw();
	void registerObject_NOLOCKED(Object* pObject) throw();
	void lock() throw(Error);
	void unlock() throw(Error);

private:
	ObjectID_t m_ObjectIDKey; // Object ID ������ ���� Ű��
	mutable Mutex m_Mutex; // mutex
};

// global variable declaration
extern ObjectRegistry* g_pObjectRegistry;

#endif
