//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : reiot@ewestsoft.com
// Description : ���� ������ ���� �Լ�
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Types.h"
#include "Exception.h"
#include "GameServer.h"
#include "LogClient.h"
#include "Properties.h"
#include "StringStream.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <new>
#include <stdexcept>
#include <stdio.h>

void handleMemoryError()
{
	cerr << "==============================================================================" << endl;
	cerr << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
	cerr << "==============================================================================" << endl;
	filelog("CriticalError.log", "CRITICAL ERROR! NOT ENOUGH MEMORY!");
	abort();
}

void handleUnhandledException()
{
	cerr << "==============================================================================" << endl;
	cerr << "UNHANDLED EXCEPTION OCCURED" << endl;
	cerr << "==============================================================================" << endl;
	filelog("CriticalError.log", "UNHANDLED EXCEPTION OCCURED");
	abort();
}

void handleUnexpectedException()
{
	cerr << "==============================================================================" << endl;
	cerr << "UNEXPECTED EXCEPTION OCCURED" << endl;
	cerr << "==============================================================================" << endl;
	filelog("CriticalError.log", "UNEXPECTED EXCEPTION OCCURED");
	abort();
}

void testMaxMemory()
{
	long mem = 10*1024*1024; // 10M

	char str[80];

	for (int i=1; i<2048; i++)
	{
		char* p = new char [mem];

		sprintf(str, "0x%08X = %04d0 M", p, i);

		cout << str << endl;
	}
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main (int argc , char* argv[])
{
	cout << ">>> STARTING GAME SERVER..." << endl;

	filelog("serverStart.log", "GameServer Start");

	// ���� �ڵ鷯�� �����Ѵ�. 
	std::set_new_handler(handleMemoryError);
	std::set_terminate(handleUnhandledException);
	std::set_unexpected(handleUnexpectedException);

	/*
	int* pPointer = NULL;
	pPointer = new int[10000000];
	delete [] pPointer;
	*/

	// ������ ��ġ�� ã�ƺ���.
	srand(time(0));
	cout << ">>> RANDOMIZATION INITIALIZATION SUCCESS..." << endl;

    if (argc < 3) 
	{
        //cout << "Usage : gameserver -f ȯ������" << endl;
        exit(1);
    }

    // command-line parameter�� string ���� ��ȯ�Ѵ�. ^^;
    string* Argv;
        
    Argv = new string[argc];
    for (int i = 0 ; i < argc ; i ++)
        Argv[i] = argv[i];

	cout << ">>> COMMAND-LINE PARAMETER READING SUCCESS..." << endl;

    // ȯ�� ������ �о���δ�.
    // �� ���� ������ $VSHOME/bin��, ȯ�� ������ $VSHOME/conf �� �����ؾ� �Ѵ�.�
    // command line ���� ȯ�� ������ ������ �� �ֵ��� �Ѵ�.

    try 
	{
        if (Argv[1] != "-f") 
		{
            throw Error("Usage : gameserver -f ȯ������ -t �׽�Ʈȯ������");
        }

        // ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;

		// by sigi. 2002.12.26
        if (argc>=4 && Argv[3] == "-t") 
		{
			g_pTestConfig = new Properties();

			if (argc>=5)
			{
				g_pTestConfig->load(Argv[4]);
			}
		}
    } 
	catch (Error & e) 
	{
        //cout << e.toString() << endl;
    }

	// �α� �Ŵ����� �����ϰ� �ʱ�ȭ���� Ȱ��ȭ��Ų��.
	// �α� �Ŵ����� ���� ������ �ʱ�ȭ�������� �߻��� ���ɼ��� �ִ� ����������
	// �����س��� �ϹǷ� ���� ���� ���ο��� �ʱ�ȭ�ؼ��� �ȵȴ�.
	// ���� �ٸ� ��ü�� �����ϰ� �ʱ�ȭ�ϱ����� �α׸Ŵ����� �켱������ ����,
	// �ʱ�ȭ�Ǿ�� �Ѵ�.
	try 
	{
		string LogServerIP   = g_pConfig->getProperty("LogServerIP");
		int    LogServerPort = g_pConfig->getPropertyInt("LogServerPort");
		int    LogLevel      = g_pConfig->getPropertyInt("LogLevel");
		g_pLogClient = new LogClient(LogServerIP, LogServerPort);
		LogClient::setLogLevel(LogLevel);

		log(LOG_GAMESERVER, "", "", "Game Server Start");

		//cout << "LogServerIP = " << LogServerIP << endl;
		//cout << "LogServerPort = " << LogServerPort << endl;
		//cout << "LogLevel = " << LogClient::getLogLevel() << endl;
	} 
	catch (Error & e) 
	{
		//cout << e.toString() << endl;
	}

	cout << ">>> LOGCLIENT INITIALZATION SUCCESS..." << endl;

	//
	// ���� ���� ��ü�� �����ϰ� �ʱ�ȭ�� �� Ȱ��ȭ��Ų��.
	//
	try 
	{
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// ���� ���� ��ü�� �����Ѵ�.
		g_pGameServer = new GameServer();

		cout << ">>> GAME SERVER INSTANCE CREATED..." << endl;

		// ���� ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pGameServer->init();

		cout << ">>> GAME SERVER INITIALIZATION SUCCESS..." << endl;

		// ���� ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pGameServer->start();
	} 
	catch (Throwable & e) 
	{
		// �αװ� �̷����� ���� ������ ���� ��츦 ����ؼ�
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// ǥ�� ������ε� ������ش�.
		cout << e.toString() << endl;

		// ���� ������ �ߴܽ�Ų��.
		// �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ�� �Ѵ�.
		g_pGameServer->stop();
	} 
	catch (...) 
	{
		cout << "unknown exception..." << endl;
	}
}
