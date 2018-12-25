//--------------------------------------------------------------------------------
//
// Filename   : TelephoneCenter.h
// Written By : elca
//
//--------------------------------------------------------------------------------

#ifndef __TELEPHONE_CENTER_H__
#define __TELEPHONE_CENTER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Slayer.h"
#include "Mutex.h"
#include <hash_map>

//--------------------------------------------------------------------------------
// class TelephoneCenter;
//
// ���� ������ �۷ι� �Ŵ��� ��ü��, PC�� ����ȣ�� ����ؼ� PC��ü�� ������ �� �ֵ���
// ���ش�. ���������� hash_map �� ����ؼ�, �˻� �ӵ��� ����Ų��.
//
//--------------------------------------------------------------------------------
class TelephoneCenter {

public:

	// add creature to hash_map
	// execute just once at PC's login
	void addSlayer(Slayer* pSlayer) throw(DuplicatedException, Error);

	// delete creature from hash_map
	// execute just once at PC's logout
	void deleteSlayer(PhoneNumber_t PhoneNumber) throw(NoSuchElementException, Error);

	// get creature with PC-name
	Slayer* getSlayer(PhoneNumber_t PhoneNumber) ;

private:

	hash_map< PhoneNumber_t, const Slayer* > m_PCs;

	mutable Mutex m_Mutex;
};

// global variable declaration
extern TelephoneCenter* g_pTelephoneCenter;

#endif
