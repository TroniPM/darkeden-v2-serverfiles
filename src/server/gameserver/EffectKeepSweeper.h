//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKeepSweeper.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_KEEP_SWEEPER__
#define __EFFECT_KEEP_SWEEPER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectKeepSweeper
//////////////////////////////////////////////////////////////////////////////

class EffectKeepSweeper : public Effect
{
public:
	EffectKeepSweeper(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_KEEP_SWEEPER; }
	EffectClass getSendEffectClass()  { return (EffectClass)(EFFECT_CLASS_KEEP_SWEEPER + m_Part); }

	void unaffect() throw(Error);

	string toString() ;

public:
	void   	setPart(int part) throw() { m_Part = part; }

private:
	ItemType_t	m_Part;	
};

#endif 
