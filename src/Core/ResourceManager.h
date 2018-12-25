//--------------------------------------------------------------------------------
// 
// Filename    : ResourceManager.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// include files
#include "Resource.h"
#include "Assert.h"
#include <list>

const uint maxResources = 1500;//modified by chengh 20060721, change the max user to connect,old value is 1024

//--------------------------------------------------------------------------------
//
// class ResourceManager
//
//--------------------------------------------------------------------------------

class ResourceManager{

public :

	// constructor
	ResourceManager ();

	// destructor
	~ResourceManager ();
	

public :

	// load from resource file
	void load (const string & filename);

	// save to resource file
	void save (const string & filename) ;


public :

	// list methods
	void push_back (Resource* pResource) throw (Error) { Assert(pResource != NULL); m_Resources.push_back(pResource); }
	void pop_front () throw (Error) { Assert(!m_Resources.empty()); m_Resources.pop_front(); }
	Resource* front ()  { Assert(!m_Resources.empty()); return m_Resources.front(); }
	bool empty ()  { return m_Resources.empty(); }

	// ������ ������ ���, ���� �ֽ� �������� �����ϰ� �������� ������ �����Ѵ�.
	void optimize ();

	// get debug string
	string toString () ;


private :

	// list of Resource
	list< Resource* > m_Resources;

};

#endif
