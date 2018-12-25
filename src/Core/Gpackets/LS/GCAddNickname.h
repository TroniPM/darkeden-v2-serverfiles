//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddNickname.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_NICKNAME_H__
#define __GC_ADD_NICKNAME_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "NicknameInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddNickname;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCAddNickname : public Packet 
{
public:
	GCAddNickname() throw();
	~GCAddNickname() throw();
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_NICKNAME; }
	PacketSize_t getPacketSize()  { return m_NicknameInfo.getSize(); }
	string getPacketName()  { return "GCAddNickname"; }
	string toString() ;

public:
	NicknameInfo&	getNicknameInfo() { return m_NicknameInfo; }

private :
	NicknameInfo	m_NicknameInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddNicknameFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddNicknameFactory : public PacketFactory 
{
public :
	GCAddNicknameFactory() throw() {}
	virtual ~GCAddNicknameFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCAddNickname(); }
	string getPacketName()  { return "GCAddNickname"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_NICKNAME; }
	PacketSize_t getPacketMaxSize()  { return NicknameInfo::getMaxSize(); }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddNicknameHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddNicknameHandler 
{
public:
	static void execute(GCAddNickname* pGCAddNickname, Player* pPlayer);

};

#endif
