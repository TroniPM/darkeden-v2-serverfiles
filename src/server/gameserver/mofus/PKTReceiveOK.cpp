/////////////////////////////////////////////////////////////////////////////
// Filename : PKTReceiveOK.cpp
// Desc		: ���� �ڷῡ ���� ó�� ���θ� �Ŀ��� ������ ����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTReceiveOK.h"
#include "MPacketID.h"

// ������
PKTReceiveOK::PKTReceiveOK()
{
	nSize = szPKTReceiveOK - szMPacketSize;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTReceiveOK::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTReceiveOK );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTReceiveOK::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTReceiveOK );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTReceiveOK::toString() const
{
	return "ReceiveOK()";
}

