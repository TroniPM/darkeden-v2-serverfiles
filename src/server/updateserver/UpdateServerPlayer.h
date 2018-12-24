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
// ������Ʈ ������ �÷��̾� Ŭ����
//
// �Է��� ���۸��� ������, ����� ���۸��� ���� �ʴ´�.
//
//--------------------------------------------------------------------------------

class UpdateServerPlayer : public Player {

public :
	
	// constructor
	UpdateServerPlayer ( Socket * pSocket ) throw ( Error );
	
	// destructor
	~UpdateServerPlayer () throw ( Error );

public :

	// read socket's receive buffer and fill input buffer
	// virtual void processInput () throw ( IOException , Error );
	
	// parse packet and execute handler for the packet
	virtual void processCommand () throw ( IOException , Error );
	
	// flush output buffer to socket's send buffer
	virtual void processOutput () throw ( IOException , Error );
	
	// send packet to player's output buffer
	virtual void sendPacket ( Packet * packet ) throw ( ProtocolException , Error );

	// disconnect
	// ���� �α׾ƿ��� ��� disconnect(UNDISCONNECTED)
	virtual void disconnect ( bool bDisconnected = DISCONNECTED ) throw ( Error );
	
	// get debug string
	virtual string toString () const throw ( Error );

	void setPenaltyFlag(PenaltyType PenaltyFlag) throw() { m_PenaltyFlag.set(PenaltyFlag); }

	// remove Flag
	void removePenaltyFlag(PenaltyType PenaltyFlag) throw() { m_PenaltyFlag.reset(PenaltyFlag); }

	// Is Flag?
	bool isPenaltyFlag(PenaltyType PenaltyFlag) throw() { return m_PenaltyFlag.test(PenaltyFlag); }

	void setExpiredTime ( int t ) throw() { getCurrentTime(m_ExpireTime); m_ExpireTime.tv_sec += 5; }

	
public :

	// get/set player's status
	PlayerStatus getPlayerStatus () const throw () { return m_PlayerStatus; }
	void setPlayerStatus ( PlayerStatus playerStatus ) throw () { m_PlayerStatus = playerStatus; }

private :

	// player status
	PlayerStatus m_PlayerStatus;

	// expire time
	Timeval m_ExpireTime;

	// Flag set
	bitset<PENALTY_TYPE_MAX> m_PenaltyFlag;

};

#endif
