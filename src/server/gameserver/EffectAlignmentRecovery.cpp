//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAlignmentRecovery.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "EffectAlignmentRecovery.h"
#include "Zone.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Player.h"
#include "AlignmentManager.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCOtherModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAlignmentRecovery member methods
//////////////////////////////////////////////////////////////////////////////

EffectAlignmentRecovery::EffectAlignmentRecovery () 
	
{
	__BEGIN_TRY

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectAlignmentRecovery::EffectAlignmentRecovery (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pCreature , Turn_t delay) 
	
: Effect(pZone,x,y,pCreature,delay) 
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	Assert(pCreature != NULL);

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectAlignmentRecovery::~EffectAlignmentRecovery () 
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectAlignmentRecovery::affect()
	
{
	__BEGIN_TRY

	setNextTime(m_Delay);

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	Assert(pCreature != NULL);

	affect(pCreature);

	__END_CATCH
}

void EffectAlignmentRecovery::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	Timeval CurrentTime;
	getCurrentTime(CurrentTime);

	GCModifyInformation gcModifyInformation;

	Alignment_t CurrentAlignment = 0;
	Alignment_t NewAlignment = 0;

	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Assert(pSlayer != NULL);

		if (m_Period != 0) 
		{
			// �÷��� �ɱ�
			pSlayer->setFlag(Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY);

			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			CurrentAlignment = pSlayer->getAlignment();
			NewAlignment     = min(10000, (int)(CurrentAlignment + m_AlignmentQuantity));

			pSlayer->setAlignment(NewAlignment);

			gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
			pSlayer->getPlayer()->sendPacket( &gcModifyInformation );

			WORD AlignmentSaveCount = pSlayer->getAlignmentSaveCount();
			if (AlignmentSaveCount > ALIGNMENT_SAVE_PERIOD)
			{
				StringStream msg;
				msg << "Alignment = " << NewAlignment;
				pSlayer->tinysave(msg.toString());
				AlignmentSaveCount = 0;
			}
			else AlignmentSaveCount++;
			pSlayer->setAlignmentSaveCount(AlignmentSaveCount);
		} 
		else 
		{
			// unaffect�ϸ鼭 ��Ŷ�� ���ư� �״ϱ�....
			setDeadline(0);
		}

		m_Period--;
	}
	else if (pCreature->isVampire())
	{

		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		Assert(pVampire != NULL);

		if (m_Period != 0) 
		{
			// �÷��� �ɱ�
			pVampire->setFlag(Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY);

			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			CurrentAlignment = pVampire->getAlignment();
			NewAlignment     = min(10000, CurrentAlignment + m_AlignmentQuantity);

			pVampire->setAlignment(NewAlignment);

			gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
			pVampire->getPlayer()->sendPacket( &gcModifyInformation );

			WORD AlignmentSaveCount = pVampire->getAlignmentSaveCount();
			if (AlignmentSaveCount > ALIGNMENT_SAVE_PERIOD)
			{
				StringStream msg;
				msg << "Alignment = " << NewAlignment;
				pVampire->tinysave(msg.toString());
				AlignmentSaveCount = 0;
			}
			else AlignmentSaveCount++;
			pVampire->setAlignmentSaveCount(AlignmentSaveCount);
		} 
		else
		{
			// unaffect�ϸ鼭 ��Ŷ�� ���ư� �״ϱ�....
			setDeadline(0);
		}

		m_Period--;
	}
	else if (pCreature->isOusters())
	{

		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		Assert(pOusters != NULL);

		if (m_Period != 0) 
		{
			// �÷��� �ɱ�
			pOusters->setFlag(Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY);

			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			CurrentAlignment = pOusters->getAlignment();
			NewAlignment     = min(10000, CurrentAlignment + m_AlignmentQuantity);

			pOusters->setAlignment(NewAlignment);

			gcModifyInformation.addLongData(MODIFY_ALIGNMENT, NewAlignment);
			pOusters->getPlayer()->sendPacket( &gcModifyInformation );

			WORD AlignmentSaveCount = pOusters->getAlignmentSaveCount();
			if (AlignmentSaveCount > ALIGNMENT_SAVE_PERIOD)
			{
				StringStream msg;
				msg << "Alignment = " << NewAlignment;
				pOusters->tinysave(msg.toString());
				AlignmentSaveCount = 0;
			}
			else AlignmentSaveCount++;
			pOusters->setAlignmentSaveCount(AlignmentSaveCount);
		} 
		else
		{
			// unaffect�ϸ鼭 ��Ŷ�� ���ư� �״ϱ�....
			setDeadline(0);
		}

		m_Period--;
	}
	else
	{
		return;	// ū �ǹ̴� ������..
	}

	// ���� �ܰ谡 �ٲ�� �ٸ� ����鿡�Ե� �˷���� �Ѵ�.  by sigi. 2002.12.28

	Alignment beforeAlignment = g_pAlignmentManager->getAlignmentType(CurrentAlignment);
	Alignment afterAlignment = g_pAlignmentManager->getAlignmentType(NewAlignment);

	if (beforeAlignment!=afterAlignment)
	{
		GCOtherModifyInfo gcOtherModifyInfo;
		gcOtherModifyInfo.setObjectID(pCreature->getObjectID());
		gcOtherModifyInfo.addShortData(MODIFY_ALIGNMENT, NewAlignment);

		Zone* pZone = pCreature->getZone();	// 2003.1.10
		Assert(pZone!=NULL);
		
		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo, pCreature);
	}

	__END_CATCH
}

