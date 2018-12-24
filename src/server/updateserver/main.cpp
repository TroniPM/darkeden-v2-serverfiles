//--------------------------------------------------------------------------------
//
// Filename    : main.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Types.h"
#include "Exception.h"
#include "UpdateServer.h"
#include "Properties.h"

// ������Ʈ ���丮 ��ĵ ����
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/resource.h>

#include <iostream.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include "UpdateManager.h"
#include "Update.h"
#include "StringStream.h"

//	scandir
//	readdir
//	seekdir
//	getcwd
//
//	// ���ڿ� ��
//	strcasecmp( "LISt" , "LIST" ) == 0

class SourceInfo {

public :
	string getName() { return m_Name; }
	void setName( string Name ) { m_Name = Name; }

	string getDirectory() { return m_Directory; }
	void setDirectory( string Directory ) { m_Directory = Directory; }

private :

	string m_Name;
	string m_Directory;

};

class VersionInfo {

public :
	string getName() { return m_Name; }
	void setName( string Name ) { m_Name = Name; }

	string getDirectory() { return m_Directory; }
	void setDirectory( string Directory ) { m_Directory = Directory; }

	int getVersion() { return m_Version; }
	void setVersion( int Version ) { m_Version = Version; }

	int getSize() { return m_Size; }
	void setSize( int Size ) { m_Size = Size; }

private :

	string m_Name;
	string m_Directory;
	int m_Size;
	int m_Version;
};

list<SourceInfo *> SourceInfoList;
list<VersionInfo*> VersionInfoList;


class isSameName {

public :

	// constructor
	isSameName ( string Name ) : m_Name(Name) {}


	bool operator () ( VersionInfo * pVersionInfo ) throw ()
	{
		// �̸��� ����.
		if( strcasecmp( m_Name.c_str(), pVersionInfo->getName().c_str() ) == 0 ) {
			return true;
		} else {
			return false;
		}
	}

private :

	// Name identifier
	string m_Name;

};

class isSource {

public :

	// constructor
	isSource ( string Name ) : m_Name(Name) {}


	bool operator () ( SourceInfo * pSourceInfo ) throw ()
	{
		// �̸��� ����.
		if( strcasecmp( m_Name.c_str(), pSourceInfo->getName().c_str() ) == 0 ) {
			return true;
		} else {
			return false;
		}
	}

private :

	// Name identifier
	string m_Name;

};


/*
void main(void) {

	struct dirent * Testdir;
	int count = 0;

	readdir( 0, Testdir, count );
	scandir

	//cout << " DirName : " << TestDir->d_Name << endl;

}
*/
/*
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
*/


#include <dirent.h>

int myselect( const struct dirent *entry ) {

	const char * filename = entry->d_name;
	if( *filename == '.' ) {
		return 0;
	} else {
		return 1;
	}

}

void scan_Source( const string & Directory ) {

//	struct dirent **namelist;

	DIR * pDIR = opendir( Directory.c_str() );
	struct dirent * versionDir;
//	//cout << "Open Dir : " << Directory << endl;

	while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

		string vName = versionDir->d_name;

		if ( versionDir->d_ino != 0  && vName[0] != '.' ) {

//			//cout << "versionDir : " << versionDir->d_name<< endl;

			string DirectoryName = Directory + "/";
			string SubDirectory = DirectoryName + versionDir->d_name;

			struct stat List;
			stat( SubDirectory.c_str(), &List );
//			//cout << versionDir->d_name << " " << List.st_size << endl;

			replace ( DirectoryName.begin(), DirectoryName.end(), '/', '\\' );
//			//cout << "Path : " << array << " Path Size : " << size << endl;

			if( S_ISDIR( List.st_mode ) ) {

//				//cout << versionDir->d_name << " is Directory " << endl;


//			string SubDirectory = DirectoryName + "/" + namelist[n]->d_name;

//				//cout << "SubDirectory : " << SubDirectory << endl;
				scan_Source( SubDirectory );
//			//cout << get_current_dir_name() << endl;
			} else {
				SourceInfo * pSourceInfo = new SourceInfo();
				pSourceInfo->setName( versionDir->d_name );
				pSourceInfo->setDirectory( DirectoryName.substr( g_pConfig->getProperty("SourceDirectory").size() + 1, DirectoryName.size()-1 ) );
				SourceInfoList.push_back( pSourceInfo );

				/*
				// �ϴ� ���� �̸��� �ִ��� ã�´�.
				list<SourceInfo*>::iterator itr = find_if( SourceInfoList.begin(), SourceInfoList.end(), isSameName(pSourceInfo->getName()) );
				
				// �Ȱ��� �̸��� �ִٸ� �ֽ� �������� �־� �����.
				if ( itr != SourceInfoList.end() ) {

					//cout << "���� ���Ͽ��� ���� �̸��� ������ �߰� �Ǿ���!" << endl;

					//cout << "���� �ִ� ������ ���� : " << (*itr)->getDirectory() << ", ���� �̸��� : " << (*itr)->getName() << endl;
					//cout << "�ֽ� ������ ������ : " << pSourceInfo->getDirectory() << ", ���� �̸��� : " << pSourceInfo->getName() << endl;

				// ���� ������ ����.
				} else {
					SourceInfoList.push_back( pSourceInfo );
				}
				*/

			}

		}

	}
	closedir( pDIR );

}

