//////////////////////////////////////////////////////////////////////
// 
// Filename    : CommonBillingPacket.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __COMMON_BILLING_PACKET_H__
#define __COMMON_BILLING_PACKET_H__

// include files
#include <stdio.h>
#include "Packet.h"
#include "PacketFactory.h"
#include "BillingInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class CommonBillingPacket;
//
// GameServer�� BillingServer�� �ְ� �޴� packet�̴�.
//
//////////////////////////////////////////////////////////////////////

class Player;
class Creature;
class GamePlayer;

class CommonBillingPacket : public Packet, public BillingInfo {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_COMMON_BILLING; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBillingInfo; }

	// get packet name
	string getPacketName()  { return "CommonBillingPacket"; }
	
	// get packet's debug string
	string toString() ;

    void test();

public :
	void	setPacket_Type(BillingPacketType bpt)	{ Packet_Type = bpt; }
	void	setResult(int result) 					{ Result = result; }
	void	setUser_CC() throw (Error);
	void	setSession(const string& session) 		{ memset(Session, 0, sizeof(Session)); memcpy(Session, session.c_str(), session.length()); }
	void	setUser_ID(const string& PlayerID) 		{ strcpy(User_ID, PlayerID.c_str()); }
	void	setUser_No(int uno) 					{ sprintf(User_No, "%d", uno); }
	void	setUser_IP(const string& IP) 			{ strcpy(User_IP, IP.c_str()); }
	void	setGame_No(int gameNo) 					{ Game_No = gameNo; }
	void	setUser_Status(const string& UserStatus){ strcpy(User_Status, UserStatus.c_str()); }
	void	setExpire_Date(const string& PlayerID) throw (Error);

	string	getExpire_DateToString() const;

private :
	// 256�� BillingInfo�� 196�̱� ������ �ϴ� �̷��� ��ƵаŴ�
	char		m_pBuffer[256];
};


//////////////////////////////////////////////////////////////////////
//
// class CommonBillingPacketFactory;
//
// Factory for CommonBillingPacket
//
//////////////////////////////////////////////////////////////////////

class CommonBillingPacketFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CommonBillingPacket(); }

	// get packet name
	string getPacketName()  { return "CommonBillingPacket"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_COMMON_BILLING; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize()  { return szBillingInfo; }

};


//////////////////////////////////////////////////////////////////////
//
// class CommonBillingPacketHandler;
//
//////////////////////////////////////////////////////////////////////

class CommonBillingPacketHandler {

public:

	// execute packet's handler
	static void execute(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);

private :
	static void executeBillingLoginVerify(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeBillingRemain(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeBillingCheck(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void executeBillingLoginCheckVerify(CommonBillingPacket* pPacket, Player* pPlayer) throw(ProtocolException, Error);
	static void disconnectGamePlayer(GamePlayer* pGamePlayer, Turn_t delay) throw (Error);
	static void sendBillingRemainMessage(CommonBillingPacket* pPacket, GamePlayer* pGamePlayer) throw (Error);

};

#endif
