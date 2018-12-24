//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : �α��� ������ ���� �Լ�
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Types.h"
#include "Exception.h"
#include "LoginServer.h"
#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void memoryError()
{
	cout << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
	exit(0);
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main ( int argc , char * argv[] )
{
	// �޸� ����.. �Լ��� �����Ѵ�.
	set_new_handler(memoryError);

	if ( argc < 3 ) {
		cout << "Usage : loginserver -f ȯ������ [-p port]" << endl;
		exit(1);
	}

	// command-line parameter�� string ���� ��ȯ�Ѵ�. ^^;
	string * Argv;

	Argv = new string[argc];
	for ( int i = 0 ; i < argc ; i ++ )
		Argv[i] = argv[i];

	// ȯ�� ������ �о���δ�.
	// �� ���� ������ $VSHOME/bin��, ȯ�� ������ $VSHOME/conf �� �����ؾ� �Ѵ�.�
	// command line ���� ȯ�� ������ ������ �� �ֵ��� �Ѵ�.

	try {

		if ( Argv[1] != "-f" ) {
			throw Error("Usage : loginserver -f ȯ������ [-p port]"); 
		}

		// ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
		g_pConfig = new Properties();
		g_pConfig->load(Argv[2]);
		
		cout << g_pConfig->toString() << endl;

	} catch ( Error & e ) {
		cout << e.toString() << endl;
	}

	try {

		if ( argc>3 )
		{
			if (argc<5 || Argv[3] != "-i" )
				throw Error("Usage : loginserver -f ȯ������ [-i ID]");

			// port�� ������ �����Ѵ�.
			char sLoginServerPort[5], sLoginServerUDPPort[5], sLoginServerID[5];
			sprintf( sLoginServerPort, "%d", g_pConfig->getPropertyInt("LoginServerBasePort") + atoi(argv[4]) );
			sprintf( sLoginServerUDPPort, "%d", g_pConfig->getPropertyInt("LoginServerBaseUDPPort") + atoi(argv[4]) );
			sprintf( sLoginServerID, "%d", g_pConfig->getPropertyInt("LoginServerBaseID") + atoi(argv[4]) );

			g_pConfig->setProperty("LoginServerPort", sLoginServerPort );
			g_pConfig->setProperty("LoginServerUDPPort", sLoginServerUDPPort );
			g_pConfig->setProperty("LoginServerID", sLoginServerID );

			cout << "LoginServerPort : " << sLoginServerPort << endl;
			cout << "LoginServerUDPPort : " << sLoginServerUDPPort << endl;
			cout << "LoginServerID : " << sLoginServerID << endl;
		}

	} catch ( Error & e ) {
		cout << e.toString() << endl;
	}


	// �α� �Ŵ����� �����ϰ� �ʱ�ȭ���� Ȱ��ȭ��Ų��.
	// �α� �Ŵ����� �α��� ������ �ʱ�ȭ�������� �߻��� ���ɼ��� �ִ� ����������
	// �����س��� �ϹǷ� �α��� ���� ���ο��� �ʱ�ȭ�ؼ��� �ȵȴ�.
	// ���� �ٸ� ��ü�� �����ϰ� �ʱ�ȭ�ϱ����� �α׸Ŵ����� �켱������ ����,
	// �ʱ�ȭ�Ǿ�� �Ѵ�.
	
	try 
	{
		string LogServerIP   = g_pConfig->getProperty("LogServerIP");
		int    LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
		g_pLogClient = new LogClient(LogServerIP, LogServerPort);
		LogClient::setLogLevel(g_pConfig->getPropertyInt("LogLevel"));

		log(LOG_LOGINSERVER, "", "", "Login Server Start");
	} 
	catch ( Throwable & t ) 
	{
		cout << t.toString() << endl;
	}

	//
	// �α��� ���� ��ü�� �����ϰ� �ʱ�ȭ�� �� Ȱ��ȭ��Ų��.
	//
	try 
	{
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// �α��� ���� ��ü�� �����Ѵ�.
		g_pLoginServer = new LoginServer();

		// �α��� ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pLoginServer->init();

		// �α��� ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pLoginServer->start();
	} 
	catch ( Throwable & e ) 
	{
		// �αװ� �̷����� ���� ������ ���� ��츦 ����ؼ�
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// �������� ĳġ���� ���� ���� �Ǵ� ������ �߻��ߴٴ� ���̴�.
		// �� ��� LEVEL1�� �α��ؾ� �Ѵ�. (������ �α��Ѵٴ� ��)
		log(LOG_LOGINSERVER_ERROR, "", "", e.toString());

		// ǥ�� ������ε� ������ش�.
		cout << e.toString() << endl;

		// �α��� ������ �ߴܽ�Ų��.
		// �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ�� �Ѵ�.
		g_pLoginServer->stop();
	}
}
