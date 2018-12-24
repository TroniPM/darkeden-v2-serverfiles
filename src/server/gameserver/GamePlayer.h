//////////////////////////////////////////////////////////////////////////////
// Filename    : GamePlayer.h 
// Written by  : reiot@ewestsoft.com
// Description : ���� ������ �÷��̾� Ŭ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include "Types.h"
#include "Exception.h"
#include "Player.h"
#include "SocketEncryptOutputStream.h"
#include "SocketEncryptInputStream.h"
#include "Mutex.h"
#include <deque>
#include "Packet.h"
#include "Timeval.h"
#include "PlayerStatus.h"
#include "EventManager.h"
#include "skill/Skill.h"
#include "PaySystem.h"
#include "billing/BillingPlayerInfo.h"
#include "chinabilling/CBillingPlayerInfo.h"
#include "Gpackets/GCReconnectLogin.h"
#include <bitset>

#include "gameguard/CSAuth.h"

//////////////////////////////////////////////////////////////////////////////
// class GamePlayer
//
// ���� ������ �÷��̾� Ŭ����
//
// Player Ŭ������ ��ӹ޾Ƽ�, ���� ���������� ���Ǵ� Mutex �� 
// Creature ���� ������ �� �޽��, PreviousPacket ���� ������ ��
// �޼ҵ���� �߰��ߴ�.
//
// Ư�� processOutput() �� sendPacket()�� Race Condition �� �߻��� ��
// �����Ƿ�, Mutex �� ��ȣ�Ǿ�� �Ѵ�.(MODE-IV�� ����̸�, MODE-I, II
// �� ��쿡�� processInput(), processCommand() ��� Mutex �� ��ȣ�ؾ�
// �Ѵ�.)
//////////////////////////////////////////////////////////////////////////////

class Creature;

class GamePlayer : public Player, public PaySystem, public BillingPlayerInfo, public CBillingPlayerInfo
{
public:
	// ������ ���� ���� ��Ŷ�� ����
	const static BYTE nPacketHistorySize = 10;

public:
	GamePlayer (Socket * pSocket) throw ( Error );
	~GamePlayer() throw(Error);

public:
	// read socket's receive buffer and fill input buffer
	// virtual void processInput() throw(IOException, Error);
	
	// parse packet and execute handler for the packet
	virtual void processCommand(bool Option = true) throw(IOException, Error);
	
	// flush output buffer to socket's send buffer
	virtual void processOutput() throw(IOException, Error);
	
	// send packet to player's output buffer
	virtual void sendPacket(Packet* packet) throw(ProtocolException, Error);

	// disconnect
	// ���� �α׾ƿ��� ��� disconnect(LOGOUT)
	virtual void disconnect(bool bDisconnected = DISCONNECTED) throw (InvalidProtocolException, Error);
	
	// get debug string
	virtual string toString() const throw(Error);

	// ���ǵ� üũ
	virtual bool verifySpeed(Packet* pPacket) throw(Error);
	
	// get creature pointer 
	Creature* getCreature() throw() { return m_pCreature; }
	const Creature* getCreature() const throw() { return m_pCreature; }

	// set creature pointer
	void setCreature(Creature* pCreature) throw() { m_pCreature = pCreature; }

	// return recent N-th packet
	// �ֱ� ���۵� N ��° ��Ŷ�� �����Ѵ�.
	Packet* getOldPacket(uint prev = 0) throw(OutOfBoundException, NoSuchElementException);

	// return recent packet which has packetID
	// Ư�� ID�� ���� ��Ŷ �� ���� �ֱ��� ��Ŷ�� �����Ѵ�.
	Packet* getOldPacket(PacketID_t packetID) throw(NoSuchElementException);

	// get player's status
	PlayerStatus getPlayerStatus() const throw() { return m_PlayerStatus; }

	// set player's status
	void setPlayerStatus(PlayerStatus playerStatus) throw() { m_PlayerStatus = playerStatus; }

	//
	void addEvent(Event* pEvent) throw(Error);
	Event* getEvent(Event::EventClass EClass) throw(Error);
	void deleteEvent(Event::EventClass EClass) throw(Error);

	// �г�Ƽ Status ���� �Լ�
    //Set Flag
	void setPenaltyFlag(PenaltyType PenaltyFlag) throw() { m_PenaltyFlag.set(PenaltyFlag); }
	
	// remove Flag
	void removePenaltyFlag(PenaltyType PenaltyFlag) throw() { m_PenaltyFlag.reset(PenaltyFlag); }
	
	// Is Flag?
	bool isPenaltyFlag(PenaltyType PenaltyFlag) throw() { return m_PenaltyFlag.test(PenaltyFlag); }

public:
	uint getSpecialEventCount(void) const { return m_SpecialEventCount; }
	void setSpecialEventCount(uint count) { m_SpecialEventCount = count; }
	void loadSpecialEventCount(void) throw();
	void saveSpecialEventCount(void) throw();
	
public :	// '�̹� ���� ��'�� ���. ���� ���Ḧ ���ؼ�. by sigi.
	bool isKickForLogin() const throw()						{ return m_bKickForLogin; }
	void setKickForLogin(bool bKickForLogin=true) throw() 	{ m_bKickForLogin = bKickForLogin; }

	const string& 	getKickRequestHost() const throw()		{ return m_KickRequestHost; }
	uint  			getKickRequestPort() const throw()		{ return m_KickRequestPort; }

	void			setKickRequestHost(const string& host) throw()	{ m_KickRequestHost = host; }
	void			setKickRequestPort(uint port) throw()			{ m_KickRequestPort = port; }

public :
	// ��. 
	void	setReconnectPacket(GCReconnectLogin* pPacket) throw() 	{ SAFE_DELETE(m_pReconnectPacket); m_pReconnectPacket = pPacket; }
	GCReconnectLogin* getReconnectPacket() const throw()			{ return m_pReconnectPacket; }

