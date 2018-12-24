#include "EffectGDRLairClose.h"
#include "GDRLairManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "ZoneGroupManager.h"
#include <cstdio>

void EffectGDRLairClose::affect() throw(Error)
{
	setNextTime( 600 );

	char msg[200];
	sprintf(msg, "%d�� ���� ���巹 ��� ���� �ϽǼ� �ֽ��ϴ�.", m_MinutesCount );
	GCSystemMessage gcSM;
	gcSM.setMessage(msg);
	g_pZoneGroupManager->broadcast( &gcSM );
	m_MinutesCount--;
}

void EffectGDRLairClose::unaffect() throw(Error)
{
	__BEGIN_TRY

	cout << "���巹 ���� �ݽ��ϴ�." << endl;
	GDRLairManager::Instance().close();

	GCSystemMessage gcSM;
	gcSM.setMessage("���巹 ��� �������ϴ�.");
	g_pZoneGroupManager->broadcast( &gcSM );

	__END_CATCH
}
