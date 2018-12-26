////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionFactoryManager.cpp 
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "ActionFactoryManager.h"
#include "StringStream.h"

#include "ActionSetPosition.h"
#include "ActionWander.h"
#include "ActionSay.h"
#include "ActionRandomSay.h"
#include "ActionAsk.h"
#include "ActionQuitDialogue.h"
#include "ActionPrepareShop.h"
#include "ActionSell.h"
#include "ActionBuy.h"
#include "ActionRegenShop.h"
#include "ActionTeachSkill.h"
#include "ActionHeal.h"
#include "ActionRedeemMotorcycle.h"
#include "ActionSearchMotorcycle.h"
#include "ActionRepair.h"
#include "ActionStashSell.h"
#include "ActionStashOpen.h"
#include "ActionRestore.h"
#include "ActionSetResurrectZone.h"
#include "ActionSilverCoating.h"
#include "ActionCreateGuild.h"
#include "ActionDestroyGuild.h"
#include "ActionTutorial.h"
#include "ActionGiveNewbieItem.h"
#include "ActionActivatePortal.h"
#include "ActionTurnOnFlag.h"
#include "ActionTurnOffFlag.h"
#include "ActionSystemMessage.h"
#include "ActionSystemMessagePerRace.h"
#include "ActionTakeDonation.h"
#include "ActionCallHelicopter.h"
#include "ActionRegenEventShop.h"
#include "ActionAskDynamic.h"
#include "ActionSayDynamic.h"
#include "ActionGiveSpecialEventItem.h"
#include "ActionRedistributeAttr.h"
#include "ActionTradeEventItem.h"
#include "ActionTradeLairItem.h"
#include "ActionShowGuildDialog.h"
#include "ActionSimpleQuestList.h"
#include "ActionSimpleQuestComplete.h"
#include "ActionSimpleQuestRegen.h"
#include "ActionTradeGiftBox.h"
#include "ActionGiveTestServerReward.h"
#include "ActionEnterCastleWithFee.h"
#include "ActionShowTaxBalance.h"
#include "ActionAskVariable.h"
#include "ActionWarRegistration.h"
#include "ActionShowWarSchedule.h"
#include "ActionJoinRaceWar.h"
#include "ActionGiveEventItem.h"
#include "ActionGiveAccountEventItem.h"
#include "ActionInitPartnerWaitingManager.h"
#include "ActionWaitForMeetCouple.h"
#include "ActionWaitForApartCouple.h"
#include "ActionAcceptCoupleRequest.h"
#include "ActionAcceptApartCouple.h"
#include "ActionForceApartCouple.h"
#include "ActionEnterPKZone.h"
#include "ActionWarpToResurrectPosition.h"
#include "ActionSelectQuest.h"
#include "ActionQuestReward.h"
#include "ActionWarpToNoviceZone.h"
#include "ActionCancelQuest.h"
#include "ActionInitSimpleQuest.h"
#include "ActionWanderZone.h"
#include "ActionInitEventQuest.h"
#include "ActionAskByQuestLevel.h"
#include "ActionGiveEventQuest.h"
#include "ActionAdvanceEventQuest.h"
#include "ActionRewardEventQuest.h"
#include "ActionCancelEventQuestScript.h"
#include "ActionGiveLotto.h"
#include "ActionGiveEventQuestScript.h"
#include "ActionStartEventQuest.h"
#include "ActionWarpInZone.h"
#include "ActionEventMeet.h"
#include "ActionGiveFinalLottoScript.h"
#include "ActionGiveQuestItem.h"
#include "ActionTakeOutGoods.h"
#include "ActionClearRankBonus.h"
#include "ActionContractGnomesHorn.h"
#include "ActionDownSkill.h"
#include "ActionMiniGame.h"
#include "ActionGiveItem.h"
#include "ActionActivateMazeExit.h"
#include "ActionActivateMazeEnter.h"
#include "ActionActivateMazeReturn.h"
#include "ActionWarpLevelWarZone.h"
#include "ActionCheckPartnerName.h"
#include "ActionStartPetQuest.h"
#include "ActionEnterInstant.h"
#include "ActionPetDeposit.h"
#include "ActionPetWithdraw.h"

