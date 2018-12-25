#include "MiniGameQuestInfo.h"

MiniGameQuestStatus* MiniGameQuestInfo::makeQuestStatus( PlayerCreature *pPC ) 
{
	__BEGIN_TRY

	return new MiniGameQuestStatus( getQuestID(), VSDateTime::currentDateTime().addSecs(getTimeLimit()), m_GameType );

	__END_CATCH
}

