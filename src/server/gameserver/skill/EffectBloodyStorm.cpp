#include "EffectBloodyStorm.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "EffectStormBloody.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

EffectBloodyStorm::EffectBloodyStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY)
	throw(Error)
{

	__BEGIN_TRY

	//m_StormDuration = 1.8;  

	m_UserObjectID = 0;
	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_bVampire = false;

	__END_CATCH
}


bool EffectBloodyStorm::affectCreature(Creature* pTargetCreature, bool bAffectByMove)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBloodyStorm " << "affectCreature Begin " << endl;

	Assert(pTargetCreature != NULL);

	// ��뿡�� �̹� poison ����Ʈ�� �ɷ��� �ִ� ��쿡�� �ɸ��� �ʴ´�.
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_STORM_BLOODY))
	{
		//cout << "EffectBloodyStorm " << "affectCreature End " << endl;
		return false;
	}
	
	Zone* pZone = pTargetCreature->getZone();

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );
	// ���濡�� ��ĥ �� �������� ����Ѵ�.
	int StormDamage = computeMagicDamage(pTargetCreature, m_Damage, SKILL_BLOODY_STORM, m_bVampire, pAttacker);

	if (StormDamage > 0)
	{
		// ������ ����Ʈ�� �����ؼ�, Ÿ�� ũ���Ŀ� ���̰�, �÷��׸� ���ش�.
		EffectStormBloody* pEffectStormBloody = new EffectStormBloody(pTargetCreature);
		pEffectStormBloody->setLevel(m_Level);
		pEffectStormBloody->setPoint(StormDamage/3);
		pEffectStormBloody->setDeadline(16); // �̺κ� �ٲ�� �Ѵ�.
		pEffectStormBloody->setTick(5);             // �̺κе� �ٲ�� �Ѵ�.
		pEffectStormBloody->setUserObjectID( m_UserObjectID );
		pEffectStormBloody->affect(pTargetCreature);
		pTargetCreature->addEffect(pEffectStormBloody);
		pTargetCreature->setFlag(Effect::EFFECT_CLASS_STORM_BLOODY);

		// ����Ʈ�� �پ��ٰ� �ֺ��� �˷��ش�.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pTargetCreature->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_STORM_BLOODY);
		gcAddEffect.setDuration(m_Duration);
		pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect);
	}

	//cout << "EffectBloodyStorm " << "affectCreature End " << endl;

	return true;

	__END_CATCH
}


void EffectBloodyStorm::affect()
	throw(Error)
{
	__BEGIN_TRY
/*	
	Assert(m_pZone != NULL);

	// get tile 
	Tile& tile = m_pZone->getTile(m_X, m_Y);

	HP_t CurrentHP = 0;
	HP_t RemainHP = 0;

	//
	const slist<Object*>& oList = tile.getObjectList();
	slist<Object*>::const_iterator itr = oList.begin();

	for(; itr != oList.end(); itr++)
	{
		Assert(*itr != NULL);

		Object* pObject = *itr;
		Assert(pObject != NULL);

		if(pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
		{
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			Assert(pCreature != NULL);

			int AcidDamage = computeMagicDamage(pCreature, m_Damage, SKILL_BLOODY_STORM);

			if(pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
			{
				if(pCreature->isSlayer())
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

					// 
					CurrentHP = pSlayer->getHP(ATTR_CURRENT);
                    RemainHP = max(0, CurrentHP-(int)AcidDamage);

					pSlayer->setHP(RemainHP, ATTR_CURRENT);
					 
					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_HP, pSlayer->getHP(ATTR_CURRENT));

					Player* pPlayer = pSlayer->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					GCStatusCurrentHP pkt;
					pkt.setObjectID(pSlayer->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &pkt);
				}
				else if(pCreature->isVampire())
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

					// 
					CurrentHP = pVampire->getHP(ATTR_CURRENT);
                    RemainHP = max(0, CurrentHP-(int)AcidDamage);

					pVampire->setHP(RemainHP, ATTR_CURRENT);
					 
					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_CURRENT_HP, pVampire->getHP(ATTR_CURRENT));

					Player* pPlayer = pVampire->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);

					GCStatusCurrentHP pkt;
					pkt.setObjectID(pVampire->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &pkt);
				}
				else if(pCreature->isMonster())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					CurrentHP = pMonster->getHP(ATTR_CURRENT);
					RemainHP = max(0, CurrentHP-(int)AcidDamage);

					pMonster->setHP(RemainHP, ATTR_CURRENT);

					GCStatusCurrentHP pkt;
					pkt.setObjectID(pMonster->getObjectID());
					pkt.setCurrentHP(RemainHP);
					m_pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &pkt);
				}
			}
		}
		
	}
		
	setNextTime(m_Tick);
*/

	__END_CATCH
}

void EffectBloodyStorm::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectBloodyStorm::affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) 
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectBloodyStorm::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectBloodyStorm::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile(m_X, m_Y);
    tile.deleteEffect(m_ObjectID);

	__END_CATCH
}

void EffectBloodyStorm::unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObjbect)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectBloodyStorm::toString()
	
{
	__BEGIN_TRY

		StringStream msg;

	msg << "EffectBloodyStorm("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH
}

EffectBloodyStormLoader* g_pEffectBloodyStormLoader = NULL;
