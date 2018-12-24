/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAsk.cpp
// Desc		: �¶��� ���� ������ �Ŀ�¯ ������ �ڻ��� ���� �ڵ�� �Բ�
// 			  ������ ��û�Ѵ�.
/////////////////////////////////////////////////////////////////////////////

// include files
#include "PKTConnectAsk.h"

// ������
PKTConnectAsk::PKTConnectAsk()
{
	nSize = szPKTConnectAsk - szMPacketSize;
	nOnGameCode = 10;
}

// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
void PKTConnectAsk::read( SocketInputStream& iStream )
{
	iStream.read( (char*)this, szPKTConnectAsk );

	// change order - network to host
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nOnGameCode	= ntohl( nOnGameCode );
}

// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
void PKTConnectAsk::write( SocketOutputStream& oStream )
{
	nCode = getID();

	// change order - host to network
//	nSize		= htonl( nSize );
//	nCode		= htonl( nCode );
//	nOnGameCode	= htonl( nOnGameCode );

	oStream.write( (const char*)this, szPKTConnectAsk );

	// restore order
//	nSize		= ntohl( nSize );
//	nCode		= ntohl( nCode );
//	nOnGameCode	= ntohl( nOnGameCode );
}

// debug message
string PKTConnectAsk::toString() const
{
	StringStream msg;

	msg << "ConnectAsk("
		<< "OnGameCode:" << nOnGameCode
		<< ")";

	return msg.toString();
}

