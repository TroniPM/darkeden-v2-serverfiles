/////////////////////////////////////////////////////////////////////////////
// Filename : PKTUserInfo.cpp
// Desc		: �¶��� ���� ����ID, ĳ���͸�, ȸ���̸�, ������ ������
// 			  �Ŀ��� ������ ���� ȸ���� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTUserInfo.h"
#include "MPacketID.h"
#include "Assert.h"

// ������
PKTUserInfo::PKTUserInfo()
{
	memset( this, 0, szPKTUserInfo );

	nSize = szPKTUserInfo - szMPacketSize;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTUserInfo::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTUserInfo );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nIndex		= ntohl( nIndex );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTUserInfo::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nIndex		= htonl( nIndex );

	oStream.write( (const char*)this, szPKTUserInfo );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nIndex		= ntohl( nIndex );
}

// debug message
string PKTUserInfo::toString() const
{
	char str[32];
	StringStream msg;
	msg << "UserInfo(";
	memcpy( str, sJuminNo, 20 ); str[20] = '\0';
	msg << "JuminNo:" << str;
	memcpy( str, sHandPhone, 12); str[12] = '\0';
	msg << ",HandPhone:" << str
		<< ",Index:" << nIndex
		<< ")";

	return msg.toString();
}

// set ssn
void PKTUserInfo::setSSN( const string& ssn )
{
	Assert( ssn.size() > 0 && ssn.size() <= 20 );

	strcpy( sJuminNo, ssn.c_str() );
}

// set cellnum
void PKTUserInfo::setCellNum( const string& cellnum )
{
	Assert( cellnum.size() > 0 && cellnum.size() <= 12 );

	strcpy( sHandPhone, cellnum.c_str() );
}

