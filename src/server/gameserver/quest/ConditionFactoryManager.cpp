////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFactoryManager.cpp 
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "ConditionFactoryManager.h"
#include "StringStream.h"

#include "ConditionAnsweredBy.h"
#include "ConditionAtFirst.h"
#include "ConditionTalkedBy.h"
#include "ConditionAnsweredBy.h"
#include "ConditionIdle.h"
#include "ConditionEveryTime.h"
#include "ConditionFlagOn.h"
#include "ConditionFlagOff.h"
#include "ConditionAttrComp.h"
#include "ConditionRaceComp.h"
#include "ConditionSameClan.h"
#include "ConditionPayPlay.h"
#include "ConditionEnterMasterLair.h"
#include "ConditionEnterCastle.h"
#include "ConditionEnterHolyLand.h"
#include "ConditionEnterCastleDungeon.h"
#include "ConditionHasQuest.h"
#include "ConditionHasInvenSpace.h"
#include "ConditionCanEnterPayZone.h"
#include "ConditionCanEnterBeginnerZone.h"
#include "ConditionCanWarpGate.h"
#include "ConditionCanEnterLevelWarZone.h"
#include "ConditionCanPetQuest.h"
#include "ConditionCanEnterEventZone.h"
#include "ConditionEffectFlag.h"
#include "ConditionCanEnterGDRLair.h"
#include "ConditionExistReinforce.h"
#include "ConditionSiegeDefenderSide.h"
#include "ConditionSiegeAttackerSide.h"
#include "ConditionNotGuildMember.h"
#include "ConditionIsGuildMember.h"
#include "ConditionPcHasItems.h"
#include "ConditionPcHasGold.h"
#include "ConditionPcHasEffect.h"
#include "ConditionCanEnterQuestZone.h"
#include "ConditionZoneHasMonster.h"
#include "ConditionPcHasParty.h"

#include "ConditionPcHasOriginalGold.h"
#include "ConditionPcHasOriginalItems.h"
////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
ConditionFactoryManager::ConditionFactoryManager () 
	throw ()
