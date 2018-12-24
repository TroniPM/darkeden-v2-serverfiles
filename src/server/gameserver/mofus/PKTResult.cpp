/////////////////////////////////////////////////////////////////////////////
// Filename : PKTResult.cpp
// Desc		: ��������� ���� ���� �ڷῡ ���� ó�� ���θ� �Ŀ��� ������
// 			  ����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTResult.h"
#include "MPacketID.h"

// ������
PKTResult::PKTResult()
{
	nSize = szPKTResult - szMPacketSize;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTResult::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTResult );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTResult::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTResult );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTResult::toString() const
{
	return "Result()";
}

