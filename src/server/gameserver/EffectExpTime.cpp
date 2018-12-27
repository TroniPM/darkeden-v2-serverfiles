//----------------------------------------------------------------------
//
// Filename    : EffectContinualGroundAttack.cpp
// Written by  : elca
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectExpTime.h"
#include "MonsterManager.h"
#include "PCManager.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "SkillUtil.h"
#include "ZoneGroupManager.h"

#include "Gpackets/GCSystemMessage.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectExpTime::EffectExpTime (Zone* pZone) 
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);

	m_pZone = pZone;

	setNextTime(10);	// 1초 후 시작
	setDeadline(99999999);

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectExpTime::~EffectExpTime () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectExpTime::affect()
	
{
	__BEGIN_TRY

	Assert(m_pZone!=NULL);

	GCSystemMessage gcSM;

	VSDateTime dt(VSDateTime::currentDateTime());
	int curHour = dt.time().hour();
	int curMin = dt.time().minute();
	int curSec = dt.time().second();
	bool TimeAdvanc = false;

				gcSM.setMessage("시간체크 test");

		if(TimeAdvanc){
			g_pZoneGroupManager->broadcast( &gcSM );
		}

	// 1분마다 돌려야 한다.
	setNextTime(10);
	
	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect()
//--------------------------------------------------------------------
void EffectExpTime::unaffect()
	
{
	__BEGIN_TRY

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectExpTime::toString () const 
	
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectExpTime("
				<< "ZoneID:" << (int)m_pZone->getZoneID();
	}

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}
