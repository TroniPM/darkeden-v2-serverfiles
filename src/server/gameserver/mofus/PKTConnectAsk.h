/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAsk.h
// Desc		: �¶��� ���� ������ �Ŀ�¯ ������ �ڻ��� ���� �ڵ�� �Բ�
// 			  ������ ��û�Ѵ�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ASK_H__
#define __PKT_CONNECT_ASK_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ ����
struct _PKT_CONNECT_ASK
{
	int nSize;			// ��Ŷ ��ü�� ũ��
	int nCode;			// ��Ŷ �ڵ�
	int nOnGameCode;	// ���۽����� �߱��� �¶��λ� ���� �ڵ� ��
};

const int szPKTConnectAsk = sizeof(_PKT_CONNECT_ASK);

// class PKTConnectASK
class PKTConnectAsk : public _PKT_CONNECT_ASK, public MPacket
{
public:
	// ������
	PKTConnectAsk();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTConnectAsk - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTConnectAsk;
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
	// get/set OnGameCode
	int getOnGameCode() const { return nOnGameCode; }
	void setOnGameCode( int onGameCode ) { nOnGameCode = onGameCode; }
};

#endif

