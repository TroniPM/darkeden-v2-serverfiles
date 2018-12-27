//--------------------------------------------------------------------------------
// 
// Filename    : CUBeginUpdate.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_BEGIN_UPDATE_H__
#define __CU_BEGIN_UPDATE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "UpdateManager.h"

//--------------------------------------------------------------------------------
//
// class CUBeginUpdate;
//
// ������Ʈ������ ������ Ŭ���̾�Ʈ�� ���ʷ� ������ ��Ŷ�̴�. ���ο� Ŭ���̾�Ʈ
// ������ ��� �ִ�. 
//
//--------------------------------------------------------------------------------

class CUBeginUpdate : public Packet {
public:
	enum TYPE
	{
		OLD_UPDATE,
		ONE_VERSION_KEY_BACK,
		TWO_VERSION_KEY_FRONT
	};

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) ;

	// �������κ��� ���� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( Socket * pSocket ) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_CU_BEGIN_UPDATE; }
	
	// get packet's body size
	PacketSize_t getPacketSize ()  { return szWORD + szWORD + szWORD; }

	//
	static PacketSize_t getPacketMaxSize ()  { return szWORD + szWORD + szWORD; }

	// get packet name
	string getPacketName ()  { return "CUBeginUpdate"; }
	
	// get packet's debug string
	string toString () ;

public :

	// get/set client version
	WORD getVersion ()  { return m_Version; }
	void setVersion ( WORD version )  { m_Version = version; }

	// get/set client version
	WORD getGuildVersion ()  { return m_GuildVersion; }
	void setGuildVersion ( WORD version )  { m_GuildVersion = version; }

	WORD getInfoVersion ()  { return m_InfoVersion; }
	void setInfoVersion ( WORD version )  { m_InfoVersion = version; }

	TYPE getType() const { return m_Type; }

private :

	// Ŭ���̾�Ʈ ����
	WORD m_Version;
	// ��� ����
	WORD m_GuildVersion;
	// ���� ����
	WORD m_InfoVersion;

	TYPE m_Type;

};


//--------------------------------------------------------------------------------
//
// class CUBeginUpdateFactory;
//
// Factory for CUBeginUpdate
//
//--------------------------------------------------------------------------------

class CUBeginUpdateFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new CUBeginUpdate(); }

	// get packet name
	string getPacketName ()  { return "CUBeginUpdate"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_CU_BEGIN_UPDATE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  { return szWORD + szWORD + szWORD; }

};


//--------------------------------------------------------------------------------
//
// class CUBeginUpdateHandler;
//
//--------------------------------------------------------------------------------

class CUBeginUpdateHandler {

public :

	// execute packet's handler
	static void execute ( CUBeginUpdate * pPacket , Player * pPlayer ) ;
	static void scan_Dir( const string Directory, CUBeginUpdate * pPacket , UpdateManager * pUpdateManager, bool bHttpPatch, bool bUpdaterPatch ) ;

};

#endif
