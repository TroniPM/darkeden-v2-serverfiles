//////////////////////////////////////////////////////////////////////////////
// Filename    : ClientManager.cc
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ClientManager.h"
#include "Socket.h"
#include "ThreadManager.h"
#include "Assert.h"
#include "ThreadPool.h"
#include "ServerSocket.h"
#include "Properties.h"
#include "IncomingPlayerManager.h"
#include "ZonePlayerManager.h"
#include "ZoneGroupManager.h"
#include "VariableManager.h"
#include "VSDateTime.h"
#include "DB.h"
//#include "UserGateway.h"
#include "WarSystem.h"
#include "ParkingCenter.h"
#include "ctf/FlagManager.h"

#include "GDRLairManager.h"

#include "LocalIP.h"
#include <list>

#include "TOpackets/GTOAcknowledgement.h"
#include "LoginServerManager.h"

ClientManager* g_pClientManager = NULL;

//////////////////////////////////////////////////////////////////////////////
// constructor
// ���� �Ŵ��� ��ü�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
ClientManager::ClientManager ()
	throw (Error)
{
	__BEGIN_TRY

	// create incoming player manager
	g_pIncomingPlayerManager = new IncomingPlayerManager();
	Assert(g_pIncomingPlayerManager != NULL);

	// ������ ZoneGroup�� Balancing�� �ð��� �����Ѵ�.
	getCurrentTime( m_BalanceZoneGroupTime );
	m_BalanceZoneGroupTime.tv_sec += 5*60;//g_pVariableManager->getZoneGroupBalancingMinute()*60;
	m_bForceZoneGroupBalancing = false;
	m_bDefaultZoneGroupBalancing = false;

	m_Mutex.setName("ClientManager");

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
// ���� �Ŵ��� ��ü�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
ClientManager::~ClientManager ()
	throw (Error)
{
	__BEGIN_TRY

	// Delete incoming player manager
	SAFE_DELETE(g_pIncomingPlayerManager);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� �Ŵ��� ��ü�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void ClientManager::init ()
	 throw (Error)
{
	__BEGIN_TRY

	// initialize incoming player manager
	g_pIncomingPlayerManager->init();
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ClientManager::stop ()
	 throw (Error)
{
	__BEGIN_TRY

	// �ñ׳ι������ ���߿� �����ϵ��� �Ѵ�.
	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// accept new connection
//////////////////////////////////////////////////////////////////////////////
void ClientManager::run ()
	 throw (Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	//ZoneGroup* pZoneGroup = g_pZoneGroupManager->getZoneGroup(1);
	//ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();

	//VSTime vstime;
	Timeval dummyQueryTime;
	getCurrentTime( dummyQueryTime );

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	Timeval theOneAckTime;
	getCurrentTime( theOneAckTime );
//	theOneAckTime.tv_sec += 198 * 60;
	theOneAckTime.tv_sec += (10 + rand()%20) * 60;

	//	theOneAckTime.tv_sec += 1 * 60;
#endif

	Timeval userGatewayTime;
	getCurrentTime(userGatewayTime);
	userGatewayTime.tv_sec += 10;

	while (true) 
	{
	    //ofstream file("ClientManager.txt", ios::out | ios::app);
		//StringStream msg;

		// CPU �������� ���̱� ���� 0.001�� ���� ����.
		try 
		{
			// I/O Multiplexing
			usleep(100);
			//g_pIncomingPlayerManager->copyPlayers();

			// game global time setting
			setCurrentTime();

			//vstime.start();
			g_pIncomingPlayerManager->select();
			//file << "IncomingPlayerManagerSelect:" << vstime.elapsed() << endl;

			//vstime.restart();
			g_pIncomingPlayerManager->processExceptions();
			//file << "IncomingPlayerManagerException:" << vstime.elapsed() << endl;

			//vstime.restart();
			g_pIncomingPlayerManager->processInputs();
			//file << "IncomingPlayerManagerInput:" << vstime.elapsed() << endl;

			//vstime.restart();
			g_pIncomingPlayerManager->processOutputs();
			//file << "IncomingPlayerManagerOutput:" << vstime.elapsed() << endl;
		} 
		catch (TimeoutException&) 
		{
			// select()���� timeout�� �߻��ϸ�, ���Ŀ� �� ���� �ϳ��� ����.
			// �ٷ� ���� ������ �Ѿ�� �ǰڴ�..
		}
		catch (Error&)
		{
			throw;
		}
		catch (Throwable& t)
		{
			filelog("clientManagerBug.txt", "%s", t.toString().c_str());
		}

		//vstime.start();
		g_pIncomingPlayerManager->processCommands();
		//file << "IncomingPlayerManagerCommands:" << vstime.elapsed() << endl;

		/*
		try 
		{
			pZonePlayerManager->select();
			pZonePlayerManager->processExceptions();
			pZonePlayerManager->processInputs();
			pZonePlayerManager->processOutputs();
		}
		catch (TimeoutException)
		{
		}

		pZonePlayerManager->processCommands();
		pZoneGroup->heartbeat();
		*/

		//usleep(100);

		// ���� �ð��� �����ؼ�, 30�ʸ��� ConnectionInfoManager ����
		// expire �� ConnectionInfo �� �����Ѵ�.

		g_pIncomingPlayerManager->heartbeat();

		//vstime.start();
		g_pConnectionInfoManager->heartbeat();
		//file << "ConnectionInfoManagerHeartbeat:" << vstime.elapsed() << endl;

		//file.close();
		Timeval currentTime;
		getCurrentTime(currentTime);

		if (dummyQueryTime < currentTime)
		{
			g_pDatabaseManager->executeDummyQuery( g_pDatabaseManager->getDistConnection("PLAYERDB") );

			// 1�ð� ~ 1�ð� 30�� ���̿��� dummy query �ð��� �����Ѵ�.
			// timeout�� ���� �ʰ� �ϱ� ���ؼ��̴�.
			dummyQueryTime.tv_sec += (60+rand()%30) * 60;
		}

#if	defined(__CHINA_SERVER__) || defined(__THAILAND_SERVER__)
		if ( theOneAckTime < currentTime )
		{
			list<string> ips = getLocalIP();
			list<string>::iterator itr = ips.begin();
			list<string>::iterator endItr = ips.end();

			for ( ; itr != endItr ; ++itr )
			{
				string& myIP = *itr;
//				cout << "My IP Address is : " << myIP << endl;

				GTOAcknowledgement GTO;
				GTO.setServerIP( myIP );
				GTO.setServerType( 0 );
				GTO.setUDPPort(g_pConfig->getPropertyInt("GameServerUDPPort") );

				//g_pLoginServerManager->sendPacket( "61.78.53.244", 9981, &GTO );
				g_pLoginServerManager->sendPacket( "61.78.53.244", 19982, &GTO );
			}

			//theOneAckTime.tv_sec += ( 180 + rand()%300 ) * 60;
			theOneAckTime.tv_sec += ( 60 + rand()%120 ) * 60;
		}
#endif

		if (m_BalanceZoneGroupTime < currentTime)
		{
			g_pZoneGroupManager->balanceZoneGroup(m_bForceZoneGroupBalancing, m_bDefaultZoneGroupBalancing);
			m_BalanceZoneGroupTime.tv_sec = currentTime.tv_sec + g_pVariableManager->getZoneGroupBalancingMinute()*60;

			m_bForceZoneGroupBalancing = false;
			m_bDefaultZoneGroupBalancing = false;
		}

		// by sigi. 2002.12.30
		if (userGatewayTime < currentTime)
		{
/*			if (UserGateway::getInstance()->getTotalInfo() > 0)
			{
				int ZonePlayerNum 		= g_pZoneGroupManager->getPlayerNum();
				int IncomingPlayerNum 	= g_pIncomingPlayerManager->size();
				int TotalPlayerNum 		= ZonePlayerNum + IncomingPlayerNum;

				filelog("userGateway.log", "Users(%d+%d=%d), %s", 
											ZonePlayerNum,
											IncomingPlayerNum,
											TotalPlayerNum,
											UserGateway::getInstance()->toString().c_str());

				UserGateway::getInstance()->clear();
			}*/

			// 10�� �� �ٽ� üũ
			userGatewayTime.tv_sec += 10;
		}

		// by sigi. 2002.9.26
		if (!m_EventManager.isEmpty())
		{
			try {
				g_pZoneGroupManager->lockZoneGroups();

				__ENTER_CRITICAL_SECTION(m_Mutex)

				m_EventManager.heartbeat();
			
				__LEAVE_CRITICAL_SECTION(m_Mutex)

				g_pZoneGroupManager->unlockZoneGroups();
			} catch (Throwable& t) {

				filelog("eventManagerBug.txt", "ClientManager::EventManager::heartbeat - %s", t.toString().c_str());
				g_pZoneGroupManager->unlockZoneGroups();
			}
		}

		// ����~
		if (g_pVariableManager->isWarActive())
		{
			g_pWarSystem->heartbeat();
		}

		if (g_pVariableManager->isActiveFlagWar())
		{
			g_pFlagManager->heartbeat();
		}

		// �����ش�.
		g_pParkingCenter->heartbeat();

		// CPU �������� ���̱� ���� 0.001�� ���� ����.
	} //while

	__END_DEBUG
	__END_CATCH
}

void    ClientManager::setBalanceZoneGroup(int afterMinutes, bool bForce, bool bDefault)
{
	getCurrentTime(m_BalanceZoneGroupTime);

	m_BalanceZoneGroupTime.tv_sec += afterMinutes*60;
	m_bForceZoneGroupBalancing = bForce;
	m_bDefaultZoneGroupBalancing = bDefault;
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void ClientManager::addEvent (Event* pEvent)
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	addEvent_LOCKED( pEvent );

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void ClientManager::addEvent_LOCKED (Event* pEvent)
	throw (Error)
{
	__BEGIN_TRY

	// �̹� �ִ°� �����.
	m_EventManager.deleteEvent(pEvent->getEventClass());

	m_EventManager.addEvent(pEvent);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
bool ClientManager::deleteEvent (Event::EventClass EClass)
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_EventManager.deleteEvent(EClass);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string ClientManager::toString () const
	   throw (Error)
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ClientManager()";
	return msg.toString();

	__END_CATCH
}


