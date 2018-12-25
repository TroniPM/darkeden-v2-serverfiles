#ifndef __EFFECT_GDR_LAIR_CLOSE_H__
#define __EFFECT_GDR_LAIR_CLOSE_H__

#include "Effect.h"

class EffectGDRLairClose : public Effect
{
public:
	EffectGDRLairClose( int minutes ) { setDeadline(minutes*600); m_MinutesCount = minutes; setNextTime(0); }
	EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_TRANSPORT_CREATURE; }

	void affect() throw(Error);
	void unaffect() throw(Error);

	string toString()  { return "EffectGDRLairClose"; }

private:
	int	m_MinutesCount;
};

#endif
