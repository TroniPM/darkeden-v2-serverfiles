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
	Resource (Version_t version = 0, const string & str = "");

	// copy constructor
	Resource (const Resource & resource);

public :

	// load from file
	void load (ifstream & ifile);

	// save to file
	void save (ofstream & ofile) ;

	// read from socket input stream
	void read (SocketInputStream & iStream) ;

	// read from socket
	void read (Socket* pSocket) ;

	// write to socket output stream
	void write (SocketOutputStream & oStream) ;

	// write to socket
	void write (Socket* pSocket) ;

	// get size
	uint getSize ()  { return szVersion + (szFilenameLen + m_Filename.size()) + szFileSize; }

	// get max size
	static uint getMaxSize () throw () { return szVersion + (szFilenameLen + maxFilename) + szFileSize; }

	// equality operator
	bool operator == (const Resource & resource) 
	{
		return m_Version == resource.m_Version &&
				m_Filename == resource.m_Filename &&
				m_FileSize == resource.m_FileSize;	
	}

	// !equality operator
	bool operator != (const Resource & resource) 
	{
		return m_Version != resource.m_Version ||
				m_Filename != resource.m_Filename ||
				m_FileSize != resource.m_FileSize;	
	}


	
public :

	// get/set version
	Version_t getVersion ()  { return m_Version; }
	void setVersion (Version_t version) throw () { m_Version = version; }
	
	// get/set filename
	string getFilename ()  { return m_Filename; }
	void setFilename (const string & filename) throw () { m_Filename = filename; }

	// get/set filesize
	FileSize_t getFileSize ()  { return m_FileSize; }
	void setFileSize (FileSize_t filesize) throw () { m_FileSize = filesize; }
	void setFileSize (const string & filesize) throw () { m_FileSize = atoi(filesize.c_str()); }
	
	// get debug string
	string toString () ;


private :

	Version_t m_Version; 	// Ŭ���̾�Ʈ ����
	string m_Filename;		// �ٿ�޾ƾ� �� ���ϸ�
	DWORD m_FileSize;		// ���� ũ��

};

#endif
