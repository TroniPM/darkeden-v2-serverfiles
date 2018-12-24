//--------------------------------------------------------------------------------
//
// Filename    : CUBeginUpdateHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "CUBeginUpdate.h"

#ifdef __UPDATE_SERVER__
	#include <sys/dir.h>
//	#include <stdio.h>
//	#include <fcntl.h>
//	#include <unistd.h>
	#include "UpdateServerPlayer.h"
	#include "Properties.h"
	#include "Upackets/UCUpdateList.h"
	#include "UpdateServerPlayer.h"
	#include "UpdateServer.h"

	// ������Ʈ ���丮 ��ĵ ����
	#include <stdio.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <sys/stat.h>

#endif

/*
//--------------------------------------------------------------------------------
//
// Ŭ���̾�Ʈ�� ���� �ٷ� ���������� �ֽ� ���������� ����Ʈ�� ������ ��,
// �� ������ ������Ʈ ����� merge �ؼ� ����ȭ�� ������Ʈ ����� ����Ʈ��
// �����ؼ� UCUpdateList ��Ŷ�� ��� Ŭ���̾�Ʈ�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
void CUBeginUpdateHandler::execute ( CUBeginUpdate * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	try {

		//cout << "Client Version : " << pPacket->getVersion() << endl;

		//--------------------------------------------------------------------------------
		// ��ġ ���丮�� ���� ���丮���� ����Ʈ�� �����Ѵ�.
		// �̶� Ŭ���̾�Ʈ �������� ���ų� ���� ������ �����ص� �ȴ�.
		//--------------------------------------------------------------------------------

		// ���丮 �̸��� ����Ʈ
		list<string> directories;

		string patchDir = g_pConfig->getProperty("HomeDir") + separator + g_pConfig->getProperty("PatchDir");

		//cout << "patchDir = " << patchDir << endl;

		// ��ġ ���丮�� �����Ѵ�.
		DIR * pDIR = opendir( patchDir.c_str() );

		// ��ġ ���丮�� ������ ��¯ Ȳ!
		Assert( pDIR != NULL );

		// ��ġ ���丮�� ���� ���丮(���� ���丮)���� �о���δ�.
		bool sameVersionFound = false;
		struct dirent * versionDir;
		while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

			// �� ����(inode==0)�� �����Ѵ�...
			if ( versionDir->d_ino != 0 ) {

				//	
				// ���� ���丮�� v + 0���� ä���� 5�ڸ� ���� ���ڿ��� �Ǿ� �ִ�.
				//  ex> v00001/ v00002/ v00003/ ...
				//
				string dir = versionDir->d_name;

				// v �� �������� �ʴ� ���� ���丮�δ� "." �� ".." �� �ִ�. -_-;
				if ( dir[0] == 'v' ) {

					// ������ ���ϱ� ���ؼ���
					// ���� �κ��� ��Ʈ������ ��ȯ�ؼ� �ٽ� ������ ��ȯ�Ѵ�.
					Version_t version = atoi( dir.substr( 1 , 5 ).c_str() );

					if ( version == pPacket->getVersion() )
						sameVersionFound = true;

					if ( version > pPacket->getVersion() )
						directories.push_back( dir );

				} else
					//cout << endl;
			}
			
		}

		closedir( pDIR );

		if ( !sameVersionFound ) {
			throw InvalidProtocolException("invalid client version");
		}

		// �׽�Ʈ�� ����غ���.
		for ( list<string>::iterator itr = directories.begin() ; itr != directories.end() ; itr ++ )
			//cout << "Newer Version : " << *itr << endl;


		//--------------------------------------------------------------------------------
		// �ֽ� ���� ���丮���� �˻��ϸ鼭, �� ���丮�� index.dat ���ϵ��� �ε��ؼ�
		// UpdateManager ��ü�� �����Ѵ�.
		//--------------------------------------------------------------------------------
	
		UCUpdateList ucUpdateList;
		UpdateManager * pUpdateManager = ucUpdateList.getUpdateManager();

//		int i = 0;

		for ( list<string>::iterator itr = directories.begin() ; itr != directories.end() ; itr ++ ) {
			
			// ex> "/home/vs/reiot/data/patch" + "/" + "v00010" + "/" + "index.dat"
			string filename = patchDir + separator + *itr + separator + "index.dat";

			//cout << "try to open " << filename << endl;

			pUpdateManager->load( filename );

//			if( i == 12 ) break;
//			i++;
		}

		//cout << pUpdateManager->toString() << endl;

		pUpdateServerPlayer->sendPacket( &ucUpdateList );

		pUpdateServerPlayer->setPlayerStatus( USPS_AFTER_SENDING_UC_UPDATE_LIST );

	} catch ( FileNotExistException & fnee ) {
		throw InvalidProtocolException( fnee.toString() );
	}

#endif
		
	__END_CATCH
}
*/

