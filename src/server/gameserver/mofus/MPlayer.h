/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayer.h
// Desc		: ���۽� ��� ��ü
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPLAYER_H__
#define __MPLAYER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Player.h"

// forward declaration
class MPacket;
class MJob;

// class MPlayer
class MPlayer : public Player
{
public:
	MPlayer( MJob* pJob ) throw ( Error );
	virtual ~MPlayer() throw ( Error );

public:
	// network read / write
	void processInput() throw ( IOException, Error );
	void processOutput() throw ( IOException, Error );

	// parse packet and execute handler for the packet
	void processCommand() throw ( IOException, Error );

	// send packet to player's output buffer
	void sendPacket( MPacket* pPacket ) throw ( ProtocolException, Error );

	// connect
	void connect();

	// disconnect
	void disconnect( bool bDisconnected = DISCONNECTED ) throw ( InvalidProtocolException, Error );

public:
	// process
	void process();

	///////////////////////////////////////////////
	// send �Լ�
	///////////////////////////////////////////////
	void sendConnectAsk();
	void sendLogout();
	void sendUserInfo();
	void sendReceiveOK();
	void sendResult();
	void sendSError( int errorCode );

	// get Job
	MJob* getJob() const { return m_pJob; }
	
	// add power point
	void addPowerPoint( int point );

	// set errorcode
	void setErrorCode( int errorCode );

	// �۾� ��
	void setEnd( bool bEnd = true );

private:
	// ó���� �۾�
	MJob* m_pJob;
};

#endif

