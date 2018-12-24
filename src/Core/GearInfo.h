//////////////////////////////////////////////////////////////////////////////
// Filename    : GearInfo.h 
// Written By  : elca@ewestsoft.com
// Description :
// �԰� �ִ� ��� �����۵��� ���� ����Ʈ�̴�.
// ������ ��� �����ۿ� ���� ������ GearSlotInfo�� �����ϸ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GEAR_INFO_H__
#define __GEAR_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "GearSlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////////////
// class GearInfo;
//////////////////////////////////////////////////////////////////////////////

class GearInfo 
{
public:
	GearInfo () throw ();
	~GearInfo () throw ();
	
public:
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	PacketSize_t getSize () throw ();

	static uint getMaxSize () throw () 
	{
		return szBYTE + (GearSlotInfo::getMaxSize()* 13);
	}

	string toString () const throw ();

public:
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	void addListElement(GearSlotInfo* pGearSlotInfo) throw() { m_GearSlotInfoList.push_back(pGearSlotInfo); }

	void clearList() throw() { m_GearSlotInfoList.clear(); m_ListNum = 0; }

	GearSlotInfo* popFrontListElement() throw() 
	{ 
		GearSlotInfo* TempGearSlotInfo = m_GearSlotInfoList.front(); m_GearSlotInfoList.pop_front(); return TempGearSlotInfo; 
	}

private:
	BYTE m_ListNum; // number of gear
	list<GearSlotInfo*> m_GearSlotInfoList; // actual gear info

};

#endif
