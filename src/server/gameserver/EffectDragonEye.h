//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDragonEye.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DRAGON_EYE__
#define __EFFECT_DRAGON_EYE__

#include "EffectHasRelic.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDragonEye
//////////////////////////////////////////////////////////////////////////////

class EffectDragonEye : public EffectHasRelic 
{
public:
	EffectDragonEye(Creature* pCreature);
	EffectDragonEye(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DRAGON_EYE; }

	void affect(Creature* pCreature);
	void affect(Item* pItem);

	void unaffect(Creature* pCreature);

	string toString() ;

	// get/set ItemID
	ItemID_t getItemID() const { return m_ItemID; }
	void setItemID( ItemID_t itemID ) { m_ItemID = itemID; }

private:
	// DragonEye �������� ID. GlobalPostionLoader �� ���� ���
	ItemID_t	m_ItemID;
};

#endif 