#include "ActionEnterEventZone.h"
#include "ActionEnterGDRLair.h"
#include "ActionTradeGQuestEventItem.h"
#include "ActionRegisterSiege.h"
#include "ActionRegisterReinforce.h"
#include "ActionAcceptReinforce.h"
#include "ActionDenyReinforce.h"
#include "ActionEnterSiege.h"
#include "ActionRecallSiege.h"
#include "ActionSelectBloodBible.h"
#include "ActionClearBloodBible.h"
#include "ActionModifyTaxRatio.h"
#include "ActionSwapAdvancementItem.h"
#include "ActionShowDonationDialog.h"
#include "ActionEnterQuestZone.h"
#include "ActionShowConfirmGetEventItemDialog.h"
#include "ActionPcGetItem.h"
#include "ActionCreateGetItem.h"
#include "ActionDeleteGetItem.h"
#include "ActionCreateGetGold.h"
#include "ActionDeleteGetGold.h"
#include "ActionCreateGetItemRand.h"
#include "ActionHeightTeachSkill.h"
#include "ActionSummonMonster.h"
#include "ActionEnterInstantExit.h"
#include "ActionCreateEffect.h"
#include "ActionCreateNotEffect.h"

#include "ActionOriginalDeleteGetGold.h"
#include "ActionOriginalDeleteGetItem.h"
////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
ActionFactoryManager::ActionFactoryManager () 
	throw ()
