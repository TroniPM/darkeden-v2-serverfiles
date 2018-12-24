////////////////////////////////////////////////////////////////////////////////
// Filename    : PropertyBuffer.h
// Written By  : 
// Description :
// DB�� TEXT �� ����� Condition/Action �ʵ带 �Ľ����ش�.
// Properties �� �ٸ� ����, Properties �� ���� ������ ��� �Ľ��ؼ� map ����
// ��ȯ�� ����, getProperty() �� ȣ��Ǹ� ������ value �� ����������,
// PropertyBuffer �� ���ο� ū ��Ʈ���� ���۸� �ΰ�, getProperty()�� ȣ���
// ������ ������ �տ������� �Ľ��� �ѹ��� �����Ѵٴ� ���̴�.
////////////////////////////////////////////////////////////////////////////////

#ifndef __PROPERTY_BUFFER_H__
#define __PROPERTY_BUFFER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class PropertyBuffer;
//////////////////////////////////////////////////////////////////////////////

class PropertyBuffer 
{
public:
	static const char Comment;
	static const char Separator;
	static const char EOL;
	static const char* WhiteSpaces;
	static const char* SpaceTab;
	
public:
	PropertyBuffer(const string & buffer) throw();
	~PropertyBuffer() throw();
	
public:
	string getProperty(string key) throw(NoSuchElementException, Error);
	int getPropertyInt(string key) throw(NoSuchElementException, Error);

	bool getProperty(string key, string& value) throw(NoSuchElementException, Error);
	bool getPropertyInt(string key, int& value) throw(NoSuchElementException, Error);

	string toString() const throw();
	
private:
	uint   m_Index;
	string m_Buffer;
	
};

#endif
