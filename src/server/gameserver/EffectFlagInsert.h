//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFlagInsert.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FLAG_INSERT__
#define __EFFECT_FLAG_INSERT__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFlagInsert
//////////////////////////////////////////////////////////////////////////////
// ���� �����뿡 �ٴ� ����Ʈ�̴�.

class EffectFlagInsert : public Effect 
{
public:
	EffectFlagInsert(Creature* pCreature) throw(Error);
	EffectFlagInsert(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FLAG_INSERT; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

};

#endif // __EFFECT_DOOM__
