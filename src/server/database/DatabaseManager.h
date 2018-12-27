//////////////////////////////////////////////////////////////////////////////
// Filename    : DatabaseManager.h
// Written By  : elca
// Description : ����Ÿ���̽� �Ŵ���
//////////////////////////////////////////////////////////////////////////////

#ifndef __DATABASE_MANAGER_H__
#define __DATABASE_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Connection.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class DatabaseManager;
//////////////////////////////////////////////////////////////////////////////

class DatabaseManager 
{
public:
	DatabaseManager() ;
	~DatabaseManager() ;
	
public:
	void init();
	void addConnection(int TID, Connection * pConnection) ;
	void addDistConnection(int TID, Connection * pConnection) ;
	void addCBillingConnection(int TID, Connection * pConnection) ;
//	void addPCRoomConnection(int TID, Connection * pConnection) ;

	Connection* getConnection(const string& ip) ;
	Connection* getDistConnection(const string& ip) ;
	Connection* getCBillingConnection(const string& ip) ;
//	Connection* getPCRoomConnection(const string& ip) ;
	Connection* getUserInfoConnection(void)  { return m_pUserInfoConnection; }
	void	executeDummyQuery(Connection* pConnection);

	//--------------------------------------------------------------------
	// * elca's NOTE
	// �α��� ���������� ĳ������ ������ ��� �������� �˾Ƴ��� ���Ͽ�
	// DB�� ��ġ�� �˾Ƴ� �´�.
	// ���� DB������ DB�� ��ġ�� �����ϴ� Table�� �����ؾ� �Ѵ�.
	// GameServerIP�� �̾� �� ���� ������ DB�� GameServer�� �ٸ� ��츦
	// �����Ͽ� Ȯ�强�� ����Ѵ�.
	//--------------------------------------------------------------------

	//--------------------------------------------------------------------
	// * elca's NOTE
	// �� ���� ������ ��� Parent/Main DB���� �˸� �ȴ�.
	// ���� DB ������ ���� ���̵�� ������ 0 ���̶�� �����ϰ�
	// ���� DB ������ ������ 0 �� ���ڷ� �ѱ��.
	// ���� ������ ��� �� 0 ���� Ŀ�ؼǸ� ������ ������ �ȴ�.
	// Ȥ�ó� �ϴ� ������ ����� �ֱ� ������ ���� �ٸ� Ŀ�ؼ��� ���� �ʵ���
	// ���� �ϵ��� �Ѵ�.
	// �Ϲ� ���� ���������� ������ ������ ���� �������� �ֱ� ������
	// �Ű澲�� �ʵ��� �Ѵ�.
	//--------------------------------------------------------------------
	Connection* getConnection( int TID ) ;
//	void addConnection(WorldID_t WorldID, Connection * pConnection) ;

private:
	// �� �����庰�� �����ϴ� DB ����
	hash_map<int, Connection*> m_Connections;

	// �� �����庰�� �����ϴ� Distribute DB ����
	hash_map<int, Connection*> m_DistConnections;

//	hash_map<WorldID_t, Connection*> m_WorldConnections;
	hash_map<int, Connection*> m_WorldConnections;

	// �� �����庰�� �����ϴ� CBilling DB ����
	hash_map<int, Connection*> m_CBillingConnections;

	// PC�� ���տ� DB ����
//	hash_map<int, Connection*> m_PCRoomConnections;

	// �� ���庰�� �����ϴ� DB ����

	// ���� ó�� �����Ǵ� �⺻ DB ����
	Connection* m_pDefaultConnection;

	// ���� ó�� �����Ǵ� �� ���� DB�� �⺻ ����
	Connection* m_pWorldDefaultConnection;

	// ����� ��� ���� DB ����
	Connection* m_pUserInfoConnection;

	Connection* m_pDistConnection;

	// PC�� ���տ� DB ���� default. �α��� �������� ����.
//	Connection* m_pPCRoomConnection;

	mutable Mutex m_Mutex;
};

extern DatabaseManager * g_pDatabaseManager;

#endif
