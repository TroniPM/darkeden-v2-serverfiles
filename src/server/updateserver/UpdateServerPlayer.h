//--------------------------------------------------------------------------------
// 
// Filename    : UpdateServerPlayer.h 
// Written by  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UPDATE_SERVER_PLAYER_H__
#define __UPDATE_SERVER_PLAYER_H__

// include files
#include "Player.h"
#include "PlayerStatus.h"
#include <deque>
#include "Packet.h"
#include "Timeval.h"
#include <bitset>

//--------------------------------------------------------------------------------
//
// class UpdateServerPlayer
//
// 업데이트 서버용 플레이어 클래스
//
// 입력은 버퍼링을 하지만, 출력은 버퍼링을 하지 않는다.
//
//--------------------------------------------------------------------------------

class UpdateServerPlayer : public Player {

public :
	
	// constructor
	UpdateServerPlayer ( Socket * pSocket );
	
	// destructor
	~UpdateServerPlayer ();

public :

	// read socket's receive buffer and fill input buffer
	// virtual void processInput () ;
	
	// parse packet and execute handler for the packet
	virtual void processCommand () ;
	
	// flush output buffer to socket's send buffer
	virtual void processOutput () ;
	
	// send packet to player's output buffer
	virtual void sendPacket ( Packet * packet ) ;

	// disconnect
	// 정식 로그아웃의 경우 disconnect(UNDISCONNECTED)
	virtual void disconnect ( bool bDisconnected = DISCONNECTED );
	
	// get debug string
	virtual string toString () ;

	void setPenaltyFlag(PenaltyType PenaltyFlag)  { m_PenaltyFlag.set(PenaltyFlag); }

	// remove Flag
	void removePenaltyFlag(PenaltyType PenaltyFlag)  { m_PenaltyFlag.reset(PenaltyFlag); }

	// Is Flag?
	bool isPenaltyFlag(PenaltyType PenaltyFlag)  { return m_PenaltyFlag.test(PenaltyFlag); }

	void setExpiredTime ( int t )  { getCurrentTime(m_ExpireTime); m_ExpireTime.tv_sec += 5; }

	
public :

	// get/set player's status
	PlayerStatus getPlayerStatus ()  { return m_PlayerStatus; }
	void setPlayerStatus ( PlayerStatus playerStatus )  { m_PlayerStatus = playerStatus; }

private :

	// player status
	PlayerStatus m_PlayerStatus;

	// expire time
	Timeval m_ExpireTime;

	// Flag set
	bitset<PENALTY_TYPE_MAX> m_PenaltyFlag;

};

#endif
