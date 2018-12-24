/////////////////////////////////////////////////////////////////////////////
// Filename : PKTPowerPoint.h
// Desc		: �¶��� �������κ��� ���۵Ǿ�� �����͸� ���� �Ŀ��� DB����
// 			  ������ ���� �¶��λ�� �Ѱ��ش�.
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_POWERPOINT_H__
#define __PKT_POWERPOINT_H__

// include files
#include "MPacket.h"
#include "Assert.h"

// ��Ŷ ����
struct _PKT_POWERPOINT
{
	int nSize;
	int nCode;
	int nMoDataCode;				// �ڷ� ó���� ���� Index, Unique ��
	char sPhoneNo[12];				// �Ŀ��� ����Ʈ�� ����� ������ �ڵ��� ��ȣ
	char sMemID[20];				// �Ŀ��� ���� ���� ID
	int nMatchingCode;				// �Ŀ��� ���̺� ��Ī �ڵ�
	char sMoGameName[20];			// �¶��� ���Ӱ� ������ ����� ���Ӹ�
	int nMoGameCode;				// �¶��� ���Ӱ� ������ ����� �����ڵ�
	int nOnGameCode;				// �¶��� ���� �ڵ�
	char sOnGameName[20];			// �¶��� ���Ӹ�
	int nOnGameSerCode;				// �¶��� ���� ���� �ڵ�
	char sOnGameSerName[20];		// �¶��� ���� ���� ��
	char sOnGameID[20];				// �¶��� ���� ���̵�
	char sCharName[40];				// �¶��� ���� ĳ���͸�
	int nOnAbilityCode;				// �¶��� ���� ���� �ɷ�ġ �ڵ�
	char sOnAbilityName[20];		// �¶��� ���� ���� �ɷ�ġ��
	int nPowerPoint;				// ������ ������ �Ŀ��� ����Ʈ
	char sInputDate[20];			// ������ ����Ϸ� �Է��� �Ŀ��� ����Ʈ �Է� �ð�
	int nIndex;						// �¶��λ��� ���Ǹ� ���� �ε���
	int nContinue;					// ���� ������ ����. 1:����. 0:����
};

const int szPKTPowerPoint = sizeof(_PKT_POWERPOINT);

// class PKTPowerPoint
class PKTPowerPoint : public _PKT_POWERPOINT, public MPacket
{
public:
	// ������
	PKTPowerPoint();

public:
	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	MPacketID_t getID() const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getSize() const
	{
		return szPKTPowerPoint - szMPacketSize;
	}

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	MPacket* create()
	{
		MPacket* pPacket = new PKTPowerPoint;
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
	// get methods
	bool isContinue() const { return nContinue == 1; }

	// get PowerPoint
	int getPowerPoint() const { return nPowerPoint; }

	// get GameCode
	int getGameCode() const { return nOnGameCode; }

	// get GameServerCode
	int getGameServerCode() const { return nOnGameSerCode; }

	// get Character Name
	const char* getCharacterName() const { return (const char*)sCharName; }
};

#endif

