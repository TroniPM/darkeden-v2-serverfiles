//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLightness.h
// Written by  : excel96
// Description : 
// Lightness�� ���ؼ� �����Ǵ� �꼺 ������ ��ȭ ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LIGHTNESS__
#define __EFFECT_LIGHTNESS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLightness
//////////////////////////////////////////////////////////////////////////////

class EffectLightness : public Effect 
{
public:
	EffectLightness(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LIGHTNESS; }

	void affect() throw(Error){}

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_LIGHTNESS__
