//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSubmitScore 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SUBMIT_SCORE_H__
#define __CG_SUBMIT_SCORE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGSubmitScore;
//
//////////////////////////////////////////////////////////////////////

class CGSubmitScore : public Packet {

public:
	
	// constructor
	CGSubmitScore() throw();
	
	// destructor
	~CGSubmitScore() throw();

	
public:
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_SUBMIT_SCORE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + szBYTE + szWORD; }

	// get packet name
	string getPacketName()  { return "CGSubmitScore"; }
	
	// get packet's debug string
	string toString() ;

public:
	BYTE	getGameType() const { return m_GameType; }
	void	setGameType(BYTE type) { m_GameType = type; }

	BYTE	getLevel() const { return m_Level; }
	void	setLevel(BYTE level) { m_Level = level; }

	WORD	getScore() const { return m_Score; }
	void	setScore(WORD score) { m_Score = score; }
private :
	BYTE	m_GameType;
	BYTE	m_Level;
	WORD	m_Score;
};


//////////////////////////////////////////////////////////////////////
//
// class CGSubmitScoreFactory;
//
// Factory for CGSubmitScore
//
//////////////////////////////////////////////////////////////////////

class CGSubmitScoreFactory : public PacketFactory {

public:
	
	// constructor
	CGSubmitScoreFactory() throw() {}
	
	// destructor
	virtual ~CGSubmitScoreFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSubmitScore(); }

	// get packet name
	string getPacketName()  { return "CGSubmitScore"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_SUBMIT_SCORE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szBYTE + szBYTE + szWORD; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGSubmitScoreHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSubmitScoreHandler {
	
public:

	// execute packet's handler
	static void execute(CGSubmitScore* pCGSubmitScore, Player* player) throw(Error);
};

#endif
