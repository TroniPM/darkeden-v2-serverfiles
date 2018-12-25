//----------------------------------------------------------------------
// 
// Filename    : GMServerInfo.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GM_SERVER_INFO_H__
#define __GM_SERVER_INFO_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"

typedef struct _ZONEUSERDATA
{
	ZoneID_t ZoneID;
	WORD	 UserNum;

} ZONEUSERDATA;

//----------------------------------------------------------------------
//
// class GMServerInfo;
//
// �α��� �������� ����ڰ� ���� ������ �����Ϸ��� �� ��, �α��� ������
// �� ���� �������� � �ּҿ��� � ����ڰ� � ũ��ó�� �α�����
// ���̴�.. ��� �˷��ִ� ��Ŷ�̴�.
//
// *CAUTION*
//
// ���� ũ��ó �̸��� �ʿ��Ѱ�? �ϴ� �ǹ��� ���� �� �ְڴµ�, ������ ����
// ��츦 ��������� �ʿ��ϰ� �ȴ�. �α��� �����κ��� Slot3 ĳ���͸� ����
// �س���, ������ ���� ������ �����ؼ��� SLOT2 ĳ���͸� �ε��ش޶�� ��
// ���� �ִ� ���̴�. �̸� ���� ���ؼ�, CLSelectPC�� ������ ĳ���͸� 
// ���� �������� �˷���� �ϸ�, CGConnect ������ ĳ���� ���̵� �����ؼ�
// �ٷ� �ε��ϵ��� �ؾ� �Ѵ�.
//
//----------------------------------------------------------------------

class GMServerInfo : public DatagramPacket {

public :
	GMServerInfo() throw();
	~GMServerInfo() throw();
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(Datagram & iDatagram) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(Datagram & oDatagram) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GM_SERVER_INFO; }
	
	// get packet name
	string getPacketName()  { return "GMServerInfo"; }
	
	PacketSize_t getPacketSize () const throw () { return szWorldID + szBYTE + m_ZoneCount*(szBYTE+szDWORD); }

	// get packet's debug string
	string toString() ;

public:

	// get/set playerID
	WorldID_t getWorldID()  { return m_WorldID; }
	void setWorldID(WorldID_t WorldID) throw() { m_WorldID= WorldID; }
	
	// get/set playerID
	BYTE getServerID()  { return m_ServerID; }
	void setServerID(BYTE ServerID) throw() { m_ServerID= ServerID; }
	
	BYTE getZoneUserCount(void)  { return m_ZoneCount; }

	void addZoneUserData(ZoneID_t ZoneID, DWORD value) throw();

	void popZoneUserData(ZONEUSERDATA& rData) throw();

	void clearList(void) throw() { m_ZoneCount = 0; m_ZoneUserList.clear(); }

private :

	// WorldID
	WorldID_t m_WorldID;

	// ServerID
	BYTE m_ServerID;

	BYTE            m_ZoneCount;
	list<ZONEUSERDATA> m_ZoneUserList;

	// Ŭ���̾�Ʈ�� IP

};


//////////////////////////////////////////////////////////////////////
//
// class GMServerInfoFactory;
//
// Factory for GMServerInfo
//
//////////////////////////////////////////////////////////////////////

class GMServerInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GMServerInfo(); }

	// get packet name
	string getPacketName()  { return "GMServerInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GM_SERVER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GMServerInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szWorldID + szBYTE + 255*(szBYTE+szDWORD); }

};


//////////////////////////////////////////////////////////////////////
//
// class GMServerInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GMServerInfoHandler {
	
public :

	// execute packet's handler
	static void execute(GMServerInfo* pPacket) throw(ProtocolException, Error);

};

#endif
