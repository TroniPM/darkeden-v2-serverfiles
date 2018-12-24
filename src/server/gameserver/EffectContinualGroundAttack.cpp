//----------------------------------------------------------------------
//
// Filename    : EffectContinualGroundAttack.cpp
// Written by  : elca
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectContinualGroundAttack.h"
#include "EffectGroundAttack.h"
#include "EffectMeteorStrike.h"
#include "MonsterManager.h"
#include "PCManager.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "SkillUtil.h"
#include "Gpackets/GCAddEffectToTile.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectContinualGroundAttack::EffectContinualGroundAttack (Zone* pZone , EffectClass attackEffect, Turn_t delay) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pZone!=NULL);

	m_pZone = pZone;

	m_AttackEffect = attackEffect;

	m_Delay = delay;

	setNextTime(10);	// 1�� �� ����
	setDeadline(delay);

	m_MinNumber = 1;
	m_MaxNumber = 1;

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectContinualGroundAttack::~EffectContinualGroundAttack () 
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectContinualGroundAttack::affect()
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pZone!=NULL);

	int creatureNum = m_pZone->getPCManager()->getSize()
						+ m_pZone->getMonsterManager()->getSize();

	// ���ϸ� �����̶� ���̱� ���ؼ�..
	// ���� ���ݹ��� ĳ���Ͱ� �־���� effect�� ������..
	if (creatureNum > 0)
	{
		// zone�� Ư�� ��ġ�� effect�� ����ϰ� damage�� �ش�.
		int range = min(100, (m_MaxNumber-m_MinNumber));		// ���ÿ� 1~100����
		int number = (range>0? m_MinNumber + rand()%range : m_MinNumber);

		cout << "EffectContinualGroundAttack: " << (int)m_pZone->getZoneID() << ", num= " << number << endl;

		VSRect rect(0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1);
cout << "test " << endl;
		// m_MinNumber ~ m_MaxNumber ���� ����
		for (int i=0; i<number; i++)
		{
cout << "test start " << endl;
			const BPOINT& pt = m_pZone->getRandomEmptyTilePosition();

			if (!rect.ptInRect(pt.x, pt.y)) continue;
cout << "test start 2" << endl;
			// �߽� Ÿ�� üũ
			Tile& tile = m_pZone->getTile(pt.x, pt.y);

			int X = pt.x;
			int Y = pt.y;
cout << "test start 3" << endl;
			if (!tile.canAddEffect()) continue;

			int	DamagePercent = 100;
		
			// ����Ʈ ������Ʈ�� �����Ѵ�.
			Effect* pAttackEffect = NULL;
cout << "test 1" << endl;
			switch (m_AttackEffect)
			{
				case EFFECT_CLASS_GROUND_ATTACK :
				{
					// ���� ����Ʈ�� �̹� �����Ѵٸ� �� �� damage�� �����Ѵ�.
					Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_GROUND_ATTACK);
					if (pOldEffect != NULL)
					{
						EffectGroundAttack* pGAEffect = dynamic_cast<EffectGroundAttack*>(pOldEffect);
						pGAEffect->setDamagePercent( max(DamagePercent, pGAEffect->getDamagePercent()) );
						continue;
					}

					EffectGroundAttack* pEffect = new EffectGroundAttack(m_pZone, X, Y);
					pEffect->setDeadline( 22 ); // 2��+����
					pEffect->setDamagePercent( DamagePercent );

					pAttackEffect = pEffect;
				}
				break;

				case EFFECT_CLASS_METEOR_STRIKE :
				{
					// ���� ����Ʈ�� �ִٸ� �����Ѵ�.
					Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_METEOR_STRIKE);
					if ( pOldEffect != NULL )
					{
						ObjectID_t effectID = pOldEffect->getObjectID();
						m_pZone->deleteEffect(effectID);
					}

					EffectMeteorStrike* pEffect = new EffectMeteorStrike(m_pZone, X, Y);
					pEffect->setDeadline( 10 ); // 1��

					// 400 ~ 600 100%
					// 200 ~ 300 50%
					// 100 ~ 150 25%
					pEffect->setDamage( 400+rand()%200 );

					pAttackEffect = pEffect;
				}
				break;

				default :
				break;
			}

cout << "test 2" << endl;
			if (pAttackEffect!=NULL)
			{
				// Ÿ�Ͽ� ���� ����Ʈ�� OID�� �޾ƾ� �Ѵ�.
				ObjectRegistry & objectregister = m_pZone->getObjectRegistry();
				objectregister.registerObject(pAttackEffect);
			cout << "test 3" << endl;
				// �� �� Ÿ�Ͽ��ٰ� ����Ʈ�� �߰��Ѵ�.
				m_pZone->addEffect(pAttackEffect);	
				tile.addEffect(pAttackEffect);

				// ������� ����Ʈ�� �����ش�.
				GCAddEffectToTile gcAddEffectToTile;
				gcAddEffectToTile.setEffectID( pAttackEffect->getEffectClass() );
				gcAddEffectToTile.setObjectID( pAttackEffect->getObjectID());
				gcAddEffectToTile.setXY(X, Y);
				gcAddEffectToTile.setDuration( 20 );	// 2��

				m_pZone->broadcastPacket(X, Y, &gcAddEffectToTile);
			}
		}
	}

	setNextTime(m_Delay);
	
	__END_CATCH
}

//--------------------------------------------------------------------
// unaffect()
//--------------------------------------------------------------------
void EffectContinualGroundAttack::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectContinualGroundAttack::toString () const 
	throw ()
{
	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectContinualGroundAttack("
				<< "ZoneID:" << (int)m_pZone->getZoneID();
	}

	msg << ",Delay:" << (int)m_Delay
		<< ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec
			<< ")";

	return msg.toString();
}
