//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectManager.h
// Written by  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Effect.h"
#include "EffectInfo.h"
#include "Timeval.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class EffectManager;
//////////////////////////////////////////////////////////////////////////////

class EffectManager 
{
public:
	EffectManager() throw(Error);
	virtual ~EffectManager() throw();

public:
	void save(const string & ownerID) throw(Error);

	EffectInfo* getEffectInfo() throw();

	bool isEffect(Effect::EffectClass EClass) throw();

	void deleteEffect(Effect::EffectClass EClass) throw();
	void deleteEffect(ObjectID_t ObjectID) throw();
	void deleteEffect(Creature* pCreature, Effect::EffectClass EClass) throw();
	Effect* findEffect(Effect::EffectClass EClass) const throw();
	Effect* findEffect(ObjectID_t ObjectID) const throw();

	// Enemy Erase ����Ʈ�� �������� ���� �Լ��̴�.
	Effect* findEffect(Effect::EffectClass EClass, string EnemyName) const throw();

	// priority_queue�� ����ϰ�, affect�Ѵ�.
	void addEffect(Effect* pEffect) throw();

	Effect* getEffect() const throw() { return m_Effects.front(); }

	// ���� �ִ� ��� ����Ʈ�� deadline �� 0���� �����.
	void setTimeOutAllEffect() throw();

	// ���� �ð����� ����Ǿ�� �ϴ� ����Ʈ�� ã�Ƽ� affect ��Ű�ų�, 
	// expire �� ����Ʈ�� �����Ѵ�.
//	int heartbeat() throw(Error);
	int heartbeat(const Timeval& currentTime) throw(Error);

	void	sendEffectInfo(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

	// ���� ����Ʈ ���� ��ȯ
	uint getSize() const { return m_Effects.size(); }

protected:
	list<Effect*> m_Effects;

	// by sigi. for debugging. 2002.12.23
	int m_LastEffectClass;

	EffectInfo	m_EffectInfo;
};

#endif
