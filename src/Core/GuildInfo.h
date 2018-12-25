//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildInfo.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_INFO_H__
#define __GUILD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class GuildInfo;
//
// Ŭ���̾�Ʈ�� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GuildInfo {

public :
	
	// constructor
	GuildInfo ();
	
	// destructor
	~GuildInfo ();

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize ();

	static uint getMaxSize() throw() {
//		return ( szGuildID + szBYTE + 30 + szBYTE + 20 + szBYTE + szBYTE + 11 ) * 256 + szBYTE;
		return szGuildID + szBYTE + 30 + szBYTE + 20 + szBYTE + szBYTE + 11;
	}

	// get packet's debug string
	string toString () ;

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Guild Name
	string getGuildName()  { return m_GuildName; }
	void setGuildName( const string& GuildName ) throw() { m_GuildName = GuildName; }

	// get/set Guild Master
	string getGuildMaster()  { return m_GuildMaster; }
	void setGuildMaster( const string& GuildMaster ) throw() { m_GuildMaster = GuildMaster; }

	// get/set Guild Member Count
	BYTE getGuildMemberCount()  { return m_GuildMemberCount; }
	void setGuildMemberCount( BYTE GuildMemberCount ) throw() { m_GuildMemberCount = GuildMemberCount; }

	// get/set Guild Expire Date
	string getGuildExpireDate()  { return m_GuildExpireDate; }
	void setGuildExpireDate( const string& GuildExpireDate ) throw() { m_GuildExpireDate = GuildExpireDate; }


private :

	// ��� ���̵�
	GuildID_t m_GuildID;

	// ��� �̸�
	string m_GuildName;

	// ��� ������
	string m_GuildMaster;

	// ��� ��� ī��Ʈ
	BYTE m_GuildMemberCount;

	// ��� Expire Date
	string m_GuildExpireDate;

};

#endif