void scan_Version( const string & Directory, int version ) {

//	struct dirent **namelist;

	DIR * pDIR = opendir( Directory.c_str() );
	struct dirent * versionDir;
//	//cout << "Open Dir : " << Directory << endl;

	while ( ( versionDir = readdir( pDIR ) ) != NULL ) {

		string vName = versionDir->d_name;

		if( vName == "index.dat" ) {
			string removeName = Directory + "/" + "index.dat";
			//cout << "Remove index.dat Directory : " << removeName << endl;
			remove( removeName.c_str() );
		}

		if ( versionDir->d_ino != 0  && vName[0] != '.' && vName != "index.dat" ) {

//			//cout << "versionDir : " << versionDir->d_name<< endl;
			string DirectoryName = Directory;

			string SubDirectory = DirectoryName + "/" + versionDir->d_name;

			/*
			replace ( DirectoryName.begin(), DirectoryName.end(), '/', '\\' );
//			//cout << "ChangeName : " << DirectoryName << endl;
			*/

			struct stat List;
			stat( SubDirectory.c_str(), &List );
//			//cout << versionDir->d_name << " " << List.st_size << endl;

//			//cout << "Path : " << array << " Path Size : " << size << endl;

			if( S_ISDIR( List.st_mode ) ) {

				int version = atoi( vName.substr( 1 , 5 ).c_str() );

//				//cout << versionDir->d_name << " is Directory " << endl;


//			string SubDirectory = DirectoryName + "/" + namelist[n]->d_name;

//				//cout << "SubDirectory : " << SubDirectory << endl;
				scan_Version( SubDirectory, version );
//			//cout << get_current_dir_name() << endl;
			} else {

				VersionInfo * pVersionInfo = new VersionInfo();
				pVersionInfo->setName( versionDir->d_name );

				list<SourceInfo*>::iterator itr2 = find_if( SourceInfoList.begin(), SourceInfoList.end(), isSource( pVersionInfo->getName() ) );

				pVersionInfo->setDirectory( (*itr2)->getDirectory() );
				pVersionInfo->setSize( List.st_size );

				pVersionInfo->setVersion( version );

				// �ϴ� ���� �̸��� �ִ��� ã�´�.
				list<VersionInfo*>::iterator itr = find_if( VersionInfoList.begin(), VersionInfoList.end(), isSameName( pVersionInfo->getName() ) );
				
				// �Ȱ��� �̸��� �ִٸ� �ֽ� �������� �־� �����.
				if ( itr != VersionInfoList.end() ) {
					//cout << "���� ������ �߰� �Ǿ��� �ֽ� �������� ��ġ��" << endl;

					//cout << "���� �ִ� ������ ������ : " << (*itr)->getVersion() << ", ���� �̸��� : " << (*itr)->getName() << endl;
					//cout << "�ֽ� ������ ������ : " << pVersionInfo->getVersion() << ", ���� �̸��� : " << pVersionInfo->getName() << endl;

					if( (*itr)->getVersion() < pVersionInfo->getVersion() ) {

						VersionInfo * pTempVersionInfo = (*itr);

						VersionInfoList.erase( itr );
						//cout << "������ ������ �����Ѵ�." << endl;

						delete pTempVersionInfo;

						VersionInfoList.push_back(pVersionInfo);
						//cout << "�� ������ ����Ʈ�� �߰��Ѵ�." << endl;

					} else {

					}

				// ���� ������ ����.
				} else {
					VersionInfoList.push_back(pVersionInfo);
				}
			}
		}
	}
	closedir( pDIR );

}

