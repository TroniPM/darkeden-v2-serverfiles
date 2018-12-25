//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectInstallTurret.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INSTALL_TURRET__
#define __EFFECT_INSTALL_TURRET__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectInstallTurret
//////////////////////////////////////////////////////////////////////////////

class EffectInstallTurret : public Effect 
{
public:
	EffectInstallTurret(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_INSTALL_TURRET; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int bonus) { m_Damage = bonus; }

	int getDefense(void) const { return m_Defense; }
	void setDefense(int bonus) { m_Defense = bonus; }

private :
	int m_Damage;
	int m_Defense;
};

#endif // __EFFECT_INSTALL_TURRET__
