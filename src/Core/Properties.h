//////////////////////////////////////////////////////////////////////
//
// Filename    : Properties.h
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <map>

// help class
class StringCompare {
public :
	bool operator () (const string & left, const string & right) const
	{
		return left.compare(right) < 0;
	}
};

//////////////////////////////////////////////////////////////////////
//
// class Properties;
//
// ���Ϸκ��� (key,value) pair �� �о map �� ���·� ������ �ִ´�.
// �ַ� ȯ���̳� �ɼǵ��� ���� ���Ͽ� ����Ѵ�. ��ü�� �����ؼ� ����
// �ɼ��� �����ϰ� �����ϸ� �� ������ ���������. 
//
// *Usage*
//
// Properties prop;
// prop.load("gameserver.conf");
// cout << prop.getProperty("MODE") << endl;
// cout << prop.getProperty("NumOfPlayerThreads") << endl;
// prop.setProperty("MODE","MODE_IV");
// prop.save();
//
// Properties prop2("loginserver.conf");
// prop2.load();
// prop2.save("loginserver.new");
//
//////////////////////////////////////////////////////////////////////

class Properties {
	
public :
	
	static const char Comment;
	static const char Separator;
	static const char* WhiteSpaces;
	
public :
	
	// constructor
	Properties ();
	Properties (const string & filename);
	
	// destructor
	~Properties ();
	

public :
	
	// load from file
	void load () throw (IOException, Error);
	void load (const string & filename) throw (IOException, Error) { m_Filename = filename; load(); }

	// save to file
	void save () throw (IOException);
	void save (const string & filename) throw (IOException) { m_Filename = filename; save(); }

	// get/set property
	string getProperty (string key) ;
	int getPropertyInt (string key) ;
	void setProperty (string key, string value);

	bool hasKey(const string& key) const { return m_Properties.find(key) != m_Properties.end(); }

	// get debug string
	string toString () ;
	
private :
	
	// key �� string �̰�, value ���� string �� map �̴�.
	map< string, string, StringCompare > m_Properties;

	// load/save target file's name
	string m_Filename;
	
};

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
extern Properties* g_pConfig;
extern Properties* g_pTestConfig;	// by sigi. 2002.12.26

#endif
