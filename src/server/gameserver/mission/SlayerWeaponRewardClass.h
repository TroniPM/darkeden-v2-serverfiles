//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerWeaponRewardClass.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_WEAPON_REWARD_CLASS_H__
#define __SLAYER_WEAPON_REWARD_CLASS_H__

#include "RewardClass.h"

//////////////////////////////////////////////////////////////////////////////
// class SlayerWeaponRewardClass;
//////////////////////////////////////////////////////////////////////////////

class SlayerWeaponRewardClass : public RewardClass
{
public:
	SlayerWeaponRewardClass( RewardClass_t rClass ) : RewardClass(rClass) { }

public:
	virtual RewardInfo*		selectReward( PlayerCreature* pPC ) ;
	virtual QuestMessage	giveReward( PlayerCreature* pPC ) ;

	virtual string	toString() ;

private:
};

#endif
