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
#include "TheOneServer.h"
#include "Properties.h"
#include "StringStream.h"
#include <stdlib.h>
#include <stdio.h>
#include <new>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#include <vector>

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
int main ( int argc , char * argv[] )
{
	// �޸� ����.. �Լ��� �����Ѵ�.
	set_new_handler(memoryError);
	cerr << "Processing Arguments..." << endl;

	if ( argc < 3 ) {
		cout << "Usage : theoneserver -f ȯ������ [-p port]" << endl;
		exit(1);
	}

	// command-line parameter�� string ���� ��ȯ�Ѵ�. ^^;
	vector<string> Argv;
	Argv.reserve(argc);

	for ( int i = 0 ; i < argc ; i ++ )
		Argv.push_back( argv[i] );

	// ȯ�� ������ �о���δ�.
	// �� ���� ������ $VSHOME/bin��, ȯ�� ������ $VSHOME/conf �� �����ؾ� �Ѵ�.
	// command line ���� ȯ�� ������ ������ �� �ֵ��� �Ѵ�.

	try {

		if ( Argv[1] != "-f" ) {
			throw Error("Usage : loginserver -f ȯ������ [-p port]"); 
		}

		cerr << "Making Properties.." << endl;

		// ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
		g_pConfig = new Properties();
		g_pConfig->load(Argv[2]);
		
		cerr << "Making Properties Complete!" << endl;
		
		cout << g_pConfig->toString() << endl;

	} catch ( Error & e ) {
		cerr << e.toString() << endl;
		exit(1);
	}

	try {

		if ( argc>3 )
		{
			if (argc<5 || Argv[3] != "-p" )
				throw Error("Usage : theoneserver -f ȯ������ [-p port]");

			g_pConfig->setProperty("TheOneServerUDPPort", Argv[4]);
			cout << "TheOneServerUDPPort : " << g_pConfig->getProperty("TheOneServerUDPPort") << endl;;
		}

	} catch ( Error & e ) {
		cerr << e.toString() << endl;
		exit(1);
	}

	cerr << "Processing Arguments Complete!" << endl;

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
		g_pTheOneServer = new TheOneServer();

		// ���� ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pTheOneServer->init();

		// ���� ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pTheOneServer->start();
	} 
	catch ( Throwable & e ) 
	{
		cerr << e.toString() << endl;

		// ���� ������ �ߴܽ�Ų��.
		// �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ�� �Ѵ�.
		g_pTheOneServer->stop();
	}
}
