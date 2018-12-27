//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyNickname.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_NICKNAME_H__
#define __CG_MODIFY_NICKNAME_H__

#include "Packet.h"
#include "PacketFactory.h"

#include "NicknameInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNickname;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNickname : public Packet 
{
public:
	CGModifyNickname() ;
	~CGModifyNickname() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_MODIFY_NICKNAME; }
	PacketSize_t getPacketSize()  { return szObjectID + szBYTE + m_Nickname.size(); }
	string getPacketName()  { return "CGModifyNickname"; }
	string toString() ;
	
public:
	ObjectID_t	getItemObjectID() const { return m_ItemObjectID; }
	void		setItemObjectID(WORD id) { m_ItemObjectID = id; }

	string		getNickname() const { return m_Nickname; }
	void		setNickname(const string& name) { m_Nickname = name; }
private:
	ObjectID_t	m_ItemObjectID;
	string		m_Nickname;
};

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNicknameFactory;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNicknameFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGModifyNickname(); }
	string getPacketName()  { return "CGModifyNickname"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MODIFY_NICKNAME; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szBYTE + MAX_NICKNAME_SIZE; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGModifyNicknameHandler;
//////////////////////////////////////////////////////////////////////////////

class CGModifyNicknameHandler 
{
public:
	static void execute(CGModifyNickname* pPacket, Player* player) ;
};

#endif
