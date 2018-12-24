#include "LevelWar.h"

void LevelWar::execute() throw(Error)
{
	__BEGIN_TRY

	switch ( m_State )
	{
		case READY:
			executeStart();
			break;
		case START:
			executeEnd();
			break;
		default:
			Assert( /*������ ���°� �̻���*/false );
	}

	__END_CATCH
}

void LevelWar::executeStart()
{

	if (m_pManager->hasWar())
		return;

	m_pManager->startWar();
	m_State = START;

	m_pManager->addSchedule( new Schedule( this, VSDateTime::currentDateTime().addSecs(3600) ) );

	m_pManager->makeGCWarList();
	m_pManager->broadcastGCWarList();

}

void LevelWar::executeEnd()
{
	m_pManager->endWar();

	m_State = READY;

	// �̰� LevelWarManager ���� ���ֵ��� �Ѵ�
	//m_pManager->addSchedule( new Schedule( this, m_pManager->getNextLevelWarTime() ) );
}

string LevelWar::toString() const
	throw(Error)
{
	StringStream msg;

	msg << "LevelWar";

	return msg.toString();
}
