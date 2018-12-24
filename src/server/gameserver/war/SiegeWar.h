///////////////////////////////////////////////////////////////////
// ���￡ ���� �������� ���� �� ���� ���� �� ����� ó����ƾ.
///////////////////////////////////////////////////////////////////

#ifndef __SIEGE_WAR_H__
#define __SIEGE_WAR_H__

#include "War.h"

class Mutex;
class PlayerCreature;

class SiegeWar : public War
{
public:
	SiegeWar( ZoneID_t castleZoneID, WarState warState, WarID_t warID=0 );
	virtual ~SiegeWar();

	ZoneID_t		getCastleZoneID()	const				{ return m_CastleZoneID; }
	void			setCastleZoneID( ZoneID_t zoneID )		{ m_CastleZoneID = zoneID; }

	WarType_t		getWarType() const				{ return WAR_GUILD; }
	string 			getWarType2DBString() const		{ return "GUILD"; }
	string			getWarName() const throw (Error); 

	int				getGuildSide(GuildID_t guildID) const;

	Gold_t			getRegistrationFee() const		{ return m_RegistrationFee; }
	void			setRegistrationFee( Gold_t fee ){ m_RegistrationFee = fee; }
	void			addRegistrationFee( Gold_t fee ){ m_RegistrationFee += fee; }

	uint			getChallengerGuildCount() const { return m_ChallangerGuildCount; }
	bool			addChallengerGuild(GuildID_t gID);

	GuildID_t		getChallangerGuildID(uint index=0) const { return m_ChallangerGuildID[index]; }
	bool			isWarParticipant(GuildID_t gID)
	{
		return gID == m_ChallangerGuildID[0]
			|| gID == m_ChallangerGuildID[1]
			|| gID == m_ChallangerGuildID[2]
			|| gID == m_ChallangerGuildID[3]
			|| gID == m_ChallangerGuildID[4]
			|| gID == m_ReinforceGuildID;
	}

	GuildID_t		getReinforceGuildID() const { return m_ReinforceGuildID; }

public:
	bool			isModifyCastleOwner( PlayerCreature* pPC ) throw (Error);
	GuildID_t		getWinnerGuildID( PlayerCreature* pPC ) throw (Error);

	//void			sendWarStartMessage() const throw (ProtocolException, Error);
	void			sendWarEndMessage() const throw (ProtocolException, Error);

	bool 			endWar(PlayerCreature* pPC) throw(Error);

protected :
	void 			executeStart() throw (Error);
	void 			executeEnd() throw (Error);

	void 			recordSiegeWarStart() throw (Error);
	void 			recordSiegeWarEnd() throw (Error);

public :
	void    makeWarScheduleInfo( WarScheduleInfo* pWSI ) const throw (Error);
	void    makeWarInfo( WarInfo* pWarInfo ) const throw (Error);
	virtual string	toString() const throw (Error);

public:
	BYTE			canReinforce(GuildID_t gID);
	GuildID_t		recentReinforceGuild();
	GuildID_t		recentReinforceCandidate() const { return m_RecentReinforceCandidate; }
	BYTE			registerReinforce(GuildID_t gID);
	bool			acceptReinforce();
	bool			denyReinforce();
	void			clearReinforceRegisters();
	void			setReinforceGuildID( GuildID_t gID ) { m_ReinforceGuildID = gID; }

private:
	ZoneID_t			m_CastleZoneID;			// ����� ���õ� ���� ZoneID
	uint				m_ChallangerGuildCount;	// ���� ��û�� ��� ��
	GuildID_t 			m_ChallangerGuildID[5];	// ������ ��û�� ����� ID
	GuildID_t			m_ReinforceGuildID;		// ������ ���� ��� ID
	Gold_t				m_RegistrationFee;		// ���޵� ���� ��û��

	GuildID_t			m_RecentReinforceCandidate;

	// ���� ���
	Race_t 				m_WinnerRace;
	GuildID_t 			m_WinnerGuildID;
	bool				m_bModifyCastleOwner;
};

#endif // __WAR_H__
