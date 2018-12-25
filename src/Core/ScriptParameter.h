//////////////////////////////////////////////////////////////////////
// 
// Filename    : ScriptParameter.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SCRIPT_PARAMETER_H__
#define __SCRIPT_PARAMETER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class ScriptParameter;
//
// 
//
//////////////////////////////////////////////////////////////////////

class ScriptParameter {

public :
	
	// constructor
	ScriptParameter () throw ();
	
	// destructor
	~ScriptParameter () throw ();

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return szBYTE + 255 + szBYTE + 255;
	}

	// get packet's debug string
	string toString () const throw ();

	// get/set Name
	string getName()  { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

	// get/set Value
	string getValue()  { return m_Value; }
	void setValue( const string& value ) throw() { m_Value = value; }

private :

	string m_Name;
	string m_Value;
};

#endif
