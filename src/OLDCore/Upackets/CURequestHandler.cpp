//--------------------------------------------------------------------------------
//
// Filename    : CURequestHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "CURequest.h"

#ifdef __UPDATE_SERVER__
	#include <sys/types.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/sendfile.h>

	#include "Properties.h"

	#include "UpdateServerPlayer.h"
	#include "Upackets/UCUpdate.h"
	#include "Resource.h"
#endif

//--------------------------------------------------------------------------------
//
// Ŭ���̾�Ʈ�� ��û�� ���ҽ��� �����ϴ��� üũ�� ��,
// ������ ���, sendfile()�� ����ؼ� Ŭ���̾�Ʈ�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
void CURequestHandler::execute ( CURequest * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	Socket * pSocket = pUpdateServerPlayer->getSocket();

	const Resource & resource = pPacket->getResource();

	Version_t ClientVersion = 0;

	if( resource.getVersion() < 2000 ) {
		ClientVersion = 1;
	}

	char filename[ maxFilename + 1 ];
	sprintf( filename , "%s/%s/v%05d/%s" ,
		g_pConfig->getProperty("HomeDir").c_str() ,
		g_pConfig->getProperty("PatchDir").c_str() ,
//		resource.getVersion() , 
		ClientVersion, 
		resource.getFilename().c_str() 
	);

	//cout << "Try to open " << filename << "..." << endl;

	ifstream ifile( filename , ios::in | ios::binary | ios::nocreate );
		
	if ( !ifile ) {
		// �������� �ʴ� ������ ��û�� ���� ��ŷ���� �����Ѵ�.
		// �α׸� �� ��, BAN ���Ѿ� �Ѵ�.
		throw InvalidProtocolException(filename);
	}

	// ���� ũ�⸦ �˾Ƴ��� ���ؼ� ���� �����͸� �� �ڷ� �����δ�.
	ifile.seekg( 0 , ios::end );
	FileSize_t filesize = ifile.tellg();

	//cout << "Original FileSize  : " << filesize << endl;
	//cout << "Requested FileSize : " << resource.getFileSize() << endl;

	// Ŭ���̾�Ʈ���� ��û�� ������ ũ��� �ٸ� ���, ��ŷ �õ��� �����Ѵ�.
	if ( resource.getFileSize() != filesize ) {
		throw InvalidProtocolException("invalid filesize");
	}

	//--------------------------------------------------------------------------------
	// CURequest �� ��ܿ� ���ҽ��� �ٽ� UCUpdate �� ��Ƽ� ���� �����Ѵ�.
	// �״��� ���� ������ �����Ѵ�.
	//--------------------------------------------------------------------------------
	UCUpdate ucUpdate;
	ucUpdate.setResource( resource );	

	pUpdateServerPlayer->sendPacket( &ucUpdate );

	//--------------------------------------------------------------------------------
	// write file content
	//--------------------------------------------------------------------------------
	// ���� �����͸� �ٽ� �� ó������ �ǵ�����.
	ifile.seekg(0);
	long offset = 0;

	//cout << "=======================================================================" << endl;
	//cout << resource.getFilename() << " (" << filesize << "bytes) : ";

	// ���� ������ �����Ѵ�.
	DWORD nSent = sendfile( pSocket->getSOCKET() , ifile.rdbuf()->fd() , &offset, filesize );

	//cout << nSent << " bytes sent to client." << endl;
	//cout << "=======================================================================" << endl;

	if ( nSent != filesize ) {
		throw Error("���� ���� ����");
	}

	// ������ �ݴ´�.
	ifile.close();

	pUpdateServerPlayer->setPlayerStatus( USPS_AFTER_SENDING_UC_UPDATE );

#endif
		
	__END_CATCH
}
