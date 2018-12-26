//--------------------------------------------------------------------------------
// QuestPricePenalty.h
//--------------------------------------------------------------------------------

#include "QuestPricePenalty.h"
#include "Creature.h"

//--------------------------------------------------------------------------------
// affect ( Creature* )
//--------------------------------------------------------------------------------
void	
QuestPricePenalty::affect(Creature* pCreature) 
	
{
	__BEGIN_TRY

	if (pCreature==NULL)
		return;

	// pCreature�� gold����
	// pCreature�� rankExp����
	// pCreature�� fame����
	cout << "[Penalty to " << pCreature->getName().c_str() << "] "
		 << "Gold=" << (int)getGold()
		 << ", RankExp=" << (int)getRankExp()
		 << ", Fame=" << (int)getFame() << endl;

	// ��ȭ�� ������ DB�� ����

	__END_CATCH
}

