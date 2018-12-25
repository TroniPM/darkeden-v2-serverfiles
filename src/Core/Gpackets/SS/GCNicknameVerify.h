//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNicknameVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NICKNAME_VERIFY_H__
#define __GC_NICKNAME_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

enum 
{
	NICKNAME_MODIFY_FAIL_NO_ITEM,
	NICKNAME_MODIFY_OK,

	NICKNAME_SELECT_FAIL_NO_SUCH,
	NICKNAME_SELECT_FAIL_FORCED,		// 운영자가 강제 지정한 닉네임은 맘대로 바꿀 수 없다.
	NICKNAME_SELECT_OK,

	NICKNAME_VERIFY_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCNicknameVerify
//////////////////////////////////////////////////////////////////////////////

class GCNicknameVerify : public Packet 
{

public:
	GCNicknameVerify() throw() { m_Code = NICKNAME_VERIFY_MAX; m_Parameter = 0;}
	virtual ~GCNicknameVerify() throw() {}

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;

	PacketID_t getPacketID()  { return PACKET_GC_NICKNAME_VERIFY; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCNicknameVerify"; }
	string toString() ;
	
public:
	BYTE getCode(void)  { return m_Code;}
	void setCode(BYTE code) throw() { m_Code = code;}

	uint getParameter(void)  { return m_Parameter; }
	void setParameter(uint parameter) throw() { m_Parameter = parameter; }

private: 
	BYTE m_Code;
	uint m_Parameter;
};


//////////////////////////////////////////////////////////////////////////////
// class GCNicknameVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNicknameVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNicknameVerify(); }
	string getPacketName()  { return "GCNicknameVerify"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_NICKNAME_VERIFY; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + szuint; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNicknameVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCNicknameVerifyHandler 
{
public:
	static void execute( GCNicknameVerify* pPacket, Player* pPlayer) ;
};

#endif
