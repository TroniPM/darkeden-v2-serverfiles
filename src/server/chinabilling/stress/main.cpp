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
#include "Properties.h"
#include "StringStream.h"
#include "SBillingPlayerManager.h"
#include "PayUserManager.h"
#include "SProfile.h"
#include <stdlib.h>
#include <new>
#include <sys/resource.h>

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
		cout << "Usage : stress -f ȯ������" << endl;
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
			throw Error("Usage : stress -f ȯ������"); 
		}

		// ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
		g_pConfig = new Properties();
		g_pConfig->load(Argv[2]);
		
		cout << g_pConfig->toString() << endl;

	} catch ( Error & e ) {
		cout << e.toString() << endl;
	}

	// �α� �Ŵ����� �����ϰ� �ʱ�ȭ���� Ȱ��ȭ��Ų��.
	// �α� �Ŵ����� �α��� ������ �ʱ�ȭ�������� �߻��� ���ɼ��� �ִ� ����������
	// �����س��� �ϹǷ� �α��� ���� ���ο��� �ʱ�ȭ�ؼ��� �ȵȴ�.
	// ���� �ٸ� ��ü�� �����ϰ� �ʱ�ȭ�ϱ����� �α׸Ŵ����� �켱������ ����,
	// �ʱ�ȭ�Ǿ�� �Ѵ�.
	
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
		g_pSBillingPlayerManager = new SBillingPlayerManager();
		g_pPayUserManager = new PayUserManager();
		g_pSProfile = new SProfile();

		// �α��� ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pSBillingPlayerManager->init();
		g_pPayUserManager->init();

		// �α��� ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pSBillingPlayerManager->start();
		g_pPayUserManager->start();

		while ( true )
			usleep( 100 );
	} 
	catch ( Throwable & e ) 
	{
		// �αװ� �̷����� ���� ������ ���� ��츦 ����ؼ�
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// ǥ�� ������ε� ������ش�.
		cout << e.toString() << endl;

		// �α��� ������ �ߴܽ�Ų��.
		// �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ�� �Ѵ�.
	}
}
