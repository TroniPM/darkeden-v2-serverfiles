//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSay.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SAY_H__
#define __CG_SAY_H__

// include files

//#ifdef __GAME_SERVER__
//#include "GamePlayer.h"
//#endif

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSay;
//
// Ŭ���̾�Ʈ�� �������� ������ Say ��Ŷ�̴�.
// ���ο� Say String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class Player;
class Creature;
class GamePlayer;

class CGSay : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szuint + szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "CGSay"; }
	
	// get packet's debug string
	string toString() ;

	// get/set text color
	uint getColor()  { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	const string& getMessage()  { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }
	

private :
	
	// text color
	uint m_Color;

	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGSayFactory;
//
// Factory for CGSay
//
//////////////////////////////////////////////////////////////////////

class CGSayFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSay(); }

	// get packet name
	string getPacketName()  { return "CGSay"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SAY; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize()  { return szuint + szBYTE + 128; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGSayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSayHandler {

public:

	// execute packet's handler
	static void execute(CGSay* pPacket, Player* pPlayer) throw(ProtocolException, Error);

#ifdef __GAME_SERVER__

	static void opExecute( Creature* pCreature, GamePlayer* pPlayer, string msg, int i ) throw(ProtocolException, Error);

	// for guild test
	static void opzone( string msg, int i ) throw( ProtocolException, Error );
	static void opguild( string msg, int i, Creature* pCreature ) throw(ProtocolException, Error);

	// ���� �ý��� ���� 
	static void opcombat( GamePlayer* pPlayer, string msg, int i ) throw(ProtocolException, Error);

	// set �̺�Ʈ ������ Ȯ��
	static void opset( GamePlayer* pPlayer, string msg, int i ) throw(ProtocolException, Error);

	static void opview( GamePlayer* pPlayer, string msg, int i ) throw(ProtocolException, Error);

	// save
	static void opsave(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// wall
	static void opwall(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// Shutdown
	static void opshutdown(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// kick
	static void opkick(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// mute
	static void opmute(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// freezing
	static void opfreezing(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// deny
	static void opdeny(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// info
	static void opinfo(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// trace
	static void optrace(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// warp
	static void opwarp(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// create
	static void opcreate(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// grant
	static void opgrant(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// recall
	static void oprecall(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// mrecall
	static void opmrecall(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// user
	static void opuser(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// summon
	static void opsummon(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// notice 
	static void opnotice(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// pay 
	static void oppay(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// world 
	static void opworld(GamePlayer* pPlayer, string msg, int i, bool bSameWorldOnly) throw(ProtocolException, Error);

	// command 
	static void opcommand(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// find
	static void opfind(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// refresh info
	static void opload(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// �ӽ�
	static void opsoulchain(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// credit
	static void opcredit(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// fun
	static void opfun(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);

	// log
	static void oplog(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);
	
	// denychat
	static void opdenychat(GamePlayer* pPlayer, string msg, int i) throw(ProtocolException, Error);
	// world 
	static void oprefreshguildunion(GamePlayer* pPlayer, string msg, int i, bool bSameWorldOnly = true) throw(ProtocolException, Error);
	static void opmodifyunioninfo(GamePlayer* pPlayer, string msg, int i, bool bSameWorldOnly = true) throw(ProtocolException, Error);

#endif

};

#endif
