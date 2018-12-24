/////////////////////////////////////////////////////////////////////////////
// Filename : PKTError.h
// Desc		: �Ŀ�¯ �������� ������ ���� ����� ������ ���ؼ� ���ȴ�.
// 			  �¶��� ���������� ���� ������ �ϰ� ó���ϰ� ��κ�
// 			  ����׿����� ���
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_ERROR_H__
#define __PKT_ERROR_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ���� �ڵ�
enum MERR_CODE
{
	MERR_SERVER = 0x01,			// ������ ��� ������ ���� ����������
								// �������� ���ϴ� ��Ȳ
	MERR_CONFIRM = 0x02,		// �¶��� ���� �ڵ�� Ȯ�� �� ������ ���
	MERR_PACKET = 0x03,			// �߸��� ��Ŷ�� ��/���ŵ� ���
	MERR_PROCESS = 0x04,		// ���� ó�� ���� ( ex: DB ���� )
	MERR_SEARCH = 0x05,			// �Ŀ�¯ ȸ���� �ƴ� ���
	MERR_NULLPOINT = 0x06,		// �Ŀ�¯ ȸ���̳� ������ �Ŀ�¯ ����Ʈ��
								// ���� ���
	MERR_MATCHING = 0x07,		// ��Ī ���� ���� (ex: ȸ�� ��Ī ������ ����)
								// Ȩ���������� ��Ī�� �����ϴ� ������ ����.
};

// ��Ŷ ����
struct _PKT_ERROR
{
	int nSize;			// ��Ŷ ��ü�� ũ��
	int nCode;			// ��Ŷ �ڵ�
	int nError;			// ���� �ڵ�
};

const int szPKTError = sizeof(_PKT_ERROR);

// class PKTError
class PKTError : public _PKT_ERROR, public MPacket
{
public:
	// ������
	PKTError();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTError - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTError;
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
	// get error code
	int getErrorCode() const { return nError; }
};

#endif

