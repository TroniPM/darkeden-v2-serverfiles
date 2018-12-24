//////////////////////////////////////////////////////////////////////////////
// Filename    : SatelliteBomb.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SatelliteBomb2.h"
#include "EffectSatelliteBombAim2.h"
#include "EffectSatelliteBombPoint2.h"

#include "ItemUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// ���� ���Ǻ������ 180��
//////////////////////////////////////////////////////////////////////////////
void SatelliteBomb2::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
    throw(Error)
{
    __BEGIN_TRY

	// ���ݰ�ȫ��֤
	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

    try
    {
		// ��ȡ��ǰ��ͼ,�����а�ȫ��֤.����Ŀ��IDȡ�ö���
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		

		// ���Ŀ�깥��������
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC()
			)
		{
			// ֪ͨ�ͻ���ʹ�ü���ʧ��
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}
		// ʹ�ü���
		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    } 
	//������
	catch (Throwable & t)  
	{
		// ֪ͨ�ͻ���ʹ�ü���ʧ��
		executeSkillFailException(pSlayer, getSkillType());			
    }
    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �������к��� pSlayer->ʹ�ü��ܶ���  X,Y->���� pSkillSlot->������Ϣ  CEffectID->Ч��ID
//////////////////////////////////////////////////////////////////////////////
void SatelliteBomb2::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	try 
	{
		// ����Slayer ȡ��Player����ָ��
		Player* pPlayer = pSlayer->getPlayer();
		// ����Slayer ȡ�õ�ǰ��ͼָ��
		Zone* pZone = pSlayer->getZone();
		// ������
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// ����Ƿ���װ������
		Item* pItem = pSlayer->getWearItem( Slayer::WEAR_RIGHTHAND );
		if ( pItem == NULL || isArmsWeapon( pItem ) == false )
		{
			// ֪ͨ�ͻ���ʹ�ü���ʧ��
			executeSkillFailException( pSlayer, getSkillType() );
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;
		// ��ȡ��ǰʹ�ü�������
		SkillType_t SkillType  = pSkillSlot->getSkillType();
		// ��ȡ���ݿ⵱ǰʹ�ü�����Ϣ
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		
		// RequiredMP  ��ȡ������Ҫ���ĵ�MPֵ.
		// bManaCheck  ��⵱ǰʹ�ö����Ƿ����㹻��MPֵ����.
		// bTimeCheck  ��⵱ǰ����ʹ��ʱ�����Ƿ񳬳�.
		// bRangeCheck ��⼼��ʹ�þ���.
		// bEffected   ��⵱ǰ�����Ƿ���ʹ����.
		// bTileCheck  ��⵱ǰ��ͼʹ�ÿ�����
		int  RequiredMP  = pSkillInfo->getConsumeMP();										
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);								
		bool bTimeCheck  = verifyRunTime(pSkillSlot);										
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());           
		bool bEffected	 = pSlayer->isFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM2 ); 

		bool bTileCheck = false;
		VSRect rect( 0, 0, pZone->getWidth()-1, pZone->getHeight()-1 );
		if ( rect.ptInRect( X, Y ) )
		{
			Tile& tile = pZone->getTile(X,Y);
			if ( tile.canAddEffect() ) bTileCheck = true;
		}
		bool bUseSkill	 = false;
		/*
		// ȡ����ǰʹ�ü��ܽ�ɫ��ʹ�õ�����
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		//û����������ʹ�ü���
		if (pWeapon != NULL) 
		{
			Silver_t silverDamage= pWeapon->getSilver();
			if (silverDamage >50)
			{
				silverDamage-=50;
				pWeapon->setSilver(silverDamage);
				bUseSkill=true;
			}
		}
		*/
		// ���ȫ�����ͨ��,��ִ�м��ܺ���.
		if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected && bTileCheck)
		{
			// ����ʹ�ý�ɫMP����
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// �������������������,�����㼼���˺�����Ϣ.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Tile& tile = pZone->getTile( X, Y );

			// ���EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT����Ч����ʹ����,�Ƴ�Ч��.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT2);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// ����ʹ�ý�ɫЧ��
			EffectSatelliteBombAim2* pEffect = new EffectSatelliteBombAim2(pSlayer, pZone, X, Y);
			// ����Ч���˺�
			pEffect->setDamage(output.Damage);
			// ����Ч��ʹ��ʱ��
			pEffect->setDeadline(output.Duration);
			
			pSlayer->addEffect( pEffect );
			pSlayer->setFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM2 );

			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToTileOK1.setSkillType(SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setDuration(output.Duration);
			_GCSkillToTileOK1.setRange(output.Range);
		
			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(output.Range);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(output.Range);

			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			list<Creature*> cList;
			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// SatelliteBombAim ����Ʈ�� ��ε�ĳ���� �Ѵ�.
			GCAddEffect gcAddAimEffect;
			gcAddAimEffect.setObjectID( pSlayer->getObjectID() );
			gcAddAimEffect.setEffectID( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM2 );
			gcAddAimEffect.setDuration( output.Duration );
			pZone->broadcastPacket( myX, myY, &gcAddAimEffect );

			///////////////////////////////////////////////////////////////////
			// SatelliteBombPoint ����Ʈ�� ���� ���̰� ��ε�ĳ���� �Ѵ�.
			///////////////////////////////////////////////////////////////////
			EffectSatelliteBombPoint2* pPointEffect = new EffectSatelliteBombPoint2( pZone, X, Y );
			pPointEffect->setDeadline( output.Duration );

			ObjectRegistry & objectRegister = pZone->getObjectRegistry();
			objectRegister.registerObject( pPointEffect );

			pZone->addEffect( pPointEffect );
			tile.addEffect( pPointEffect );

			GCAddEffectToTile gcAddEffectToTile;
			gcAddEffectToTile.setObjectID( pPointEffect->getObjectID() );
			gcAddEffectToTile.setEffectID( pPointEffect->getEffectClass() );
			gcAddEffectToTile.setXY( X, Y );
			gcAddEffectToTile.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffectToTile );

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	__END_CATCH
}

