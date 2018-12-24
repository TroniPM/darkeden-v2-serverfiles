/////////////////////////////////////////////////////////////////////////////
// Filename : PKTLogout.cpp
// Desc		: ������ �������� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTLogout.h"
#include "MPacketID.h"

// ������
PKTLogout::PKTLogout()
{
	nSize = szPKTLogout - szMPacketSize;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTLogout::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTLogout );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTLogout::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );

	oStream.write( (const char*)this, szPKTLogout );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
}

// debug message
string PKTLogout::toString() const
{
	return "Logout()";
}

