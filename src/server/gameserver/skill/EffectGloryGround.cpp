//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRegeneration.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectGloryGround.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectGloryGround::EffectGloryGround( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y )
	
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = X;
	m_Y = Y;

	m_UserObjectID = 0;
	m_bSlayer = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGloryGround::affect()
	
{
	__BEGIN_TRY

	Assert( m_pZone != NULL );

	affect( m_pZone, m_X, m_Y );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGloryGround::affect(Zone* pZone, ZoneCoord_t Cx, ZoneCoord_t Cy)
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );

	VSRect rect( 0, 0, pZone->getWidth() - 1, pZone->getHeight() - 1 );

	GCSkillToSelfOK1 _GCSkillToSelfOK1;
	GCSkillToSelfOK2 _GCSkillToSelfOK2;

			int X = Cx;
			int Y = Cy;

			if ( !rect.ptInRect( X, Y ) ) return;

			// 타일안에 존재하는 오브젝트를 가져온다.
			Tile& tile = pZone->getTile( X, Y );

			const slist<Object*>& oList = tile.getObjectList();
			for ( slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++ )
			{
				Object* pTargetObject = (*itr);
				if ( pTargetObject != NULL
					&& pTargetObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
				{
					Creature* pCreature = dynamic_cast<Creature*>(pTargetObject);
					Assert( pCreature != NULL );

					// 코마가 걸려있거나 죽은 애는 치료 안해준다.
					// 2003. 3. 11. Sequoia
					if( pCreature->isSlayer() && !pCreature->isFlag(Effect::EFFECT_CLASS_COMA) && !pCreature->isDead() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

						HP_t CurrentHP	= pSlayer->getHP( ATTR_CURRENT );
						HP_t MaxHP		= pSlayer->getHP( ATTR_MAX	   );
						
						if ( CurrentHP < MaxHP )
						{
							HP_t RemainHP	= min((int)MaxHP, (int)CurrentHP + m_Damage);
							pSlayer->setHP(RemainHP, ATTR_CURRENT);

							GCModifyInformation gcMI;
							gcMI.addShortData( MODIFY_CURRENT_HP, RemainHP );
							pSlayer->getPlayer()->sendPacket( &gcMI );

							_GCSkillToSelfOK1.setSkillType( SKILL_CURE_EFFECT );
							_GCSkillToSelfOK1.setDuration( 0 );
							pSlayer->getPlayer()->sendPacket( &_GCSkillToSelfOK1 );

							_GCSkillToSelfOK2.setObjectID( pSlayer->getObjectID() );
							_GCSkillToSelfOK2.setSkillType( SKILL_CURE_EFFECT );
							_GCSkillToSelfOK2.setDuration( 0 );
							pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &_GCSkillToSelfOK2, pCreature );

							GCStatusCurrentHP gcStatusCurrentHP;
							gcStatusCurrentHP.setObjectID( pSlayer->getObjectID() );
							gcStatusCurrentHP.setCurrentHP( RemainHP );
							pZone->broadcastPacket( X, Y, &gcStatusCurrentHP );
						}
					}
					int PoisonDamage = computeMagicDamage(pCreature, m_Damage, SKILL_GLORYGROUND, m_bSlayer, pCastCreature);
					if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
						Assert(pVampire != NULL);
		
						GCModifyInformation gcMI;
						::setDamage( pVampire, PoisonDamage, pCastCreature, SKILL_GLORYGROUND, &gcMI );
			
						Player* pPlayer = pCreature->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcMI);
					}
					else if (pCreature->isOusters())
					{
					Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
					Assert(pOusters != NULL);
	
					GCModifyInformation gcMI;
					::setDamage( pOusters, PoisonDamage, pCastCreature, SKILL_GLORYGROUND, &gcMI );

					Player* pPlayer = pCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&gcMI);
					}
					else if (pCreature->isMonster())
					{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);
					Assert(pMonster != NULL);

					::setDamage( pMonster, PoisonDamage, pCastCreature, SKILL_GLORYGROUND );
					}
				}
	}

	setNextTime( m_Delay );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectGloryGround::unaffect()
	
{
	__BEGIN_TRY

	Tile& tile = m_pZone->getTile( m_X, m_Y );
	tile.deleteEffect( m_ObjectID );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectGloryGround::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectGloryGround("
		<< "Damage:" << (int)m_Damage
		<< ")";
	return msg.toString();

	__END_CATCH
}