: m_Factories(NULL) , m_Size(Action::ACTION_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// �׼����丮�迭�� �����Ѵ�.
	m_Factories = new ActionFactory*[ m_Size ];
	
	// ���丮�� ���� �����͵��� NULL �� �ʱ�ȭ�Ѵ�.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
			
	__END_CATCH
}

	
////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
ActionFactoryManager::~ActionFactoryManager () 
	throw ()
{
	__BEGIN_TRY
		
	Assert(m_Factories != NULL);

	// ������ �׼����丮���� �����Ѵ�.
	for (int i = 0 ; i < m_Size ; i ++) {
		if (m_Factories[i] != NULL) {
			delete m_Factories[i];
			m_Factories[i] = NULL;
		}
	}
	
	// �׼����丮�迭�� �����Ѵ�.
	delete [] m_Factories;
	m_Factories = NULL;
			
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// ���ǵ� ��� �׼����丮���� ���⿡ �߰��Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionFactoryManager::init ()
	 
{
	__BEGIN_TRY
		
	addFactory(new ActionSetPositionFactory());
	addFactory(new ActionWanderFactory());
	addFactory(new ActionSayFactory());
	addFactory(new ActionRandomSayFactory());
	addFactory(new ActionAskFactory());
	addFactory(new ActionQuitDialogueFactory());
	addFactory(new ActionPrepareShopFactory());
	addFactory(new ActionSellFactory());
	addFactory(new ActionBuyFactory());
	addFactory(new ActionRegenShopFactory());
	addFactory(new ActionTeachSkillFactory());
	addFactory(new ActionHealFactory());
	addFactory(new ActionRedeemMotorcycleFactory());
	addFactory(new ActionSearchMotorcycleFactory());
	addFactory(new ActionRepairFactory());
	addFactory(new ActionStashSellFactory());
	addFactory(new ActionStashOpenFactory());
	addFactory(new ActionRestoreFactory());
	addFactory(new ActionSetResurrectZoneFactory());
	addFactory(new ActionSilverCoatingFactory());
	addFactory(new ActionCreateGuildFactory());
	addFactory(new ActionDestroyGuildFactory());
	addFactory(new ActionTutorialFactory());
	addFactory(new ActionGiveNewbieItemFactory());
	addFactory(new ActionActivatePortalFactory());
	addFactory(new ActionTurnOnFlagFactory());
	addFactory(new ActionTurnOffFlagFactory());
	addFactory(new ActionSystemMessageFactory());
	addFactory(new ActionTakeDonationFactory());
	addFactory(new ActionCallHelicopterFactory());
	addFactory(new ActionRegenEventShopFactory());
	addFactory(new ActionAskDynamicFactory());
	addFactory(new ActionSayDynamicFactory());
	addFactory(new ActionGiveSpecialEventItemFactory());
	addFactory(new ActionRedistributeAttrFactory());
	addFactory(new ActionTradeEventItemFactory());
	addFactory(new ActionTradeLairItemFactory());
	addFactory(new ActionShowGuildDialogFactory());
	addFactory(new ActionSimpleQuestListFactory());
	addFactory(new ActionSimpleQuestCompleteFactory());
	addFactory(new ActionSimpleQuestRegenFactory());
	addFactory(new ActionTradeGiftBoxFactory());
	addFactory(new ActionGiveTestServerRewardFactory());
	addFactory(new ActionEnterCastleWithFeeFactory());
	addFactory(new ActionShowTaxBalanceFactory());
	addFactory(new ActionAskVariableFactory());
	addFactory(new ActionWarRegistrationFactory());
	addFactory(new ActionShowWarScheduleFactory());
	addFactory(new ActionJoinRaceWarFactory());
	addFactory(new ActionGiveEventItemFactory());
	addFactory(new ActionGiveAccountEventItemFactory());

	addFactory(new ActionInitPartnerWaitingManagerFactory());
	addFactory(new ActionWaitForMeetCoupleFactory());
	addFactory(new ActionWaitForApartCoupleFactory());
	addFactory(new ActionAcceptCoupleRequestFactory());
	addFactory(new ActionAcceptApartCoupleFactory());
	addFactory(new ActionForceApartCoupleFactory());
	addFactory(new ActionEnterPKZoneFactory());
	addFactory(new ActionWarpToResurrectPositionFactory());
	addFactory(new ActionSelectQuestFactory());
	addFactory(new ActionQuestRewardFactory());
	addFactory(new ActionWarpToNoviceZoneFactory());
	addFactory(new ActionCancelQuestFactory());
	addFactory(new ActionInitSimpleQuestFactory());
	addFactory(new ActionWanderZoneFactory());
	addFactory(new ActionInitEventQuestFactory());
	addFactory(new ActionGiveEventQuestFactory());
	addFactory(new ActionAdvanceEventQuestFactory());
	addFactory(new ActionRewardEventQuestFactory());
	addFactory(new ActionCancelEventQuestScriptFactory());
	addFactory(new ActionGiveLottoFactory());
	addFactory(new ActionAskByQuestLevelFactory());
	addFactory(new ActionGiveEventQuestScriptFactory());
	addFactory(new ActionStartEventQuestFactory());
	addFactory(new ActionWarpInZoneFactory());
	addFactory(new ActionEventMeetFactory());
	addFactory(new ActionGiveFinalLottoScriptFactory());
	addFactory(new ActionGiveQuestItemFactory());
	addFactory(new ActionTakeOutGoodsFactory());
	addFactory(new ActionClearRankBonusFactory());
	addFactory(new ActionContractGnomesHornFactory());
	addFactory(new ActionDownSkillFactory());
	addFactory(new ActionMiniGameFactory());
	addFactory(new ActionGiveItemFactory());
	addFactory(new ActionActivateMazeExitFactory());
	addFactory(new ActionActivateMazeEnterFactory());
	addFactory(new ActionActivateMazeReturnFactory());
	addFactory(new ActionSystemMessagePerRaceFactory());
	addFactory(new ActionWarpLevelWarZoneFactory());
	addFactory(new ActionCheckPartnerNameFactory());
	addFactory(new ActionStartPetQuestFactory());

	addFactory(new ActionPetDepositFactory());
	/* �� ������ : �׼����� PetDeposit�� ����� �Ѵ�. Withdraw�� ���� �ʴ´�. */
	/* 2004�� 5�� 13�� - �¸�, ��� */
	/* addFactory(new ActionPetWithdrawFactory());	*/

	addFactory(new ActionEnterEventZoneFactory());
	addFactory(new ActionEnterGDRLairFactory());
	addFactory(new ActionTradeGQuestEventItemFactory());
	addFactory(new ActionRegisterSiegeFactory());
	addFactory(new ActionRegisterReinforceFactory());
	addFactory(new ActionAcceptReinforceFactory());
	addFactory(new ActionDenyReinforceFactory());
	addFactory(new ActionEnterSiegeFactory());
	addFactory(new ActionRecallSiegeFactory());
	addFactory(new ActionSelectBloodBibleFactory());
	addFactory(new ActionClearBloodBibleFactory());
	addFactory(new ActionModifyTaxRatioFactory());
	addFactory(new ActionSwapAdvancementItemFactory());
	addFactory(new ActionShowDonationDialogFactory());
	addFactory(new ActionEnterQuestZoneFactory());
	addFactory(new ActionShowConfirmGetEventItemDialogFactory());
	addFactory(new ActionPcGetItemFactory());
	addFactory(new ActionEnterInstantFactory());
	addFactory(new ActionCreateGetItemFactory());
	addFactory(new ActionDeleteGetItemFactory());
	addFactory(new ActionCreateGetGoldFactory());
	addFactory(new ActionDeleteGetGoldFactory());
	addFactory(new ActionCreateGetItemRandFactory());
	addFactory(new ActionHeightTeachSkillFactory());
	addFactory(new ActionSummonMonsterFactory());
	addFactory(new ActionEnterInstantExitFactory());
	addFactory(new ActionCreateEffectFactory());
	addFactory(new ActionCreateNotEffectFactory());
	addFactory(new ActionOriginalDeleteGetItemFactory());
	addFactory(new ActionOriginalDeleteGetGoldFactory());
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// add condition factory to factories array
////////////////////////////////////////////////////////////////////////////////
void ActionFactoryManager::addFactory (ActionFactory * pFactory) 
	 
{
	__BEGIN_TRY
		
	Assert(pFactory != NULL);

	if (m_Factories[ pFactory->getActionType() ] != NULL) {
		StringStream msg;
		msg << "duplicate action factories, " << pFactory->getActionName() ;
		throw Error(msg.toString());
	}
	
	// �׼����丮�� ����Ѵ�.
	m_Factories[ pFactory->getActionType() ] = pFactory;
			
	__END_CATCH
}

	
////////////////////////////////////////////////////////////////////////////////
// create condition object with condition type
////////////////////////////////////////////////////////////////////////////////
Action * ActionFactoryManager::createAction (ActionType_t actionType) const
	
{
	__BEGIN_TRY

	// �׼� Ÿ���� ������ �Ѿ���� ���ؼ� Seg.Fault �� �߻����� �ʵ���.
	// �̷� ����ڴ� ���� ©��� �Ѵ�.
	if (actionType >= m_Size || m_Factories[actionType] == NULL) 
	{
		StringStream msg;
		msg << "action factory [" << actionType << "] not exist.";
		cout << msg.toString() << endl;
		throw Error(msg.toString());
	}

	return m_Factories[actionType]->createAction();
			
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get condition name with condition type
////////////////////////////////////////////////////////////////////////////////
string ActionFactoryManager::getActionName (ActionType_t actionType) const
	
{
	__BEGIN_TRY

	// �׼� Ÿ���� ������ �Ѿ���� ���ؼ� Seg.Fault �� �߻����� �ʵ���.
	// �̷� ����ڴ� ���� ©��� �Ѵ�.
	if (actionType >= m_Size || m_Factories[actionType] == NULL) 
	{
		StringStream msg;
		msg << "invalid action type (" << actionType << ")";
		cout << msg.toString() << endl;
		throw Error(msg.toString());
	}

	return m_Factories[actionType]->getActionName();
			
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get action type with action type name
////////////////////////////////////////////////////////////////////////////////
ActionType_t ActionFactoryManager::getActionType (const string & actionname) const
	
{
	__BEGIN_TRY

#ifdef __OUTPUT_INIT__
	cout << "Action[" << actionname << "]..." << endl;
#endif

	for (int i = 0 ; i < m_Size ; i ++)
	{
		if (m_Factories[i] != NULL)
		{
			if (m_Factories[i]->getActionName() == actionname)
			{
				return i;
			}
		}
	}

	string msg = "no such action type : " + actionname;
	cout << msg << endl;
	throw Error(msg);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionFactoryManager::toString () const
	throw ()
{

	__BEGIN_TRY

	StringStream msg;

	msg << "ActionFactoryManager(\n";

	for (int i = 0 ; i < m_Size ; i ++)
	{
		msg << "ActionFactories[" << i << "] == ";
		msg << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getActionName());
		msg << "\n";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable declaration
ActionFactoryManager * g_pActionFactoryManager = NULL;
