#include "EffectKickOut.h"
#include "Zone.h"
#include "PCManager.h"
#include "Gpackets/GCSystemMessage.h"
#include <cstdio>

void EffectKickOut::affect() 
{
	// 1�п� �ѹ�
	setNextTime( 600 );
	m_MinutesCount--;

	char msg[200];
	sprintf(msg, "��涨ʱ�仹ʣ��%d��.", m_MinutesCount);
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	m_pZone->broadcastPacket( &gcSM );
}

void EffectKickOut::unaffect() 
{
	__BEGIN_TRY

	GCSystemMessage gcSM;
	gcSM.setMessage("�ѹ��涨ʱ��. 10����ƶ�������ص�.");
	m_pZone->broadcastPacket( &gcSM );

	if ( m_pZone != NULL ) m_pZone->getPCManager()->transportAllCreatures(0xffff);

	__END_CATCH
}
