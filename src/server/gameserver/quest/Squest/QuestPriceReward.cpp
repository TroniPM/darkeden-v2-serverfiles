//--------------------------------------------------------------------------------
// QuestPriceReward.h
//--------------------------------------------------------------------------------

#include "QuestPriceReward.h"
#include "Creature.h"

//--------------------------------------------------------------------------------
// affect ( Creature* )
//--------------------------------------------------------------------------------
void	
QuestPriceReward::affect(Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	if (pCreature==NULL)
		return;

	// pCreature�� gold����
	// pCreature�� rankExp����
	// pCreature�� fame����
	cout << "[Reward to " << pCreature->getName().c_str() << "] "
		<< "Gold=" << (int)getGold()
		<< ", RankExp=" << (int)getRankExp()
		<< ", Fame=" << (int)getFame() << endl;

	// ��ȭ�� ������ DB�� ����

	__END_CATCH
}

