/////////////////////////////////////////////////////////////////////////////
// Filename : PKTLogout.h
// Desc		: ������ �������� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_LOGOUT_H__
#define __PKT_LOGOUT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ ����
struct _PKT_LOGOUT
{
	int nSize;		// ��Ŷ ��ü�� ũ��
	int nCode;		// ��Ŷ �ڵ�
};

const int szPKTLogout = sizeof(_PKT_LOGOUT);

// class PKTLogout
class PKTLogout : public _PKT_LOGOUT, public MPacket
{
public:
	// ������
	PKTLogout();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTLogout - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTLogout;
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

