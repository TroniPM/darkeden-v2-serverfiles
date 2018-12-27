//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFadeOut.cpp
// Written by  : elca
// Description : 
// ���α�� Sniping �Ǵ� �����̾� ��� Invisibility�� ���ؼ�
// ���� ���� ����������� �ִ�(������� �ִ�) ũ���Ŀ� �ٴ� ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "EffectFadeOut.h"
#include "EffectInvisibility.h"
#include "EffectSnipingMode.h"
#include "Slayer.h"
#include "Vampire.h"
#include "DB.h"
#include "ZoneUtil.h"

#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectFadeOut::EffectFadeOut(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	
	//cout << "EffectFadeOut " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	ZoneCoord_t x = pCreature->getX();
	ZoneCoord_t y = pCreature->getY();
	pCreature->removeFlag(Effect::EFFECT_CLASS_FADE_OUT);

	// ���α�� Sniping�� ���� ���̶��...
	if (m_isSniping) 
	{
		// �����̾�� �ش�ȴ�.
		Assert(pCreature->isSlayer());
		Assert(pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) == false);
		Assert(pCreature->findEffect(Effect::EFFECT_CLASS_SNIPING_MODE) == NULL);

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		
		EffectSnipingMode* pEffect = new EffectSnipingMode(pSlayer);
		pEffect->setDeadline(m_Duration);
		pSlayer->addEffect(pEffect);
		pSlayer->setFlag(Effect::EFFECT_CLASS_SNIPING_MODE);

		// ����Ʈ�� �ٿ�����, �ɷ�ġ�� �����Ѵ�.
		SLAYER_RECORD prev;
		pSlayer->getSlayerRecord(prev);
		pSlayer->initAllStat();
		pSlayer->sendRealWearingInfo();
		pSlayer->sendModifyInfo(prev);

		addSnipingModeCreature(pZone, pCreature, x, y);
	} 
	// �����̾� ��� Invisibility�� ���� ���̶��... 
	else 
	{
		// �����̾ ���͸��� �ش�ȴ�.
		Assert(pCreature->isVampire() || pCreature->isMonster());
		Assert(pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) == false);
		Assert(pCreature->findEffect(Effect::EFFECT_CLASS_INVISIBILITY) == NULL);
		
		EffectInvisibility* pEffect = new EffectInvisibility(pCreature);
		pEffect->setNextTime(10);
		pEffect->setDeadline(99999999); // �����̴�.
		pCreature->addEffect(pEffect);

		addInvisibleCreature(pZone, pCreature, x, y);
	}

	//cout << "EffectFadeOut " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectFadeOut " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);
	
	//cout << "EffectFadeOut " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectFadeOut::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectFadeOut("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