	// by sigi. 2002.10.23
	bool isFreePass() const { return m_bFreePass; }
	void setFreePass(bool bFreePass=true) { m_bFreePass = bFreePass; }

public :
	void lock() throw(Error) { m_Mutex.lock(); }
    void unlock() throw(Error) { m_Mutex.unlock(); }

public :
	void    setBillingSession() throw (Error)	{ BillingPlayerInfo::setBillingSession(this); }
	bool    sendBillingLogin() throw (Error);

	void	sendCBillingPayInfo() throw ( Error );

	// ��Ŷ ��ȣȭ ����
	// by sigi. 2002.11.27
	void	setEncryptCode() throw (Error);

public :

	void kickPlayer( uint nSeconds, uint KickMessageType ) throw (Error);

	//////////////////////////////////////////////////
	// PaySystem ����
	//////////////////////////////////////////////////
public:
	bool	loginPayPlay( PayType payType,
						const string& PayPlayDate, int PayPlayHours, uint payPlayFlag,
						const string& ip, const string& playerID )
				throw (Error);

	bool	loginPayPlay( const string& ip, const string& playerID )
				throw (Error);

	bool	updatePayPlayTime( const string& playerID,
							const VSDateTime& currentDateTime,
							const Timeval& currentTime )
				throw (ProtocolException, Error );

	void	logoutPayPlay( const string& playerID, bool bClear=false, bool bDecreaseTime=true )
				throw (Error);

	bool	isPayPlaying() const;

	bool	isMetroFreePlayer() const { return m_bMetroFreePlayer; }
	void	setMetroFreePlayer( bool bMetroFreePlayer = true ) { m_bMetroFreePlayer = bMetroFreePlayer; }

	int getItemRatioBonusPoint(void) const { return m_ItemRatioBonusPoint; }
	void setItemRatioBonusPoint(int point) { m_ItemRatioBonusPoint = point; }

	bool	startPacketLog( uint sec );
	CCSAuth&	getCSAuth() { return m_NProtectCSAuth; }

	void logLoginoutDateTime();
	
#ifdef __THAILAND_SERVER__
	bool getPermission(void) const { return m_bPermission; }
	void setPermission(bool permission) { m_bPermission = permission; }
#endif
	
private:
	void setPCRoomLottoStartTime();
	void checkPCRoomLotto( const Timeval& currentTime );
	void savePCRoomLottoTime();
	void giveLotto();
	// add by Coffee 2007-6-25
	void tv_sub(struct timeval *out,struct timeval *in);
private:

	// creature
	Creature* m_pCreature;

	// previous packet queue
	deque<Packet *> m_PacketHistory;

	// player status
	PlayerStatus m_PlayerStatus;

	// Panelty status
	bitset<PENALTY_TYPE_MAX> m_PenaltyFlag;

	// expire time
	Timeval m_ExpireTime;

	BYTE m_VerifyCount;

	// �ð� ���� Ÿ��.
	Timeval m_SpeedVerify;
	Timeval m_MoveSpeedVerify;
	Timeval m_AttackSpeedVerify;
	Timeval m_SkillSpeedVerify[SKILL_MAX];

	// mutex
	mutable Mutex m_Mutex;

	EventManager m_EventManager;

	// ����� �̺�Ʈ ���� ī����
	// �ذ� ���� �ݱ⳪, �� �׷� ������ �̺�Ʈ�� ���� �� �ִ� ī����
	uint m_SpecialEventCount;

	// '�̹� ���� ��'���� ���� ���� ��Ű�� ���
	bool	m_bKickForLogin;
	string  m_KickRequestHost;
	uint    m_KickRequestPort;

	// GameServer --> LoginServer�� ���� ����Ѵ�. ������. by sigi. 2002.6.19
	GCReconnectLogin*	m_pReconnectPacket;

	bool m_bFreePass;

	// ���� �ý��ۿ� �������� �ʰ� ���� �÷��� �ϱ�
	bool m_bMetroFreePlayer;

	// �� ����ں� ������ ȹ�� ���ʽ� Ȯ�� 
	int m_ItemRatioBonusPoint;

	Timeval			m_PCRoomLottoStartTime;		// PC �� ���� ����. ������� �ð�
	uint			m_PCRoomLottoSumTime;		// PC �� ���� ����. �����ð�. logoutPayPlay�� �����

	string			m_PacketLogFileName;
	bool			m_bPacketLog;
	Timeval			m_PacketLogEndTime;

	CCSAuth			m_NProtectCSAuth;

	VSDateTime		m_LoginDateTime;


#ifdef __THAILAND_SERVER__
	bool            m_bPermission;
#endif
	// add by Coffee 2007-7-15 ���ӷ�����м��
	private:
		BYTE m_Sequence;
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class isSamePlayer 
{
public:
	isSamePlayer(GamePlayer* pGamePlayer) : m_pGamePlayer(pGamePlayer) {}
	bool operator()(GamePlayer* pGamePlayer) throw()
	{
		return pGamePlayer->getID() == m_pGamePlayer->getID();
	}

private:
	// Creature Pointer
	GamePlayer* m_pGamePlayer;
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class isSamePlayerbyID
{
public:
	isSamePlayerbyID(const string & ID) : m_ID(ID) {}
	bool operator()(GamePlayer* pGamePlayer) throw()
	{
		return pGamePlayer->getID() == m_ID;
	}

private:
	// Creature ID
	string m_ID;
};

#endif
