#include "EffectGDRLairClose.h"
#include "GDRLairManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "ZoneGroupManager.h"
#include <cstdio>

void EffectGDRLairClose::affect() throw(Error)
{
	setNextTime( 600 );

	char msg[200];
	sprintf(msg, "%d분 동안 질드레 레어에 입장 하실수 있습니다.", m_MinutesCount );
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	g_pZoneGroupManager->broadcast( &gcSM );
	m_MinutesCount--;
}

void EffectGDRLairClose::unaffect() throw(Error)
{
	__BEGIN_TRY

	cout << "질드레 레어 닫습니다." << endl;
	GDRLairManager::Instance().close();

	GCSystemMessage gcSM;
	gcSM.setMessage("질드레 레어가 닫혔습니다.");
	g_pZoneGroupManager->broadcast( &gcSM );

	__END_CATCH
}
