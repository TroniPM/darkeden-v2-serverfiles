//////////////////////////////////////////////////////////////////////
// 
// Filename    : EffectInfo.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INFO_H__
#define __EFFECT_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class EffectInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� ����Ʈ ������ �˷��ֱ� ���� ��ä
// GCUpdateInfo, AddSlayer, AddVampire, AddMonster� �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////

class EffectInfo {

public :
	
	// constructor
	EffectInfo () throw ();
	
	// destructor
	~EffectInfo () throw ();
	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () const throw () { return szBYTE + (szWORD+szDWORD) * m_ListNum; }
	static PacketSize_t getMaxSize() throw() { return szBYTE + (szWORD+szDWORD) * 255; }

	// get packet's debug string
	string toString () const throw ();

	// get / set ListNumber
	BYTE getListNum()  { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(EffectID_t EffectID, DWORD Value) throw(); 

	// ClearList
	void clearList() throw() { m_EList.clear(); m_ListNum = 0; }


	// pop front Element in Status List
	//DWORD popFrontListElement() throw() { DWORD EffectList = m_EList.front(); m_EList.pop_front(); return EffectList; }
	const pair<WORD,DWORD> popFrontListElement() throw() { pair<WORD,DWORD> ret = m_EList.front(); m_EList.pop_front(); return ret; }

	list<pair<WORD,DWORD> >& GetList() { return m_EList; }


	// pop front Element in Status List
	//WORD popFrontListElement() throw() { WORD EffectList = m_EList.front(); m_EList.pop_front(); return EffectList; }

protected :
	
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	list<pair<WORD,DWORD> > m_EList;

};

#endif
