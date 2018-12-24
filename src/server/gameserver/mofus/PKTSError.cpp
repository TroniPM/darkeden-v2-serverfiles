/////////////////////////////////////////////////////////////////////////////
// Filename : PKTSError.cpp
// Desc		: �¶��� �������� ó�� ������ ���� ����� ������ ���ؼ� ���ȴ�.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTSError.h"
#include "MPacketID.h"

// ������
PKTSError::PKTSError()
{
	nSize = szPKTSError - szMPacketSize;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTSError::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTSError );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTSError::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nError		= htonl( nError );

	oStream.write( (const char*)this, szPKTSError );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// debug message
string PKTSError::toString() const
{
	StringStream msg;
	msg << "Result("
		<< "ErrorCode:" << nError
		<< ")";

	return msg.toString();
}

