//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSubInventoryInfoHandler.cpp
// Written By  : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCSubInventoryInfo.h"
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		#include "ClientDef.h"
		#include "UIFunction.h"
	#endif

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		extern void SetSubInventoryInfo(InventoryInfo* pInventoryInfo);
	#endif
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void GCSubInventoryInfoHandler::execute ( GCSubInventoryInfo * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{

	
#ifdef __GAME_CLIENT__
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		if(NULL == g_pZone || NULL == g_pPlayer)
			return ;
		MItem* pItem = g_pPlayer->GetItemCheckBuffer();
		if(NULL == pItem)
			return;

		g_pPlayer->ClearItemCheckBuffer();
		UI_RunSubInventory(pItem);
		
		SetSubInventoryInfo(pPacket->getInventoryInfo());
	#endif
#endif

}
