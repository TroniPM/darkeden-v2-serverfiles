//////////////////////////////////////////////////////////////////////
// 
// Filename    : ServerGroupInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 인벤토리 아이템의 정보들
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
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class ServerGroupInfo {

public :
	
	// constructor
	ServerGroupInfo ();
	
	// destructor
	~ServerGroupInfo ();

public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read (SocketInputStream & iStream);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write (SocketOutputStream & oStream) ;

	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getSize ();

	static uint getMaxSize()  {
		return (szBYTE + szBYTE + 20 + szBYTE)* 37;
	}

	// get packet's debug string
	string toString () ;

	// get / set GroupID
	BYTE getGroupID()  { return m_GroupID; }
	void setGroupID(ServerGroupID_t GroupID)  { m_GroupID = GroupID; }

	// get / set GroupName
	string getGroupName()  { return m_GroupName; }
	void setGroupName(string GroupName)  { m_GroupName = GroupName; }

	// get / set Group Stat
	BYTE getStat()  { return m_Stat; }
	void setStat(BYTE Stat)  { m_Stat = Stat; }

private :

	// 그룹 아이디
	ServerGroupID_t m_GroupID;

	// 그룹 이름
	string m_GroupName;

	// 그룹의 상태
	BYTE	m_Stat;

};

#endif
