#include "LogNameManager.h"
#include "Exception.h"
#include "DB.h"

void
LogNameManager::init()
{
	try 
	{
		release();

		Statement* pStmt   = NULL;
		Result*    pResult = NULL;
		
		BEGIN_DB
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery("SELECT Name FROM LogUserInfo");

			while (pResult->next()) 
			{
				// 0 �� �ǹ̾���.
				add( pResult->getString(1), 0 );
			}

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)

	} catch (Throwable& t) {
		filelog("LogNameManagerBUG.txt", "%s", t.toString().c_str());
	}
}

