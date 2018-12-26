//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicTable.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRelicTable.h"
#include "Item.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRelicTable::EffectRelicTable(Item* pItem)
	
{
	__BEGIN_TRY

	m_SafeTime.tv_sec = 0;
	m_SafeTime.tv_usec = 0;

	m_LockTime.tv_sec = 0;
	m_LockTime.tv_usec = 0;

	setTarget(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicTable::affect()
	
{
	__BEGIN_TRY

	Item* pItem = dynamic_cast<Item*>(m_pTarget);
	affect(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicTable::affect(Item* pItem)
	
{
	__BEGIN_TRY

	__END_CATCH
}

void EffectRelicTable::unaffect() 
	
{
	__BEGIN_TRY	

    Item* pItem = dynamic_cast<Item *>(m_pTarget);
	unaffect(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicTable::unaffect(Item* pItem)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	/*
	//cout << "EffectRelicTable" << "unaffect BEGIN" << endl;

	Assert(pItem != NULL);

	// �ɷ�ġ�� ���������� �ǵ����� ���ؼ��� �÷��׸� ����,
	// initAllStat�� �ҷ��� �Ѵ�.
	pItem->removeFlag(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);

	Zone* pZone = pItem->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pItem->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);
	pZone->broadcastPacket(pItem->getX(), pItem->getY(), &gcRemoveEffect);

	//cout << "EffectRelicTable" << "unaffect END" << endl;
	*/
	pItem->removeFlag( getEffectClass() );

	__END_DEBUG
	__END_CATCH
}

// SafeTime �� ������ �ʾ����� ������ ���� �� ����.
bool EffectRelicTable::isSafeTime() const
{
	Timeval currentTime;
	getCurrentTime( currentTime );

	return currentTime > m_SafeTime;
}

// LockTime ������ ������ ���� �� ����.
bool EffectRelicTable::isLockTime() const
{
	Timeval currentTime;
	getCurrentTime( currentTime );

	return currentTime < m_LockTime;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRelicTable::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRelicTable("
		<< "SafeTime:" << m_SafeTime.tv_sec
		<< ")";
	return msg.toString();

	__END_CATCH
}