void create_Index() {

	list<VersionInfo*>::const_iterator itr = VersionInfoList.begin();

	int beforeVersion = 0;
	int version = 0;

	// ������������ ������ �ϳ��� �����鼭 ������ �� ��ġ�� �̾Ƴ���.
	for( ; itr != VersionInfoList.end(); itr++ ) {

		StringStream msg1;
		StringStream msg2;
		StringStream msg3;
		StringStream msg4;

		UpdateManager updatemanager;

		Update * pUpdate = new Update();

		msg1 << (*itr)->getName() << " " << (*itr)->getSize();
		msg2 << (*itr)->getDirectory() << (*itr)->getName();

		version = (*itr)->getVersion();

		char filename[256];
		sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , version);

		ofstream ofile( filename , ios::out | ios::app );

		// ������Ʈ ������ �˾Ƴ��� ����.
		if( beforeVersion != version ) {

			int Count = 0;
			list<VersionInfo*>::const_iterator itr2 = VersionInfoList.begin();

			for(; itr2 != VersionInfoList.end(); itr2++ ) {
				if( (*itr2)->getVersion() == version ) {
					Count++;
				}
			}
			//cout << "Version : " << version << ", Count: " << Count << endl;

			ofile.write( (const char *)&Count , szWORD );
			beforeVersion = version;
		}

		//cout << "create Index msg1 : " << msg1.toString() << endl;
		//cout << "create Index msg2 : " << msg2.toString() << endl;

		pUpdate = new Update();
		pUpdate->setVersion(version);
		pUpdate->setUpdateType(UPDATETYPE_CREATE_FILE);
		pUpdate->setParam(0,msg1.toString());
		pUpdate->setParam(1,msg2.toString());

		pUpdate->save(ofile);
		ofile.close();

	}

	// �� �ε����� �����Ѵ�.
	for( int i = 0; i <= version ; i++ ) {

		char filename[256];
		sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , i );
		ifstream ifile( filename, ios::in | ios::binary | ios::nocreate );
		// ������ ������ �� �ε����� �����Ѵ�.
		if ( !ifile ) {
			int Count = 0;

			char filename[256];
			sprintf(filename,"%s/v%05d/index.dat", g_pConfig->getProperty("PatchDirectory").c_str() , i );
			ofstream ofile( filename , ios::out | ios::app );
			ofile.write( (const char *)&Count , szWORD );

		}
		ifile.close();
	}
}

//--------------------------------------------------------------------------------
//
// main()
//
// UpdateServer�� ���� ����
//
//--------------------------------------------------------------------------------
int main ( int argc , char * argv[] )
{
    if ( argc < 3 ) {
        //cout << "Usage : updateserver -f ȯ������" << endl;
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
            throw Error("Usage : updateserver -f ȯ������");
        }

        // ù��° �Ķ���Ͱ� -f �� ���, �ι�° �Ķ���ʹ� ȯ�������� ��ġ�� �ȴ�.
        g_pConfig = new Properties();
        g_pConfig->load(Argv[2]);
    
        //cout << g_pConfig->toString() << endl;
    
    } catch ( Error & e ) {
        //cout << e.toString() << endl;
    }

	// �ҽ� ���丮�� �д´�.
//	scan_Source( g_pConfig->getProperty( "SourceDirectory") );

	/*
	//cout << "============================================================================" << endl;
	for( list<SourceInfo*>::const_iterator itr = SourceInfoList.begin(); itr != SourceInfoList.end(); itr++ ) {
		//cout << "Name : " << (*itr)->getName() << ", Directory : " << (*itr)->getDirectory() << endl;
	}
	//cout << "============================================================================" << endl;
	*/

//	scan_Version( g_pConfig->getProperty("PatchDirectory" ), 0 );

	/*
	// ���� ���丮�� �д´�.
	//cout << "============================================================================" << endl;
	for( list<VersionInfo*>::const_iterator itr = VersionInfoList.begin(); itr != VersionInfoList.end(); itr++ ) {
		//cout << "Version : " << (*itr)->getVersion() << ",Name : " << (*itr)->getName() << ", Directory : " << (*itr)->getDirectory() << endl;
	}
	//cout << "============================================================================" << endl;
	*/

	// index.dat ������ ���� �۾��� �Ѵ�.
//	create_Index();


	//
	// ������Ʈ ���� ��ü�� �����ϰ� �ʱ�ȭ�� �� Ȱ��ȭ��Ų��.
	//
	try {

		struct rlimit rl;
		rl.rlim_cur = RLIM_INFINITY;
		rl.rlim_max = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &rl);

		// ������Ʈ ���� ��ü�� �����Ѵ�.
		g_pUpdateServer = new UpdateServer();

		// ������Ʈ ���� ��ü�� �ʱ�ȭ�Ѵ�.
		g_pUpdateServer->init();

		// ������Ʈ ���� ��ü�� Ȱ��ȭ��Ų��.
		g_pUpdateServer->start();

	} catch ( Throwable & e ) {

		// �αװ� �̷����� ���� ������ ���� ��츦 ����ؼ�
		ofstream ofile("../log/instant.log",ios::out);
		ofile << e.toString() << endl;
		ofile.close();

		// ǥ�� ������ε� ������ش�.
		//cout << e.toString() << endl;

		// ������Ʈ ������ �ߴܽ�Ų��.
		// �� ���ο��� ���� �Ŵ��� ���� �ߴܵǾ�� �Ѵ�.
		g_pUpdateServer->stop();

	}
}
