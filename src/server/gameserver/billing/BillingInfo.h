#ifndef __BILLING_INFO_H__
#define __BILLING_INFO_H__

#include <string>
using namespace std;

#include "types/ServerType.h"

#ifdef __NETMARBLE_SERVER__
#define __CONNECT_BILLING_SYSTEM__
#endif
//#define __COUT_BILLING_SYSTEM__

#ifdef __GAME_SERVER__
	#define LOGFILE_BILLING_PLAYER	"billingPlayerGame.txt"
	#define LOGFILE_BILLING_PACKET	"billingPacketGame.txt"
#elif defined(__LOGIN_SERVER__)
	#define LOGFILE_BILLING_PLAYER	"billingPlayerLogin.txt"
	#define LOGFILE_BILLING_PACKET	"billingPacketLogin.txt"
#else
	#define LOGFILE_BILLING_PLAYER	"billingPlayer.txt"
	#define LOGFILE_BILLING_PACKET	"billingPacker.txt"
#endif

////////////////////////////////////////////////////////////////////////////////
// Packet_Type�� ���� ��(G=GameServer, B=BillingServer)
////////////////////////////////////////////////////////////////////////////////
enum BillingPacketType
{
	BILLING_PACKET_LOGIN	= 0x00000001,	// ���ӿ� ���ö�		(G->B �̸� B->G)
	BILLING_PACKET_LOGOUT	= 0x00000002,	// ���ӿ��� ������		(G->B only)
	BILLING_PACKET_POLLING	= 0x00000003,	// GameServer������ 	(��� ����)
	BILLING_PACKET_INIT		= 0x00000004,	// ���Ӽ��� ó�� �㶧	(G->B only)
	BILLING_PACKET_REMAIN	= 0x00000005,	// ���� �ð� �����ش�.	(B->G only)
	BILLING_PACKET_CHECK	= 0x00000006,	// ���� �� üũ			(B->G �̸� G->B)
	BILLING_PACKET_LOGIN_CHECK	= 0x00000008,	// ���� �� üũ			(G->B �̸� B->G(LoginVerify(Type 1)))

	BILLING_PACKET_MAX
};

////////////////////////////////////////////////////////////////////////////////
// BILLING_PACKET_LOGIN�� Result��
////////////////////////////////////////////////////////////////////////////////
enum BillingResultLogin {
	BILLING_RESULT_LOGIN_OK				= 0,	// ���� ����
	BILLING_RESULT_LOGIN_DB_ERROR		= 2,	// DB�� ���� �Ұ�
	BILLING_RESULT_LOGIN_NETWORK_ERROR	= 3,	// ��Ʈ��ũ ����
	BILLING_RESULT_LOGIN_NO_ACCOUNT		= 10,	// ���� ���� ����
	BILLING_RESULT_LOGIN_NO_CASH		= 11,	// �ܾ� ����
	BILLING_RESULT_LOGIN_NO_SESSION		= 12,	// ���� ����
	BILLING_RESULT_LOGIN_BAD_PACKET		= 20,	// ���� �������� ��Ŷ
	BILLING_RESULT_LOGIN_COM_ERROR		= 25,	// COM Error
	BILLING_RESULT_LOGIN_NO_RESPONSE	= 26,	// �ð�(30��)���� �������
	BILLING_RESULT_LOGIN_NO_MACHINE		= 27,	// �ش� ��� ���� �Ұ�
	BILLING_RESULT_LOGIN_BAD_GAME_NO	= 30,	// ��Ŷ�� ���� �ѹ��� ���� ������ ��ϵ� ���ӹ�ȣ�� �ٸ�
	BILLING_RESULT_LOGIN_ACCOUNT_ERROR	= 31,	// ���� ��ī��Ʈ�� ���� ����
//	BILLING_RESULT_LOGIN_DUPLICATE		= 32,	// �������� �Ұ�
	BILLING_RESULT_LOGIN_DENY			= 33,	// ��� �Ұ�(���� ������ ����)
	BILLING_RESULT_LOGIN_TIME_OVER		= 34,	// ��ȿ �Ⱓ ����
	BILLING_RESULT_LOGIN_BUSY			= 35,	// ��ٸ��� ����� ����
	BILLING_RESULT_LOGIN_UNKNOWN_ERROR	= 100,	// ���� ���� ���� ����
	BILLING_RESULT_LOGIN_IP_COM_ERROR	= 200,	// IPȮ�� �� COM Error
	BILLING_RESULT_LOGIN_IP_ERROR		= 201,	// IP ������ ���� ����
	BILLING_RESULT_LOGIN_KEY_COM_ERROR	= 210,	// ����Ű Ȯ���� COM ����
	BILLING_RESULT_LOGIN_NO_KEY			= 211,	// ����Ű ����

