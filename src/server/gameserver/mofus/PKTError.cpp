/////////////////////////////////////////////////////////////////////////////
// Filename : PKTError.cpp
// Desc		: �Ŀ�¯ �������� ������ ���� ����� ������ ���ؼ� ���ȴ�.
// 			  �¶��� ���������� ���� ������ �ϰ� ó���ϰ� ��κ�
// 			  ����׿����� ���
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTError.h"
#include "MPacketID.h"

// ������
PKTError::PKTError()
{
	nSize = szPKTError - szMPacketSize;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTError::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTError );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTError::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nError		= htonl( nError );

	oStream.write( (const char*)this, szPKTError );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nError		= ntohl( nError );
}

// debug message
string PKTError::toString() const
{
	StringStream msg;
	msg << "Result("
		<< "ErrorCode:" << nError
		<< ")";

	return msg.toString();
}

