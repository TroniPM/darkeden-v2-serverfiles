//////////////////////////////////////////////////////////////////////
//
// Filename    : main.cpp
// Written By  : �� ȫ â   changaya@metrotech.co.kr
// Description : Database Cache Server�� main function
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

void memoryError()
{
	cerr << "CRITICAL ERROR! NOT ENOUGH MEMORY!" << endl;
	exit(0);
}

//////////////////////////////////////////////////////////////////////
//
// main()
//
//////////////////////////////////////////////////////////////////////
int main (int argc , char* argv[])
{
	cout << ">>> STARTING CACHE SERVER..." << endl;

	// �޸� ����..�Լ��� �����Ѵ�.
	set_new_handler(memoryError);
	cout << ">>> MEMORY HANDLER INSTALL SUCCESS..." << endl;

	// What?
	int* pPointer = NULL;
	pPointer = new int[500000000];
	delete pPointer;

	// ������ ��ġ�� ã�ƺ���.
	srand(time(0));
	cout << ">>> RANDOMIZATION INITIALIZATION SUCCESS..." << endl;

    if (argc < 3) 
	{
        cout << "Usage : cacheserver -f ȯ������" << endl;
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
            throw Error("Usage : cacheserver -f ȯ������");
        }

        // ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
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

		log(LOG_GAMESERVER, "", "", "Cache Server Start");

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
		// what?
		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// ���� ���� ��ü�� �����Ѵ�.
		g_pCacheServer = new CacheServer();

		cout << ">>> CACHE SERVER INSTANCE CREATED..." << endl;

		// ���� ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pCacheServer->init();

		cout << ">>> CACHE SERVER INITIALIZATION SUCCESS..." << endl;

		// ���� ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pCacheServer->start();
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
		g_pCacheServer->stop();
	} 
	catch (...) 
	{
		cout << "unknown exception..." << endl;
	}
}