void CUBeginUpdateHandler::scan_Dir( const string Directory, CUBeginUpdate* pPacket, UpdateManager * pUpdateManager, bool bHttpPatch, bool bUpdaterPatch )
	throw( ProtocolException, Error )
{

#ifdef __UPDATE_SERVER__

	DIR * pDIR = opendir( Directory.c_str() );
	struct dirent * versionDir;
	//cout << "Open Dir : " << Directory << endl;

	while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

		string vName = versionDir->d_name;

		if ( versionDir->d_ino != 0  && vName[0] != '.' ) {

			//cout << "versionDir : " << versionDir->d_name<< endl;

			string DirectoryName = Directory + "/";
			string SubDirectory = DirectoryName + versionDir->d_name;

			struct stat List;
			stat( SubDirectory.c_str(), &List );
			//cout << versionDir->d_name << " " << List.st_size << endl;

			//cout << "Path : " << SubDirectory << " Path Size : " << List.st_size << endl;

			if( S_ISDIR( List.st_mode ) ) {

				// ������ ���ϱ� ���ؼ���
				// ���� �κ��� ��Ʈ������ ��ȯ�ؼ� �ٽ� ������ ��ȯ�Ѵ�.
				Version_t version = atoi( vName.substr( 1 , 5 ).c_str() );

				Version_t ClientVersion = pPacket->getVersion() - 3000;
				if( bUpdaterPatch ) 
				{
					ClientVersion = (ClientVersion<=46? 1 : 2);
				}

				if ( version == ClientVersion ) {

					//cout << versionDir->d_name << " is Directory " << endl;


					string SubDirectory = DirectoryName + versionDir->d_name;

					//cout << "SubDirectory : " << SubDirectory << endl;
					scan_Dir( SubDirectory, pPacket, pUpdateManager, bHttpPatch, bUpdaterPatch );
//					//cout << get_current_dir_name() << endl;
				}

			} else {

				//string tempversion = g_pConfig->getProperty("PatchVersion");

				//Version_t PatchVersion = atoi( tempversion.c_str() );

				//cout << "It is correct file" << endl;

				StringStream msg1;
				StringStream msg2;

				msg1 << versionDir->d_name << " " << List.st_size;

				if( vName == "AppendPatch.inf" ) {
					msg2 << "Data\\Info\\" << versionDir->d_name;
				} else {
					msg2 << versionDir->d_name;
				}


				//cout << " msg1 :" << msg1.toString() << endl;
				//cout << " msg2 :" << msg2.toString() << endl;

				Update * pUpdate = new Update();

				// ClientVersion���� �ٲ�. by sigi. 2002.10.16
				Version_t ClientVersion = pPacket->getVersion();
				if (ClientVersion > 3000)
					ClientVersion -= 3000;

				pUpdate->setVersion( ClientVersion );//pPacket->getVersion() );
				pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
				pUpdate->setParam(0,msg1.toString());
				pUpdate->setParam(1,msg2.toString());

//				pUpdate->setVersion( PatchVersion );
//				if( pPacket->getVersion() > 1000 ) {
				if( bHttpPatch ) {

					srand(time(NULL));
					int randomv = rand();
					// URL ���� �۾�....... �� ��¼�� ��¼��
					int Random = randomv % g_pConfig->getPropertyInt( "MAXURL" );
					StringStream ConfigParam;
					ConfigParam << "URL" << Random;
					StringStream URL;
					URL << g_pConfig->getProperty( ConfigParam.toString() );
					pUpdate->setParam(5, URL.toString() );

				}

				pUpdateManager->push_back( pUpdate );

			}
		}
	}
	closedir( pDIR );

#endif

}

