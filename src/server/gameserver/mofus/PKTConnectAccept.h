/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAccept.h
// Desc		: ���������� ���ӵǾ����� ��Ŷ���� �˷��ش�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ACCEPT_H__
#define __PKT_CONNECT_ACCEPT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ ����
struct _PKT_CONNECT_ACCEPT
{
	int nSize;		// ��Ŷ ��ü�� ũ��
	int nCode;		// ��Ŷ �ڵ�
};

const int szPKTConnectAccept = sizeof(_PKT_CONNECT_ACCEPT);

// class PKTConnectAccept
class PKTConnectAccept : public _PKT_CONNECT_ACCEPT, public MPacket
{
public:
	// ������
	PKTConnectAccept();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTConnectAccept - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ�Ѵ�.
	MPacket* create()
	{
		MPacket* pPacket = new PKTConnectAccept;
		Assert( pPacket != NULL );
		return pPacket;
	}

	// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
	void read( SocketInputStream& iStream );

	// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write( SocketOutputStream& oStream );

	// debug message
	string toString() const;
};

#endif

