//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFadeOut.h
// Written by  : elca@ewestsoft.com
// Description : 
// ���α�� Sniping �Ǵ� �����̾� ��� Invisibility�� ���ؼ�
// ���� ���� ����������� �ִ�(������� �ִ�) ũ���Ŀ� �ٴ� ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FADE_OUT__
#define __EFFECT_FADE_OUT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFadeOut
//////////////////////////////////////////////////////////////////////////////

class EffectFadeOut : public Effect 
{
public:
	EffectFadeOut(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_FADE_OUT; }

	void affect() {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Item* pItem) {}
	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
	Duration_t getDuration()  { return m_Duration;}
	void setDuration(Duration_t d)  { m_Duration = d;}

	bool isSniping(void) const { return m_isSniping; }
	void setSniping()  { m_isSniping = true; }
	
	bool isInvisibility(void) const { return !m_isSniping; }
	void setInvisibility()  { m_isSniping = false; }

private:
	Duration_t  m_Duration;
	bool        m_isSniping;

};

#endif // __EFFECT_FADE_OUT__