void SatelliteBomb2::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error)
{
	__BEGIN_TRY

	try 
	{
		cout << pMonster->getName() << " use gunshotguiadance" << endl;
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		SkillType_t SkillType  = getSkillType();
		bool bTileCheck = false;
		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
		if (rect.ptInRect(X, Y))
		{
			Tile& tile = pZone->getTile(X, Y);
			if (tile.canAddEffect()) bTileCheck = true;
		}

		if (bTileCheck)
		{
			Tile& tile = pZone->getTile(X, Y);
		
			ZoneCoord_t myX = pMonster->getX();
			ZoneCoord_t myY = pMonster->getY();

			// ���� ����Ʈ�� �̹� �����Ѵٸ� �����Ѵ�.
			Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT2);
			if (pOldEffect != NULL)
			{
				ObjectID_t effectID = pOldEffect->getObjectID();
				pZone->deleteEffect(effectID);
			}

			// �������� ���� �ð��� ����Ѵ�.
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);
		
			// ����Ʈ ������Ʈ�� �����Ѵ�.
			EffectSatelliteBombAim2* pEffect = new EffectSatelliteBombAim2(pMonster, pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamage(output.Damage);

			pMonster->setFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM2 );
			pMonster->addEffect( pEffect );

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);
			
			_GCSkillToTileOK4.setSkillType(SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(output.Duration);
			_GCSkillToTileOK4.setRange(1);
		
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setDuration(output.Duration);
			_GCSkillToTileOK5.setRange(1);
	
			list<Creature*> cList;
			cList.push_back(pMonster);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// SatelliteBombAim ����Ʈ�� ��ε�ĳ���� �Ѵ�.
			GCAddEffect gcAddAimEffect;
			gcAddAimEffect.setObjectID( pMonster->getObjectID() );
			gcAddAimEffect.setEffectID( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM2 );
			gcAddAimEffect.setDuration( output.Duration );
			pZone->broadcastPacket( myX, myY, &gcAddAimEffect );

			EffectSatelliteBombPoint2* pPointEffect = new EffectSatelliteBombPoint2( pZone, X, Y );
			pPointEffect->setDeadline( output.Duration );

			ObjectRegistry & objectRegister = pZone->getObjectRegistry();
			objectRegister.registerObject( pPointEffect );

			pZone->addEffect( pPointEffect );
			tile.addEffect( pPointEffect );

			GCAddEffectToTile gcAddEffectToTile;
			gcAddEffectToTile.setObjectID( pPointEffect->getObjectID() );
			gcAddEffectToTile.setEffectID( pPointEffect->getEffectClass() );
			gcAddEffectToTile.setXY( X, Y );
			gcAddEffectToTile.setDuration( output.Duration );

			pZone->broadcastPacket( X, Y, &gcAddEffectToTile );
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	__END_CATCH
}

SatelliteBomb2 g_SatelliteBomb2;
