//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeterChakram.h
// Written by  : elca@ewestsoft.com
// Description : �������� HeterChakram�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HETER_CHAKRAM__
#define __EFFECT_HETER_CHAKRAM__

#include "Effect.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHeterChakram
//////////////////////////////////////////////////////////////////////////////

class EffectHeterChakram : public Effect 
{
public:
	EffectHeterChakram(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HETER_CHAKRAM; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	ObjectID_t getUserOID(void) const { return m_UserOID; }
	void setUserOID(ObjectID_t UserOID ) { m_UserOID = UserOID; }

	Damage_t getDamage(void) const { return m_Damage; }
	void setDamage(Damage_t Damage ) { m_Damage = Damage; }

	Turn_t getDuration(void) const { return m_Duration; }
	void setDuration(Turn_t Duration ) { m_Duration = Duration; }

// 	int getAttackNum(void) const { return m_AttackNum; }
// 	void setAttackNum(int AttackNum ) { m_AttackNum = AttackNum; }

private:
	ObjectID_t  			m_UserOID;
	Damage_t				m_Damage;
	Turn_t					m_Duration;
// 	int						m_AttackNum;
// 	HP_t					m_TrageSaveHP;
};

#endif // __EFFECT_FIRECE_FLAME__
