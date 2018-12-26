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
	EffectManager();
	virtual ~EffectManager() ;

public:
	void save(const string & ownerID);

	EffectInfo* getEffectInfo() ;

	bool isEffect(Effect::EffectClass EClass) ;

	void deleteEffect(Effect::EffectClass EClass) ;
	void deleteEffect(ObjectID_t ObjectID) ;
	void deleteEffect(Creature* pCreature, Effect::EffectClass EClass) ;
	Effect* findEffect(Effect::EffectClass EClass) ;
	Effect* findEffect(ObjectID_t ObjectID) ;

	// Enemy Erase ����Ʈ�� �������� ���� �Լ��̴�.
	Effect* findEffect(Effect::EffectClass EClass, string EnemyName) ;

	// priority_queue�� ����ϰ�, affect�Ѵ�.
	void addEffect(Effect* pEffect) ;

	Effect* getEffect()  { return m_Effects.front(); }

	// ���� �ִ� ��� ����Ʈ�� deadline �� 0���� �����.
	void setTimeOutAllEffect() ;

	// ���� �ð����� ����Ǿ�� �ϴ� ����Ʈ�� ã�Ƽ� affect ��Ű�ų�, 
	// expire �� ����Ʈ�� �����Ѵ�.
//	int heartbeat();
	int heartbeat(const Timeval& currentTime);

	void	sendEffectInfo(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y);

	// ���� ����Ʈ ���� ��ȯ
	uint getSize() const { return m_Effects.size(); }

protected:
	list<Effect*> m_Effects;

	// by sigi. for debugging. 2002.12.23
	int m_LastEffectClass;

	EffectInfo	m_EffectInfo;
};

#endif
