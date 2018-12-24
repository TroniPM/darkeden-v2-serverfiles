//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.cpp
// Written by  : ��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHasPet.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "PetInfo.h"
#include "CreatureUtil.h"
#include "PetExpInfo.h"
#include "PetUtil.h"
#include "types/PetTypes.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCModifyInformation.h"
#include "PetItem.h"
#include "VSDateTime.h"
#include "VariableManager.h"

#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasPet::EffectHasPet(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasPet::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasPet::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL || !pCreature->isPC() ) return;

	VSDateTime currentTime = VSDateTime::currentDateTime();
	setNextTime(600);
	setDeadline(999999);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	//cout << pPC->getName() << " �� ���� ��������� �ƽ��ϴ�." << endl;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
	Assert( pGamePlayer != NULL );

	list<PetItem*>::iterator itr = pPC->getPetItems().begin();
	list<PetItem*>::iterator endItr = pPC->getPetItems().end();

	for ( ; itr != endItr ; ++itr )
	{
		PetItem* pPetItem = *itr;
		if ( pPetItem == NULL ) continue;

		PetInfo* pPetInfo = pPetItem->getPetInfo();

		//cout << pPC->getName() << " �� ���� " << pPetItem->getObjectID() << " �� ���� ��Խ��ϴ�." << pPetInfo->getPetHP() << endl;

		if ( pPetInfo == NULL )
		{
			filelog( "PetBug.log", "EffectHasPet ���ư��µ� ���� ���� : %s", pPC->getName().c_str() );
			continue;
		}

		PetHP_t PetHP = pPetInfo->getPetHP();
		if ( PetHP == 0 )
		{
			continue;
		}

		int secsLast = pPetInfo->getLastFeedTime().secsTo(currentTime);
//		if ( secsLast > 70 )
//		{
//			filelog( "PetBug.log", "���� ��Դµ� 70�� �Ѱ� �ɷȴ�. %d�� : %s", secsLast, pPC->getName().c_str() );
//		}

		// 50���� ���� 10�п� �ѹ��� ��Դ´�.
		if ( pPetInfo->getEnchantSkillType() != 3 && pPetInfo->getPetLevel() == 50 && secsLast < 600 ) continue;
		if( pPetInfo->getEnchantSkillType() == 3 && pPetInfo->getPetLevel() == 50 && secsLast < 600*2){
		continue;
		}	
		if( pPetInfo->getEnchantSkillType() == 3 && secsLast < 600){
		continue;
		}	
		pPetInfo->setCurrentFeedTurn( pPetInfo->getCurrentFeedTurn() + 1 );

		// ���� ����δ�.
		if ( pPetInfo->getCurrentFeedTurn() >= pPetInfo->getFeedTurn() )
		{
			pPetInfo->setCurrentFeedTurn(0);

			pPetInfo->setPetHP( PetHP-1 );
			pPetInfo->setFeedTime( currentTime );

			if ( pPetInfo->getPetHP() == 0 )
			{
				filelog( "Pet.log", "%s�� ���� �׾���.", pPC->getName().c_str() );
				//cout << pPC->getName() << "�� ���� �׾���" << endl;
				if ( pPC->getPetInfo() == pPetInfo )
				{
					pPC->setPetInfo(NULL);
					pPC->initAllStatAndSend();
					sendPetInfo( pGamePlayer, true, false );
				}
			}
		}

		if ( pPC->getPetInfo() == pPetInfo )
		{

			PetExp_t exp = 20;
			if( pCreature->isFlag(Effect::EFFECT_CLASS_PET_EXP1)) exp *= 3;
			if ( !pGamePlayer->isPayPlaying() ) exp = 12;

			exp = getPercentValue( exp, g_pVariableManager->getPetExpRatio() );

			if ( increasePetExp( pPetInfo, exp ) )
			{
				sendPetInfo( pGamePlayer, true, false );
			}
			else
			{
				GCModifyInformation gcMI;
				gcMI.addLongData( MODIFY_PET_EXP, pPetInfo->getPetExp() );
				gcMI.addShortData( MODIFY_PET_HP, pPetInfo->getPetHP() );

				pGamePlayer->sendPacket( &gcMI );
			}

			addOlympicStat( pPC, 8, exp );
		}

		char query[100];
		sprintf(query, "PetHP=%u, LastFeedTime='%s', PetExp=%u", pPetInfo->getPetHP(), currentTime.toDateTime().c_str(), pPetInfo->getPetExp());
		pPetInfo->getPetItem()->tinysave(query);
	}

	__END_CATCH
}

void EffectHasPet::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasPet::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectHasPet" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	//cout << "EffectHasPet ����ϴ�." << endl;

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pCreature->removeFlag(Effect::EFFECT_CLASS_HAS_PET);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HAS_PET);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectHasPet" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHasPet::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHasPet("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
