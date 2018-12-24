/////////////////////////////////////////////////////////////////////////////
// Filename : PKTSError.h
// Desc		: �¶��� �������� ó�� ������ ���� ����� ������ ���ؼ� ���ȴ�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_SERROR_H__
#define __PKT_SERROR_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ���� �ڵ�
enum MSERR_CODE
{
	MSERR_MATCH = 0x01,			// ȸ���� Ȯ�������� ������ ���� ��ġ ����
								// ���� ��� ( �� ��û�ڿ� �Ŀ�¯ ������
								// ��ġ ���� ���� ��� )
};

// ��Ŷ ����
struct _PKT_SERROR
{
	int nSize;			// ��Ŷ ��ü�� ũ��
	int nCode;			// ��Ŷ �ڵ�
	int nError;			// ���� �ڵ�
};

const int szPKTSError = sizeof(_PKT_SERROR);

// class PKTSError
class PKTSError : public _PKT_SERROR, public MPacket
{
public:
	// ������
	PKTSError();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTSError - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTSError;
		Assert( pPacket != NULL );
		return pPacket;
	}

	// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
	void read( SocketInputStream& iStream );

	// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write( SocketOutputStream& oStream );

	// debug message
	string toString() const;

public:
	// ���� �ڵ� ����
	void setErrorCode( int errorCode ) { nError = errorCode; }
};

#endif

