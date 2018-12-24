//////////////////////////////////////////////////////////////////////
// 
// Filename    : OustersSkillInfo.h 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_SKILL_INFO_H__
#define __OUSTERS_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "PCSkillInfo.h"
#include "SubOustersSkillInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class OustersSkillInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class OustersSkillInfo : public PCSkillInfo {

public :
	
	// constructor
	OustersSkillInfo () throw ();
	
	// destructor
	~OustersSkillInfo () throw ();

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () throw ();

	static uint getMaxSize () throw () { 
		return szBYTE + szBYTE + (SubOustersSkillInfo::getMaxSize()* 120);
	}

	// get packet's debug string
	string toString () const throw ();

	// get / set New Skill
	bool isLearnNewSkill() const throw() { return m_bLearnNewSkill; }
	void setLearnNewSkill(bool NewSkill) throw() { m_bLearnNewSkill = NewSkill; }

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(SubOustersSkillInfo* pSubOustersSkillInfo) throw() { m_SubOustersSkillInfoList.push_back(pSubOustersSkillInfo); }

	// ClearList
	void clearList() throw() { m_SubOustersSkillInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	SubOustersSkillInfo* popFrontListElement() throw() 
	{ 
		SubOustersSkillInfo* TempSubOustersSkillInfo = m_SubOustersSkillInfoList.front(); m_SubOustersSkillInfoList.pop_front(); return TempSubOustersSkillInfo; 
	}

private :

	// New ��ų�� ��� �� �ִ��� ������ ����
	bool m_bLearnNewSkill;

	// SubOustersSkillInfo List Total Number
	BYTE m_ListNum;

	// SubOustersSkillInfo List
	list<SubOustersSkillInfo*> m_SubOustersSkillInfoList;

};

#endif
