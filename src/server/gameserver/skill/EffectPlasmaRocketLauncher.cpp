//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPlasmaRocketLauncher.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectPlasmaRocketLauncher.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPlasmaRocketLauncher::EffectPlasmaRocketLauncher(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPlasmaRocketLauncher::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect(pCreature);
	//cout << "EffectPlasmaRocketLauncher " << "begin begin" << endl;

//	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
//	affect(pCreature);

	//cout << "EffectPlasmaRocketLauncher " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPlasmaRocketLauncher::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Creature* pAttacker = pZone->getCreature( m_UserObjectID );

	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

	int cX = pCreature->getX();
	int cY = pCreature->getY();
	
	for( int x = -1; x <= 1; x++)
	{
		for(int y= -1; y <= 1; y++)
		{
			int X = cX + x;
			int Y = cY + y;

			if(!rect.ptInRect(X, Y)) continue;
			Tile& tile = pZone->getTile(X, Y);
			
			const slist<Object*>& oList = tile.getObjectList();
			slist<Object*>::const_iterator itr = oList.begin();
			for(; itr != oList.end(); itr++)
			{
				Assert(*itr != NULL);
				Object* pObject = *itr;
				Assert(pObject != NULL);

				if(pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					Creature* pCreature2 = dynamic_cast<Creature*>(pObject);
					Assert(pCreature2 != NULL);

					if ( pCreature2 != pCreature && pCreature2->isSlayer() ) continue;
	
					if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
						&& !pCreature2->isDead()
						&& !pCreature2->isFlag(Effect::EFFECT_CLASS_COMA)
						// �������� üũ. by sigi. 2002.9.5
						&& canAttack( pAttacker, pCreature2 )
					   )
					{
						GCModifyInformation gcMI, gcAttackerMI;
						setDamage( pCreature2, m_Point, pAttacker, SKILL_PLASMA_ROCKET_LAUNCHER, &gcMI, &gcAttackerMI );
						if ( pCreature2->isPC() ) pCreature2->getPlayer()->sendPacket( &gcMI );

						if (pAttacker!=NULL) 
						{
							computeAlignmentChange( pCreature2, m_Point, pAttacker, &gcMI, &gcAttackerMI );
							if ( pAttacker->isPC() )
							{ 
								if ( pAttacker->isSlayer() && !pCreature2->isSlayer() )
								{
									Slayer* pSlayer = dynamic_cast<Slayer*>(pAttacker);

									if ( pSlayer != NULL )
									{
										GCModifyInformation gcMI;
										shareAttrExp( pSlayer, m_Point, 1, 8, 1, gcAttackerMI );
									}
								}

								if ( pAttacker->isPC() ) pAttacker->getPlayer()->sendPacket( &gcAttackerMI );
							}
						}
					}

				}
				
			}
		}
	}

	setDeadline(0);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPlasmaRocketLauncher::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
//	unaffect(pCreature);

	if ( pCreature == NULL ) return;

	pCreature->removeFlag(Effect::EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect );				

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPlasmaRocketLauncher::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectPlasmaRocketLauncher("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

