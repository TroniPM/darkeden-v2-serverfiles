//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasBloodBible.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_BLOOD_BIBLE__
#define __EFFECT_HAS_BLOOD_BIBLE__

#include "EffectHasRelic.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasBloodBible
//////////////////////////////////////////////////////////////////////////////

class EffectHasBloodBible : public EffectHasRelic 
{
public:
	EffectHasBloodBible(Creature* pCreature);
	EffectHasBloodBible(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HAS_BLOOD_BIBLE; }

	void affect(Creature* pCreature);
	void affect(Item* pItem);

	string toString() ;

public:
	void   	setPart(int part) throw();

private:
	string	m_PartName;	// 피의 성서 조각 이름
};

#endif 
