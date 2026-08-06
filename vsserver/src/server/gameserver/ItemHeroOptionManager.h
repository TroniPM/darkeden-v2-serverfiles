#ifndef __ITEM_HEROOPTION_MANAGER_H__
#define __ITEM_HEROOPTION_MANAGER_H__

#include "Types.h"
#include "Exception.h"

class ItemHeroOptionManager
{
public:
	ItemHeroOptionManager() { m_HeroOptionRatios; }
	void load() throw(Error);
	int getRandomHeroOptionAttr(int Group) const;
	int getRandomHeroOption() const;
	int getRandomBeadHeroOption(int Group) const;
	int getClassHeroOptionSize(int Group) const;

	static ItemHeroOptionManager& Instance();

private:
	int m_HeroOptionRatios[50][19];
	int m_HeroOptionGambleRatios[50][19];
	int m_HeroOptionBeadRatios[50][19];
};

#endif