void EffectAlignmentRecovery::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

void EffectAlignmentRecovery::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	Assert(pCreature != NULL);
	unaffect(pCreature);

	__END_CATCH
}

void EffectAlignmentRecovery::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	
	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Assert(pSlayer != NULL);

		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		if (m_Period != 0) 
		{
			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			Alignment_t CurrentAlignment = pSlayer->getAlignment();
			Alignment_t NewAlignment     = min(10000, (int)(CurrentAlignment + m_AlignmentQuantity* m_Period));

			pSlayer->setAlignment(NewAlignment);

			WORD AlignmentSaveCount = pSlayer->getAlignmentSaveCount();
			if (AlignmentSaveCount == 10)
			{
				StringStream msg;
				msg << "Alignment = " << NewAlignment;
				pSlayer->tinysave(msg.toString());

				AlignmentSaveCount = 0;
			}
			else AlignmentSaveCount++;
			pSlayer->setAlignmentSaveCount(AlignmentSaveCount);
		} 

		// ���� Alignment�� ��ε�ĳ�����Ѵ�.
		// ���� ȸ���� �������� ���� �˸����� �Ѵ�.
		// �ڽſ��� ����
		GCModifyInformation gcModifyInformation;
		gcModifyInformation.addLongData(MODIFY_ALIGNMENT, pSlayer->getAlignment());
		pSlayer->getPlayer()->sendPacket(&gcModifyInformation);

		// �ֺ�������Ե� ���𰡸� ������� �Ѵ�.
		// ��Ŷ�� ���� �����߰���..
		pSlayer->removeFlag(Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY);
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		//Zone* pZone = pVampire->getZone();

		if (m_Period != 0) 
		{
			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			Alignment_t CurrentAlignment = pVampire->getAlignment();
			Alignment_t NewAlignment     = min(10000, (int)(CurrentAlignment + m_AlignmentQuantity* m_Period));

			WORD AlignmentSaveCount = pVampire->getAlignmentSaveCount();
			if (AlignmentSaveCount == 10)
			{
				StringStream msg;
				msg << "Alignment = " << NewAlignment;
				pVampire->tinysave(msg.toString());

				AlignmentSaveCount = 0;
			}
			else AlignmentSaveCount++;
			pVampire->setAlignmentSaveCount(AlignmentSaveCount);
		} 

		// ���� Alignment�� ��ε�ĳ�����Ѵ�.
		// ���� ȸ���� �������� ���� �˸����� �Ѵ�.
		// �ڽſ��� ����
		GCModifyInformation gcModifyInformation;
		gcModifyInformation.addLongData(MODIFY_ALIGNMENT, pVampire->getAlignment());
		pVampire->getPlayer()->sendPacket(&gcModifyInformation);

		// �ֺ�������Ե�..
		pVampire->removeFlag(Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY);
	}
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		//Zone* pZone = pOusters->getZone();

		if (m_Period != 0) 
		{
			// �� �Ͽ� �󸶳� ȸ�� ��ų ���ΰ�.
			Alignment_t CurrentAlignment = pOusters->getAlignment();
			Alignment_t NewAlignment     = min(10000, (int)(CurrentAlignment + m_AlignmentQuantity* m_Period));

			WORD AlignmentSaveCount = pOusters->getAlignmentSaveCount();
			if (AlignmentSaveCount == 10)
			{
				StringStream msg;
				msg << "Alignment = " << NewAlignment;
				pOusters->tinysave(msg.toString());

				AlignmentSaveCount = 0;
			}
			else AlignmentSaveCount++;
			pOusters->setAlignmentSaveCount(AlignmentSaveCount);
		} 

		// ���� Alignment�� ��ε�ĳ�����Ѵ�.
		// ���� ȸ���� �������� ���� �˸����� �Ѵ�.
		// �ڽſ��� ����
		GCModifyInformation gcModifyInformation;
		gcModifyInformation.addLongData(MODIFY_ALIGNMENT, pOusters->getAlignment());
		pOusters->getPlayer()->sendPacket(&gcModifyInformation);

		// �ֺ�������Ե�..
		pOusters->removeFlag(Effect::EFFECT_CLASS_ALIGNMENT_RECOVERY);
	}

	__END_CATCH
}

void EffectAlignmentRecovery::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectAlignmentRecovery::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	if (m_pZone) 
	{
		msg << "EffectAlignmentRecovery("
			<< "ZoneID:" << (int)m_pZone->getZoneID()
			<< ",X:"     << (int)getX()
			<< ",Y:"     << (int)getY();
	}

	if (m_pTarget)
	{
		msg << ",Target:" << m_pTarget->toString();
	}
	else
	{
		msg << ",Target:NULL";
	}

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
		<< "." << (int)m_Deadline.tv_usec
		<< ")";

	return msg.toString();

	__END_CATCH
}