	BILLING_RESULT_LOGIN_MAX
};

////////////////////////////////////////////////////////////////////////////////
// BILLING_PACKET_REMAIN�� Result��
////////////////////////////////////////////////////////////////////////////////
enum BillingResultRemain {
	BILLING_RESULT_REMAIN_DISCONNECT	= -4,	// ���� ����
	BILLING_RESULT_REMAIN_RESERVE		= -3,	// ���ο� �������� ��� ����
	BILLING_RESULT_REMAIN_DUPLICATE		= -2,	// �ߺ� �α���
	BILLING_RESULT_REMAIN_REFUND		= -1,	// ȯ�� �Ǿ���.
	BILLING_RESULT_REMAIN_NONE			= 0,	// ���� �ð� ����.
	BILLING_RESULT_REMAIN_TIME			= 1,	// ���������� ���� �ð�

	BILLING_RESULT_REMAIN_MAX
};

////////////////////////////////////////////////////////////////////////////////
// BILLING_PACKET_CHECK�� Result��
////////////////////////////////////////////////////////////////////////////////
enum BillingResultCheck {
	BILLING_RESULT_CHECK_PLAYING		= 0,	// ���� �����
	BILLING_RESULT_CHECK_DISCONNECTED	= 1,	// ����� �����

	BILLING_RESULT_CHECK_MAX
};

////////////////////////////////////////////////////////////////////////////////
// User_CC ��
////////////////////////////////////////////////////////////////////////////////
enum BillingUserCC
{
	BILLING_USER_METROTECH,		// ����~
	BILLING_USER_NETMARBLE,		// �ݸ��� ����

	BILLING_USER_MAX
};

const string BillingUserCC2String[BILLING_USER_MAX] =
{
	"DE", 		// BILLING_USER_METROTECH,		// ����~
	"NM"		// BILLING_USER_NETMARBLE,		// �ݸ��� ����
};

////////////////////////////////////////////////////////////////////////////////
// BillingInfo == _AUTH_GAME
////////////////////////////////////////////////////////////////////////////////
struct _AUTH_GAME {
	mutable int 	Packet_Type;		// ��Ŷ Ÿ��
	mutable int 	Result;				// ó�������
	char 			S_KEY[32];			// ����Ű�� ����Ҷ��� ����Ѵ�.
	char 			Session[32];		// guid
	char 			User_CC[4];			// ���� �ڵ�
	char 			User_No[20];		// ����� ��ȣ�� �ֹε�Ϲ�ȣ
	char 			User_ID[40]; 		// ����� ���̵�
	char 			User_IP[24];		// ����� ���� ������
	char 			User_Gender;		// ����� ����
	char 			User_Status[3];		// ����� ����
	char 			User_PayType[2];	// ���� ���� ���� ������� ��� "F0"
	mutable int 	User_Age;			// ����� ����
	mutable int 	Game_No;			// ���� ��ȣ(���� DB�� ��ϵ� ��ȣ)
	char 			Bill_PayType[2];	// ���� ��� "A0" �ĺ�, "D0" ����, "P0" ����
	char 			Bill_Method[2];		// ���� ���
	char 			Expire_Date[12];	// ���� ������ YYYYMMDDHHMM
	mutable int 	Remain_Time;		// ����:���� �ð�(��) ����:���� ������ȣ

};

typedef _AUTH_GAME BillingInfo;

const int szBillingInfo = sizeof(BillingInfo);

#endif
