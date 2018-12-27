//----------------------------------------------------------------------
//
// Filename    : EffectTransportCreature.cpp
// Written by  : elca
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectTransportCreature.h"
#include "Gpackets/GCSystemMessage.h"
#include "VariableManager.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Slayer.h"
#include "Player.h"
#include "StringPool.h"

#include <stdio.h>


//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectTransportCreature::EffectTransportCreature (Creature *pCreature, ZoneID_t zoneID , ZoneCoord_t x , ZoneCoord_t y , Turn_t delay) 
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	Assert(pCreature->getZone()!=NULL);

	m_CreatureID = pCreature->getObjectID();
	m_ZoneID = zoneID;
	m_pZone = pCreature->getZone();	// �׳� �ٸ� �������� assert������
	setTarget( pCreature );
	setDeadline( delay );
	setNextTime( 0 );

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectTransportCreature::~EffectTransportCreature () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectTransportCreature::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = m_pZone->getCreature( m_CreatureID );
	//Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	if (pCreature!=NULL)
	{
		affect(pCreature);
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// affect
//----------------------------------------------------------------------
void EffectTransportCreature::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Timeval      nextTime   = getNextTime();
	Timeval      deadLine   = getDeadline();
	Turn_t       RemainTime = deadLine.tv_sec - nextTime.tv_sec;

//	StringStream msg;
//	msg << (int)RemainTime << "�� �Ŀ� " << m_ZoneName << "�� �̵��˴ϴ�.";

    char msg[50];
    sprintf( msg, g_pStringPool->c_str( STRID_TRANSPORT_CREATURE ),
                    (int)RemainTime,
                    m_ZoneName.c_str() );

	string sMsg( msg );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(sMsg);
	pCreature->getPlayer()->sendPacket( &gcSystemMessage );

	setNextTime( m_MessageTick );

	__END_CATCH
}
			
//--------------------------------------------------------------------
// unaffect()
//--------------------------------------------------------------------
void EffectTransportCreature::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = m_pZone->getCreature( m_CreatureID );
	//Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);

	if (pCreature!=NULL)
	{
		unaffect(pCreature);
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect
//--------------------------------------------------------------------
void EffectTransportCreature::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	Assert(m_pZone!=NULL);

	transportCreature( pCreature, m_ZoneID, getX(), getY(), false );

	__END_CATCH
}



//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectTransportCreature::toString () const 
	
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectTransportCreature("
				<< ",ZoneName:" << m_ZoneName.c_str()
				<< ",ZoneID:" << (int)m_pZone->getZoneID()
				<< ",X:"     << (int)getX()
				<< ",Y:"     << (int)getY()
				<< ")";
	}

	return msg.toString();
}
