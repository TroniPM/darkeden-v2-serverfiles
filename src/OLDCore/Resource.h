//--------------------------------------------------------------------------------
// 
// Filename    : Resource.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __RESOURCE_H__
#define __RESOURCE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "UpdateDef.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#include <stdlib.h>


// forward declaration
class Socket;


//--------------------------------------------------------------------------------
//
// class Resource
//
// �ٿ�ε� �޾ƾ��� ������ ��Ÿ����.
//
//--------------------------------------------------------------------------------

class Resource {

public :

	// constructor
	Resource (Version_t version = 0, const string & str = "") throw (ProtocolException, Error);

	// copy constructor
	Resource (const Resource & resource) throw ();

public :

	// load from file
	void load (ifstream & ifile) throw (Error);

	// save to file
	void save (ofstream & ofile) const throw (Error);

	// read from socket input stream
	void read (SocketInputStream & iStream) throw (IOException, Error);

	// read from socket
	void read (Socket* pSocket) throw (IOException, Error);

	// write to socket output stream
	void write (SocketOutputStream & oStream) const throw (IOException, Error);

	// write to socket
	void write (Socket* pSocket) const throw (IOException, Error);

	// get size
	uint getSize () const throw () { return szVersion + (szFilenameLen + m_Filename.size()) + szFileSize; }

	// get max size
	static uint getMaxSize () throw () { return szVersion + (szFilenameLen + maxFilename) + szFileSize; }

	// equality operator
	bool operator == (const Resource & resource) const throw ()
	{
		return m_Version == resource.m_Version &&
				m_Filename == resource.m_Filename &&
				m_FileSize == resource.m_FileSize;	
	}

	// !equality operator
	bool operator != (const Resource & resource) const throw ()
	{
		return m_Version != resource.m_Version ||
				m_Filename != resource.m_Filename ||
				m_FileSize != resource.m_FileSize;	
	}


	
public :

	// get/set version
	Version_t getVersion () const throw () { return m_Version; }
	void setVersion (Version_t version) throw () { m_Version = version; }
	
	// get/set filename
	string getFilename () const throw () { return m_Filename; }
	void setFilename (const string & filename) throw () { m_Filename = filename; }

	// get/set filesize
	FileSize_t getFileSize () const throw () { return m_FileSize; }
	void setFileSize (FileSize_t filesize) throw () { m_FileSize = filesize; }
	void setFileSize (const string & filesize) throw () { m_FileSize = atoi(filesize.c_str()); }
	
	// get debug string
	string toString () const throw ();


private :

	Version_t m_Version; 	// Ŭ���̾�Ʈ ����
	string m_Filename;		// �ٿ�޾ƾ� �� ���ϸ�
	DWORD m_FileSize;		// ���� ũ��

};

#endif
