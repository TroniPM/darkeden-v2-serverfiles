
// Billing Test

#include <iostream>
#include "BillingPlayerManager.h"
#include "DatabaseManager.h"
#include "Properties.h"
#include "CommonBillingPacket.h"

int main (int argc , char* argv[])
{
	CommonBillingPacket cbp;
	cbp.test();
	cout << cbp.toString().c_str() << endl;



	// command-line parameter�� string ���� ��ȯ�Ѵ�. ^^;
    string* Argv;
        
    Argv = new string[argc];
    for (int i = 0 ; i < argc ; i ++)
        Argv[i] = argv[i];

    // ȯ�� ������ �о���δ�.
    // �� ���� ������ $VSHOME/bin��, ȯ�� ������ $VSHOME/conf �� �����ؾ� �Ѵ�.�
    // command line ���� ȯ�� ������ ������ �� �ֵ��� �Ѵ�.

	//-------------------------------------------------------------------
	// Load config file
	//-------------------------------------------------------------------
    try 
	{
        if (Argv[1] != "-f") 
		{
            throw Error("Usage : gameserver -f ȯ������");
        }

        // ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
    } 
	catch (Error & e) 
	{
        cout << e.toString() << endl;
		return 0;
    }

	//-------------------------------------------------------------------
	// DatabaseManager
	//-------------------------------------------------------------------
	g_pDatabaseManager = new DatabaseManager();

	//-------------------------------------------------------------------
	// BillingPlayerManager
	//-------------------------------------------------------------------
	g_pBillingPlayerManager = new BillingPlayerManager();

	try {

		g_pBillingPlayerManager->init();
		g_pBillingPlayerManager->start();

	} catch (Throwable &t) {
		cout << t.toString().c_str() << endl;
	}

	//-------------------------------------------------------------------
	// Main Loop
	//-------------------------------------------------------------------
	string cmd;
	while (1)
	{
		cout << "command> ";
		cin >> cmd;

		if (cmd=="quit")
			break;
	}

	delete g_pBillingPlayerManager;
}

