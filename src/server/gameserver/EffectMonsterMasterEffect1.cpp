//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGrandMasterSlayer.cpp
// Written by  : 쉭
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectMonsterMasterEffect1.h"
#include "Creature.h"
#include "Monster.h"
#include "Player.h"
#include "Zone.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectMonsterMasterEffect1::EffectMonsterMasterEffect1(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

Effect::EffectClass EffectMonsterMasterEffect1::getSendEffectClass() 
{
	Monster* pSlayer = dynamic_cast<Monster*>(m_pTarget);
	if ( pSlayer == NULL ) return getEffectClass();

	int level = pSlayer->getEffectClass();

	if ( level > 0 ) return (Effect::EffectClass)level;
	else return getEffectClass();

	cout << " 오오라 " << level << endl;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMonsterMasterEffect1::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect( pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMonsterMasterEffect1::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature->isMonster());

	cout << " 작동됨 " << getSendEffectClass() << "크리쳐 오브젝트 : " << pCreature->getObjectID() << endl;

	pCreature->setFlag(getSendEffectClass());

	// 주위에 뿌려준다.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pCreature->getObjectID());
	gcAddEffect.setEffectID(getSendEffectClass());
	gcAddEffect.setDuration(999999);
	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	__END_CATCH
}

void EffectMonsterMasterEffect1::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMonsterMasterEffect1::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//cout << "EffectMonsterMasterEffect1" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pCreature->removeFlag(getSendEffectClass());

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectMonsterMasterEffect1" << "unaffect END" << endl;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMonsterMasterEffect1::toString()
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectMonsterMasterEffect1("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
