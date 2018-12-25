//////////////////////////////////////////////////////////////////////
// 
// Filename    : ExtraInfo.h 
// Written By  : elca@ewestsoft.com
// Description : �κ��丮 �������� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EXTRA_INFO_H__
#define __EXTRA_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ExtraSlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class ExtraInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class ExtraInfo {

public :
	
	// constructor
	ExtraInfo ();
	
	// destructor
	~ExtraInfo ();

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize ();

	static uint getMaxSize () throw () { 
		return szBYTE + (ExtraSlotInfo::getMaxSize()* 1);
	}

	// get packet's debug string
	string toString () ;

	// get / set ListNumber
	BYTE getListNum()  { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(ExtraSlotInfo* pExtraSlotInfo) throw() { m_ExtraSlotInfoList.push_back(pExtraSlotInfo); }

	// ClearList
	void clearList() throw() { m_ExtraSlotInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	ExtraSlotInfo* popFrontListElement() throw() 
	{ 
		ExtraSlotInfo* TempExtraSlotInfo = m_ExtraSlotInfoList.front(); m_ExtraSlotInfoList.pop_front(); return TempExtraSlotInfo; 
	}

private :
	
	// ExtraSlotInfo List Total Number
	BYTE m_ListNum;

	// ExtraSlotInfo List
	list<ExtraSlotInfo*> m_ExtraSlotInfoList;

};

#endif
