//////////////////////////////////////////////////////////////////////////////
// Filename    : RandomRewardClass.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __RANDOM_REWARD_CLASS_H__
#define __RANDOM_REWARD_CLASS_H__

#include "RewardClass.h"

//////////////////////////////////////////////////////////////////////////////
// class RandomRewardClass;
//////////////////////////////////////////////////////////////////////////////

class RandomRewardClass : public RewardClass
{
public:
	RandomRewardClass( RewardClass_t rClass ) : RewardClass(rClass) { }

public:
	RewardInfo*		selectReward( PlayerCreature* pPC ) const throw(Error);

	virtual string	toString() ;

private:
};

#endif