: m_Factories(NULL) , m_Size(Condition::CONDITION_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// ��������丮�迭�� �����Ѵ�.
	m_Factories = new ConditionFactory*[ m_Size ];
	
	// ���丮�� ���� �����͵��� NULL �� �ʱ�ȭ�Ѵ�.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
			
	__END_CATCH
}

	
////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
ConditionFactoryManager::~ConditionFactoryManager () 
	throw ()
{
	__BEGIN_TRY
		
	Assert(m_Factories != NULL);

	// ������ ��������丮���� �����Ѵ�.
	for (int i = 0 ; i < m_Size ; i ++) {
		if (m_Factories[i] != NULL) {
			delete m_Factories[i];
			m_Factories[i] = NULL;
		}
	}
	
	// ��������丮�迭�� �����Ѵ�.
	delete [] m_Factories;
	m_Factories = NULL;
			
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// ���ǵ� ��� ��������丮���� ���⿡ �߰��Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ConditionFactoryManager::init ()
	 
{
	__BEGIN_TRY
		
	addFactory(new ConditionAtFirstFactory());
	addFactory(new ConditionTalkedByFactory());
	addFactory(new ConditionIdleFactory());
	addFactory(new ConditionEveryTimeFactory());
	addFactory(new ConditionAnsweredByFactory());
	addFactory(new ConditionFlagOnFactory());
	addFactory(new ConditionFlagOffFactory());
	addFactory(new ConditionAttrCompFactory());
	addFactory(new ConditionRaceCompFactory());
	addFactory(new ConditionSameClanFactory());
	addFactory(new ConditionPayPlayFactory());
	addFactory(new ConditionEnterMasterLairFactory());
	addFactory(new ConditionEnterCastleFactory());
	addFactory(new ConditionEnterHolyLandFactory());
	addFactory(new ConditionEnterCastleDungeonFactory());
	addFactory(new ConditionHasQuestFactory());
	addFactory(new ConditionHasInvenSpaceFactory());
	addFactory(new ConditionCanEnterPayZoneFactory());
	addFactory(new ConditionCanEnterBeginnerZoneFactory());
	addFactory(new ConditionCanWarpGateFactory());
	addFactory(new ConditionCanEnterLevelWarZoneFactory());
	addFactory(new ConditionCanPetQuestFactory());
	addFactory(new ConditionCanEnterEventZoneFactory());
	addFactory(new ConditionEffectFlagFactory());
	addFactory(new ConditionCanEnterGDRLairFactory());
	addFactory(new ConditionExistReinforceFactory());
	addFactory(new ConditionSiegeDefenderSideFactory());
	addFactory(new ConditionSiegeAttackerSideFactory());
	addFactory(new ConditionNotGuildMemberFactory());
	addFactory(new ConditionIsGuildMemberFactory());
	addFactory(new ConditionCanEnterQuestZoneFactory());
	addFactory(new ConditionPcHasItemsFactory());
	addFactory(new ConditionPcHasGoldFactory());
	addFactory(new ConditionPcHasEffectFactory());
	addFactory(new ConditionZoneHasMonsterFactory());
	addFactory(new ConditionPcHasPartyFactory());
	addFactory(new ConditionPcHasOriginalItemsFactory());
	addFactory(new ConditionPcHasOriginalGoldFactory());
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// add condition factory to factories array
////////////////////////////////////////////////////////////////////////////////
void ConditionFactoryManager::addFactory (ConditionFactory * pFactory) 
	 
{
	__BEGIN_TRY
		
	Assert(pFactory != NULL);

	if (m_Factories[ pFactory->getConditionType() ] != NULL) 
	{
		StringStream msg;
		msg << "duplicate condition factories, " << pFactory->getConditionName() ;
		cout << msg.toString() << endl;
		throw Error(msg.toString());
	}
	
	// ��������丮�� ����Ѵ�.
	m_Factories[ pFactory->getConditionType() ] = pFactory;
			
	__END_CATCH
}

	
////////////////////////////////////////////////////////////////////////////////
// create condition object with condition type
////////////////////////////////////////////////////////////////////////////////
Condition * ConditionFactoryManager::createCondition (ConditionType_t conditionType) const
   
{
	__BEGIN_TRY

	if (conditionType >= m_Size || m_Factories[conditionType] == NULL) 
	{
		StringStream msg;
		msg << "condition factory [" << conditionType << "] not exist.";
		cout << msg.toString() << endl;
		throw Error(msg.toString());
	}

	return m_Factories[conditionType]->createCondition();
			
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get condition name with condition type
////////////////////////////////////////////////////////////////////////////////
string ConditionFactoryManager::getConditionName (ConditionType_t conditionType) const
   
{
	__BEGIN_TRY

	// ����� Ÿ���� ������ �Ѿ���� ���ؼ� Seg.Fault �� �߻����� �ʵ���.
	// �̷� ����ڴ� ���� ©��� �Ѵ�.
	if (conditionType >= m_Size || m_Factories[conditionType] == NULL) 
	{
		StringStream msg;
		msg << "invalid condition type (" << conditionType << ")";
		cout << msg.toString() << endl;
		throw Error(msg.toString());
	}

	return m_Factories[conditionType]->getConditionName();
			
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
ConditionType_t ConditionFactoryManager::getConditionType (const string & conditionname) const
	
{
	__BEGIN_TRY

#ifdef __OUTPUT_INIT__
	cout << "Condition[" << conditionname << "]...";
#endif

	for (int i = 0 ; i < m_Size ; i ++)
	{
		if (m_Factories[i] != NULL)
		{
			if (m_Factories[i]->getConditionName() == conditionname)
			{
				return i;
			}
		}
	}

	string msg = "no such condition type : " + conditionname;
	cout << msg << endl;
	throw Error(msg);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionFactoryManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ConditionFactoryManager(\n";

	for (int i = 0 ; i < m_Size ; i ++)
	{
		msg << "ConditionFactories[" << i << "] == ";
		msg << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getConditionName()) ;
		msg << "\n";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable declaration
ConditionFactoryManager * g_pConditionFactoryManager = NULL;
