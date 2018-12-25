//////////////////////////////////////////////////////////////////////
// 
// Filename    : ServerGroupInfo.h 
// Written By  : elca@ewestsoft.com
// Description : �κ��丮 �������� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SERVER_GROUP_INFO_H__
#define __SERVER_GROUP_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class ServerGroupInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class ServerGroupInfo {

public :
	
	// constructor
	ServerGroupInfo () throw ();
	
	// destructor
	~ServerGroupInfo () throw ();

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return (szBYTE + szBYTE + 20 + szBYTE)* 37;
	}

	// get packet's debug string
	string toString () const throw ();

	// get / set GroupID
	BYTE getGroupID()  { return m_GroupID; }
	void setGroupID(ServerGroupID_t GroupID) throw() { m_GroupID = GroupID; }

	// get / set GroupName
	string getGroupName()  { return m_GroupName; }
	void setGroupName(string GroupName) throw() { m_GroupName = GroupName; }

	// get / set Group Stat
	BYTE getStat()  { return m_Stat; }
	void setStat(BYTE Stat) throw() { m_Stat = Stat; }

private :

	// �׷� ���̵�
	ServerGroupID_t m_GroupID;

	// �׷� �̸�
	string m_GroupName;

	// �׷��� ����
	BYTE	m_Stat;

};

#endif
