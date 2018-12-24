//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectComa.h
// Written by  : excel96
// Description : 
// �����̾ �����̾ �׾��� ��, �ɸ��� ����Ʈ.
// �� ����Ʈ�� �ɸ� �����̾�� ������ �� ������, ������ �� ����� ����� 
// �� ������, ���� �� �� ����.
// (CGMove, CGUseItem, CGSkillTo..., CGSay)
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_COMA__
#define __EFFECT_COMA__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectComa
//////////////////////////////////////////////////////////////////////////////

class EffectComa : public Effect 
{
public:
	EffectComa(Creature* pCreature) throw(Error);
	~EffectComa() throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_COMA; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

    virtual void create(const string & ownerID) throw(Error);
    virtual void save(const string & ownerID) throw(Error);
    virtual void destroy(const string & ownerID) throw(Error);	

	string toString() const throw();

public:
	Timeval getStartTime(void) const { return m_StartTime; }
	void setStartTime(void);
	bool canResurrect(void);

private:
	Timeval m_StartTime;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectComaLoader
//////////////////////////////////////////////////////////////////////////////

class EffectComaLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_COMA; }
	virtual string getEffectClassName() const throw() { return "EffectComa"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectComaLoader* g_pEffectComaLoader;

#endif // __EFFECT_COMA__
