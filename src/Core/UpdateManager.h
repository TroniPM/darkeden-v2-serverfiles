//--------------------------------------------------------------------------------
// 
// Filename    : UpdateManager.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UPDATE_MANAGER_H__
#define __UPDATE_MANAGER_H__

// include files
#include "Update.h"
#include "Assert.h"
#include <list>
#include "Resource.h"
#include "ResourceManager.h"

//--------------------------------------------------------------------------------
// ������Ʈ ����� 1024�� ���� �����̴�..
//--------------------------------------------------------------------------------
const uint maxUpdates = 1024;

//--------------------------------------------------------------------------------
//
// class UpdateManager
//
// ������Ʈ ����� �����ϴ� �Ŵ����̴�.
//
// ��Ŷ�� embedding �Ǹ�, ���Ͻý��ۿ� save/load �Ǳ� ������,
//
// load/save
// read(SocketInputStream&)/write(SocketOutputStream&)
// read(Socket*)/write(Socket*)
//
// ��� �����ϵ��� ����.
//
//--------------------------------------------------------------------------------

class UpdateManager{

public :

	// constructor
	UpdateManager () throw ();

	// destructor
	~UpdateManager () throw ();
	

public :

	// load from update file
	void load (const string & filename) throw (Error);

	// save to update file
	void save (const string & filename) ;

	// read from socket input stream
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// read from socket
	void read (Socket* pSocket) throw (IOException, Error);

	// write to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// write to socket
	void write (Socket* pSocket) const throw (IOException, Error);

	// get size
	uint getSize () const throw ();

	// get max size
	static uint getMaxSize () throw () { return Update::getMaxSize()* maxUpdates; }


public :

	// list methods
	void push_back (Update* pUpdate) throw (Error) { Assert(pUpdate != NULL); m_Updates.push_back(pUpdate); }
	void pop_front () throw (Error) { Assert(!m_Updates.empty()); m_Updates.pop_front(); }
	Update* front () const throw (Error) { Assert(!m_Updates.empty()); return m_Updates.front(); }
	bool empty () const throw () { return m_Updates.empty(); }

	// get resource manager
	ResourceManager* getResourceManager () throw (Error);

	// get debug string
	string toString () const throw ();


private :

	// list of Update
	list< Update* > m_Updates;

	ResourceManager* m_pResourceManager;

};

#endif
