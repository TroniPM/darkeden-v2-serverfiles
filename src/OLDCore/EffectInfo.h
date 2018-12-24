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
	PacketSize_t getSize () const throw () { return szBYTE + szWORD* m_ListNum* 2; }
	static PacketSize_t getMaxSize() throw() { return 255;}

	// get packet's debug string
	string toString () const throw ();

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(EffectID_t EffectID, WORD Value) throw(); 

	// ClearList
	void clearList() throw() { m_EList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	WORD popFrontListElement() throw() { WORD EffectList = m_EList.front(); m_EList.pop_front(); return EffectList; }

protected :
	
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	list<WORD> m_EList;

};

#endif
