#include "RandomRewardClass.h"
#include "RewardInfo.h"
#include "Assert.h"

RewardInfo*	RandomRewardClass::selectReward( PlayerCreature* pPC ) 
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	vector<RewardInfo*>::size_type index = rand() % m_RewardInfos.size();
	return m_RewardInfos[ index ];

	__END_CATCH
}

string RandomRewardClass::toString() 
{
	return "RandomRewardClass() : \n" + RewardClass::toString();
}
