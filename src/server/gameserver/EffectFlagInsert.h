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
	EffectFlagInsert(Creature* pCreature);
	EffectFlagInsert(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_FLAG_INSERT; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);
	void affect(Item* pItem);

	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem);
	void unaffect(); 

	string toString() ;

};

#endif // __EFFECT_DOOM__
