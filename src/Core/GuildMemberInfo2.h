//////////////////////////////////////////////////////////////////////
// 
// Filename    : GuildMemberInfo2.h 
// Written By  : 
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GUILD_MEMBER_INFO2_H__
#define __GUILD_MEMBER_INFO2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class GuildMemberInfo2;
//
// Ŭ���̾�Ʈ�� ��� ����Ʈ�� ������.
//
//////////////////////////////////////////////////////////////////////

class GuildMemberInfo2 {

public :
	
	// constructor
	GuildMemberInfo2 ();
	
	// destructor
	~GuildMemberInfo2 ();

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) ;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize ();

	static uint getMaxSize()  {
		return szGuildID + szBYTE + 20 + szGuildMemberRank + szbool;
	}

	// get packet's debug string
	string toString () ;

	// get/set guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Name
	string getName()  { return m_Name; }
	void setName( const string& Name )  { m_Name = Name; }

	// get/set GuildMemberRank
	GuildMemberRank_t getRank()  { return m_Rank; }
	void setRank( GuildMemberRank_t rank )  { m_Rank = rank; }

	// get/set logon
	bool getLogOn() const { return m_bLogOn; }
	void setLogOn( bool logOn ) { m_bLogOn = logOn; }

private :

	// ��� ���̵�
	GuildID_t m_GuildID;

	// �̸�
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_Rank;

	// log on
	bool m_bLogOn;

};

#endif
