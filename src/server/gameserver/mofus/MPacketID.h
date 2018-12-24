/////////////////////////////////////////////////////////////////////////////
// filename	: MPacketID.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_ID_H__
#define __MPACKET_ID_H__

// MPacketID send enum
enum
{
	PTC_CONNECT_ASK = 0x01,			// ���Ӽ����� ���� ��û
	PTC_LOGOUT = 0x11,				// ���Ӽ����� ���� ����
	PTC_USERINFO = 0x20,			// ���� ���� ��û
	PTC_RECEIVE_OK = 0x30,			// ���� �ڷῡ ���� ó�� ����
	PTC_RESULT = 0x40,				// ���������� ���۹��� �ڷῡ ���� ó�� ����
	PTC_ERROR = 0xFF,				// ���Ӽ������� ó�� ������ ���� ����� ������ ���ؼ� ���ȴ�.

	PTC_SEND_MAX
};

// MPacketID recv enum
enum
{
	PTS_CONNECT_ACCEPT = 0x01,		// ���Ӽ����� ���� ��û �㰡
	PTS_POWERPOINT = 0x20,			// ��û�� ����
	PTS_ERROR = 0xFF,				// ���� ���� �˸�

	PTC_MAX
};

#endif

