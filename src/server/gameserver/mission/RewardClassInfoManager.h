#ifndef __REWARD_CLASS_INFO_MANAGER__
#define __REWARD_CLASS_INFO_MANAGER__

#include "Types.h"
#include "Exception.h"

#include "Gpackets/GCNPCResponse.h"

#include <hash_map>

class RewardClass;
class PlayerCreature;
class NPC;

class RewardClassInfoManager
{
protected:
	typedef hash_map<RewardClass_t,RewardClass*> RewardClassHashMap;

public:
	RewardClassInfoManager( NPC* pNPC );
	virtual ~RewardClassInfoManager();

public:
	virtual void load( const string& name = "" )  = 0;

	bool			hasReward( RewardClass_t rClass ) const { return m_RewardClasses.find(rClass) != m_RewardClasses.end(); }
	QuestMessage	canGiveReward( RewardClass_t rClass, PlayerCreature* pPC ) ;
//	QuestMessage	giveReward( RewardClass_t rClass, PlayerCreature* pPC );
	RewardClass*	getRewardClass( RewardClass_t rClass ) ;

protected:
	NPC*				m_pOwnerNPC;
	RewardClassHashMap	m_RewardClasses;
};

#endif //  __REWARD_CLASS_INFO_MANAGER__

