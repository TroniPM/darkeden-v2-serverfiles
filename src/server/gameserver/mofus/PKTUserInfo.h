/////////////////////////////////////////////////////////////////////////////
// Filename : PKTUserInfo.h
// Desc		: �¶��� ���� ����ID, ĳ���͸�, ȸ���̸�, ������ ������
// 			  �Ŀ��� ������ ���� ȸ���� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_USERINFO_H__
#define __PKT_USERINFO_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ ����
struct _PKT_USERINFO
{
	int nSize;
	int nCode;
	char sJuminNo[20];		// �ֹι�ȣ
	char sHandPhone[12];	// �ڵ��� ��ȣ
	int nIndex;				// �¶��λ��� ���Ǹ� ���� �ε���
};

const int szPKTUserInfo = sizeof(_PKT_USERINFO);

// class PKTUserInfo
class PKTUserInfo : public _PKT_USERINFO, public MPacket
{
public:
	// ������
	PKTUserInfo();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTUserInfo - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTUserInfo;
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
	// set ssn & cellnum
	void setSSN( const string& ssn );
	void setCellNum( const string& cellnum );
};

#endif

