/////////////////////////////////////////////////////////////////////////////
// Filename : PKTReceiveOK.h
// Desc		: ���� �ڷῡ ���� ó�� ���θ� �Ŀ��� ������ ����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_RECEIVE_OK_H__
#define __PKT_RECEIVE_OK_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ����
struct _PKT_RECEIVE_OK
{
	int nSize;			// ��Ŷ ��ü�� ũ��
	int nCode;			// ��Ŷ �ڵ�
};

const int szPKTReceiveOK = sizeof(_PKT_RECEIVE_OK);

// class PKTReceiveOK
class PKTReceiveOK : public _PKT_RECEIVE_OK, public MPacket
{
public:
	// ������
	PKTReceiveOK();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTReceiveOK - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTReceiveOK;
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

