//////////////////////////////////////////////////////////////////////////////
// Filename    : GearSlotInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GEAR_SLOT_INFO_H__
#define __GEAR_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// Inventory ������ ��� �ִ� ��ü.
//////////////////////////////////////////////////////////////////////////////

class GearSlotInfo : public PCItemInfo 
{
public:
	void read (SocketInputStream & iStream);
	void write (SocketOutputStream & oStream) ;

	uint getSize () 
	{ 
		return PCItemInfo::getSize() + szSlotID;
	}

	static uint getMaxSize () 
	{ 
		return PCItemInfo::getMaxSize() + szSlotID;
	}

	string toString () ;

public:
	void setSlotID(SlotID_t SlotID)  { m_SlotID = SlotID; }
	SlotID_t getSlotID()  { return m_SlotID; }

private:
	SlotID_t m_SlotID;
};

#endif
