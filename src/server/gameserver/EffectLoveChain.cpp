//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoveChain.cpp
// Written by  : elca
// Description : 
// ���α�� Sniping �Ǵ� �����̾� ��� Invisibility�� ���ؼ�
// ���� ���� ����������� �ִ�(������� �ִ�) ũ���Ŀ� �ٴ� ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "EffectLoveChain.h"
#include "Slayer.h"
#include "Vampire.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "CreatureUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCUseOK.h"
#include "Gpackets/GCCannotUse.h"
#include "GDRLairManager.h"
#include "Store.h"
#include "GQuestManager.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectLoveChain::EffectLoveChain(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//setTarget(pCreature);

	m_OwnerOID = pCreature->getObjectID();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoveChain::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoveChain::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	
	//cout << "EffectLoveChain " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// ����Ʈ �÷��װ� ���ٸ� �׾��ٰų� �ϴ� ������ transport ���� �ʰڴٴ°� �ǹ��Ѵ�.
	if ( !pCreature->isFlag( Effect::EFFECT_CLASS_LOVE_CHAIN ) )
		return;

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Player* pPlayer = pCreature->getPlayer();
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	ZoneCoord_t x = pCreature->getX();
	ZoneCoord_t y = pCreature->getY();
	pCreature->removeFlag(Effect::EFFECT_CLASS_LOVE_CHAIN);

	// Effect �� ���������� �˸���.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_LOVE_CHAIN );
	pZone->broadcastPacket( x, y, &gcRemoveEffect );

	// Target �� üũ�ؼ� ������ �����ϸ� �����Ѵ�.
	bool bValid = false;

	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED( m_TargetName );
	if ( pTargetCreature != NULL )
	{
		Zone* pTargetZone = pTargetCreature->getZone();
		if ( pTargetZone != NULL )
		{
			// ������ ����δ� �̵��� �� ����.
			if ( !pTargetZone->isMasterLair() && !GDRLairManager::Instance().isGDRLairZone( pTargetZone->getZoneID() ) )
			{
				// ���� ���� �̿��� �����Ѱ�?
				if ( pGamePlayer->loginPayPlay( pGamePlayer->getSocket()->getHost(), pGamePlayer->getID() )
					|| !( g_pZoneInfoManager->getZoneInfo( pTargetZone->getZoneID() )->isPayPlay() ) )
				{
					if ( !pTargetCreature->isPC() || !(dynamic_cast<PlayerCreature*>(pTargetCreature)->getStore()->isOpen()) )
					{
						// ������ɺ�, �ÿܰ�����, �̺�Ʈ�����, �̺�ƮOX �����δ� �� �� ����.
						if ( pTargetZone->getZoneID() != 2101 && pTargetZone->getZoneID() != 2102 &&
							 pTargetZone->getZoneID() != 1005 && pTargetZone->getZoneID() != 1006 &&
							 pTargetZone->getZoneID() != 1131 &&
							 pTargetZone->getZoneID() != 1132 && pTargetZone->getZoneID() != 1133 &&
							 pTargetZone->getZoneID() != 1134 && ( pTargetZone->getZoneID() != 1122 || canEnterBeginnerZone( pCreature ) ) &&
							 !pTargetZone->isCastleZone() &&  !pTargetZone->isDynamicZone()
						)
						{
							bValid = true;

							if ( pCreature->isSlayer() )
							{
								Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
								Assert( pSlayer != NULL );

								if ( pSlayer->hasRideMotorcycle() )
								{
									pSlayer->getOffMotorcycle();
								}
							}

							pPC->getGQuestManager()->illegalWarp();
							transportCreature( pCreature, pTargetZone->getZoneID(), pTargetCreature->getX(), pTargetCreature->getY(), false );
						}
					}
				}
			}
		}
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

	if ( !bValid )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID( m_ItemObjectID );
		pGamePlayer->sendPacket(&_GCCannotUse);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLoveChain::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	if ( m_pZone != NULL )
	{
		Creature* pCreature = m_pZone->getCreature( m_OwnerOID );
		if ( pCreature != NULL )
			unaffect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectLoveChain::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectLoveChain("
		<< "ObjectID:" << getObjectID()
		<< "TargetName:" << m_TargetName
		<< ")";
	return msg.toString();

	__END_CATCH
}

