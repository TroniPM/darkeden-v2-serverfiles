//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMonsterKillQuestStatusHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMonsterKillQuestStatus.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCMonsterKillQuestStatusHandler::execute ( GCMonsterKillQuestStatus * pGCMonsterKillQuestStatus , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	//cout << pGCMonsterKillQuestStatus->toString() << endl;
	
#elif __WINDOWS__

#endif

	__END_DEBUG_EX __END_CATCH
}
