#ifndef __QUEST_STATUS_INFO_H__
#define __QUEST_STATUS_INFO_H__

#include "Types.h"

#include "Packet.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#include <list>

#define MAX_MISSION_NUM	100

struct MissionInfo
{
	enum Status
	{
		HIDE = 0,			// �������� ����
		CURRENT,			// ���� �ؾ� �Ǵ� �̼� (������)
		SUCCESS,			// �̹� ������ �̼�
		FAIL,				// ����
	};

	BYTE	m_Condition;	// ��� ���ǿ� �ִ°� 0 : Happen, 1 : Complete, 2 : Fail, 3 : Reward
	WORD	m_Index;		// �ش� ������ ���° element�ΰ�
	BYTE	m_Status;		// ���� ����

	string	m_StrArg;		// ����� ���ڿ�
	DWORD	m_NumArg;		// ����� ����

	MissionInfo() : m_StrArg(""), m_NumArg(0) { }

	void read(SocketInputStream& iStream) throw(ProtocolException, Error)
	{
		iStream.read(m_Condition);
		iStream.read(m_Index);
		iStream.read(m_Status);

		BYTE szSTR;
		iStream.read(szSTR);
		if ( szSTR != 0 ) iStream.read(m_StrArg, szSTR);

		iStream.read(m_NumArg);
	}

	void write(SocketOutputStream& oStream) 
	{
		oStream.write(m_Condition);
		oStream.write(m_Index);
		oStream.write(m_Status);

		BYTE szSTR = m_StrArg.size();
		oStream.write( szSTR );
		if ( szSTR != 0 ) oStream.write( m_StrArg );

		oStream.write( m_NumArg );

		cout << "write mission : " << m_NumArg << " , " << m_StrArg << endl;
	}

	PacketSize_t getSize() const { return szBYTE + szWORD + szBYTE + szBYTE + m_StrArg.size() + szDWORD; }
	static PacketSize_t getMaxSize() { return szBYTE + szWORD + szBYTE + szBYTE + 255 + szDWORD; }
};

class QuestStatusInfo
{
public:
	enum Status
	{
		CANNOT = 0,		// ���� �Ұ���
		CAN_ACCEPT,		// ���డ��
		DOING,			// ������
		SUCCESS,		// ���� (���� ������� ����)
		COMPLETE,		// �Ϸ� (�������, ����� �Ұ���)
		FAIL,			// ���� (����� �Ұ���)
		CAN_REPLAY,		// ����� ����
	};

	QuestStatusInfo(DWORD qID) : m_QuestID(qID), m_Status(CANNOT) { }

	void read(SocketInputStream& iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream& oStream) ;
	PacketSize_t getSize() const;
	static PacketSize_t getMaxSize();

protected:
	DWORD	m_QuestID;
	BYTE	m_Status;	// ���� enum ����
	list<MissionInfo*>	m_Missions;
};

#endif
