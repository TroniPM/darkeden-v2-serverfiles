/////////////////////////////////////////////////////////////////////////////
// Filename : PKTResult.h
// Desc		: ���������� ���� ���� �ڷῡ ���� ó�� ���θ� �Ŀ��� ������
// 			  ����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_RESULT_H__
#define __PKT_RESULT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ ����
struct _PKT_RESULT
{
	int nSize;			// ��Ŷ ��ü�� ũ��
	int nCode;			// ��Ŷ �ڵ�
};

const int szPKTResult = sizeof(_PKT_RESULT);

// class PKTResult
class PKTResult : public _PKT_RESULT, public MPacket
{
public:
	// ������
	PKTResult();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTResult - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTResult;
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