//--------------------------------------------------------------------------------
//
// Ŭ���̾�Ʈ�� ���� �ٷ� ���������� �ֽ� ���������� ����Ʈ�� ������ ��,
// �� ������ ������Ʈ ����� merge �ؼ� ����ȭ�� ������Ʈ ����� ����Ʈ��
// �����ؼ� UCUpdateList ��Ŷ�� ��� Ŭ���̾�Ʈ�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
void CUBeginUpdateHandler::execute ( CUBeginUpdate * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	bool bHttpPatch = true;
	bool bUpdaterPatch = false;


	// 3000�� �̻� ������ 2002.7.12 �����������̴�.
	// ���� ������ �� �̻� �������� ���� �����̹Ƿ�
	// 3000�� ���ϴ� ¥����.
	if (pPacket->getVersion() < 3000)
	{
		throw DisconnectException("under3000");	
	}

	/*
	if( pPacket->getVersion() < 2000 ) {
		if( pPacket->getVersion () > 1000 ) {
			bHttpPatch = true;
			pPacket->setVersion( pPacket->getVersion() - 1000 );
		}

		bUpdaterPatch = true;
	} else {

		if (pPacket->getVersion() > 2000)
		{
			bHttpPatch = true;
			pPacket->setVersion( pPacket->getVersion() - 2000 );
		}

	}
	*/

	// 3000�� �̻��� ������ HTTP patch�̴�.
	if( bHttpPatch )
	{
		((UpdateServerPlayer*)pPlayer)->setExpiredTime( 5 );
	}

	// ���� ���⼭ ��� ó���� �ϰ� �ȴ�.
	// ��� �� �͵� ����. ���� ������ ���丮�� �о �� �ȿ� ������ ������ ����Ʈ�� ����� ������
	// ������ ���� �ϸ� �ȴ�.
	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	string Directory = g_pConfig->getProperty("HomeDir") + separator + g_pConfig->getProperty("PatchDir");

	UCUpdateList ucUpdateList;
	UpdateManager * pUpdateManager = ucUpdateList.getUpdateManager();

	// Info ���õǼ� ������Ʈ�� �ϳ� �߰��Ѵ�.
	if ( pPacket->getVersion() >= g_pConfig->getPropertyInt("InfoVersion") )
	{
		if ( pPacket->getInfoVersion() < g_pConfig->getPropertyInt("InfoMarkVersion") )
		{
			Update* pUpdate = new Update();

			Version_t ClientVersion = pPacket->getVersion();
			if (ClientVersion > 3000)
				ClientVersion -= 3000;

			pUpdate->setVersion( ClientVersion );//pPacket->getVersion() );
			pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);

			string infoFileName = "InfoPatch" + g_pConfig->getProperty("InfoMarkVersion");
			infoFileName = infoFileName + " 1";
			pUpdate->setParam(0, infoFileName);

			int Random = rand() % g_pConfig->getPropertyInt( "MAXINFOURL" );
			StringStream ConfigParam;
			ConfigParam << "INFOURL" << Random;
			StringStream URL;
			URL << g_pConfig->getProperty( ConfigParam.toString() );

			pUpdate->setParam(5, URL.toString() );
			pUpdateManager->push_back( pUpdate );
		}
	}

	scan_Dir( Directory, pPacket, pUpdateManager, bHttpPatch, bUpdaterPatch );

//	WORD version = pPacket->getVersion();
//	WORD keyver = atoi( g_pConfig->getProperty("KeyVersion").c_str() );

	if ( pPacket->getType() == CUBeginUpdate::OLD_UPDATE )
	{
		ucUpdateList.setOld(true);
	}
	else
	{
		ucUpdateList.setOld(false);
		string KeyFileName = Directory + "/../" + g_pConfig->getProperty("KeyFile");
		FILE* pKeyFile = fopen( KeyFileName.c_str(), "r" );
		if ( pKeyFile == NULL )
		{
			filelog("UpdateServerError.log", "Ű ������ �����.");
			throw Error("Ű ������ ������ ��.��");
		}

		fread( (void*)ucUpdateList.getKeyArray(), szBYTE, 10, pKeyFile );
		fclose( pKeyFile );

		if ( pPacket->getType() == CUBeginUpdate::ONE_VERSION_KEY_BACK ) ucUpdateList.setFront( false );
		else 
		{
			ucUpdateList.setFront( true );

			Update* pUpdate = new Update();

			Version_t ClientVersion = pPacket->getVersion();
			if (ClientVersion > 3000)
				ClientVersion -= 3000;

			pUpdate->setVersion( ClientVersion );//pPacket->getVersion() );
			pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);

			WORD lastGuildMarkVersion = g_pConfig->getPropertyInt("LastGuildMarkVersion");
			string guildFileName = "Guild";

			if ( lastGuildMarkVersion > pPacket->getGuildVersion() )
				guildFileName = guildFileName + itos( lastGuildMarkVersion ) + ".txt" + " 1"; 
			else 
				guildFileName = guildFileName + itos( pPacket->getGuildVersion() ) + ".txt" + " 1";

			pUpdate->setParam(0, guildFileName);
			pUpdate->setParam(5, g_pConfig->getProperty("GUILDURL"));

			if ( pPacket->getGuildVersion() > 0 && pPacket->getGuildVersion() < g_pConfig->getPropertyInt("GuildMarkVersion") && ClientVersion > g_pConfig->getPropertyInt("StartGuildVersion") )
				pUpdateManager->push_back( pUpdate );

		}
	}

	//cout << pUpdateManager->toString() << endl;
	pUpdateServerPlayer->sendPacket( &ucUpdateList );
	pUpdateServerPlayer->setPlayerStatus( USPS_AFTER_SENDING_UC_UPDATE_LIST );

#endif
		
	__END_CATCH
}


