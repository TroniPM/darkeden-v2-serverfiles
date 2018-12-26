//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelic.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRelic.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRelic::EffectRelic(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelic::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	cout << "Effect Relic start" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	if(pCreature->isMonster())
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		if(pMonster->getMonsterType()>=371 && pMonster->getMonsterType()<= 375)
		{
			HP_t CurrentHP = pMonster->getHP(ATTR_CURRENT);

			if(CurrentHP>0)
			{
				HP_t PlusHP = min(500, CurrentHP+m_Point);

				if(PlusHP < 500)
				{
					cout << "�������� ȸ���մϴ�: " << PlusHP << endl;
				}

				pMonster->setHP(PlusHP, ATTR_CURRENT);

				GCStatusCurrentHP pkt;
				pkt.setObjectID(pMonster->getObjectID());
				pkt.setCurrentHP(PlusHP);
				pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &pkt);
			}
		}
		else
		{
			cout << "���� �������� �ƴ϶�� �� ����Ʈ�� ���� ����" << endl;
			return;
		}
	}
	else
	{
		cout << "���Ͱ� �ƴ϶�� ����Ʈ�� ���� ����" << endl;
		return;
	}

	setNextTime(m_Tick);

	__END_CATCH
}

void EffectRelic::unaffect() 
	
{
	__BEGIN_TRY	

    Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelic::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectRelic" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_RELIC);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_RELIC);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectRelic" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRelic::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRelic("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
