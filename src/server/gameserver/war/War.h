///////////////////////////////////////////////////////////////////
// ���￡ ���� �������� ���� �� ���� ���� �� ����� ó����ƾ.
///////////////////////////////////////////////////////////////////

#ifndef __WAR_H__
#define __WAR_H__

#include "Types.h"
#include "Work.h"
#include "Exception.h"
#include "VSDateTime.h"

class Mutex;
class PlayerCreature;
class WarScheduleInfo;
class WarInfo;

class War : public Work
{
public:
	enum WarState {
		WAR_STATE_WAIT,				// 0
		WAR_STATE_CURRENT,			// 1
		WAR_STATE_END,				// 2
		WAR_STATE_CANCEL,			// 3

		MAX_WAR_STATE				// 4
	};

public:
	War( WarState warState, WarID_t warID=0 );
	virtual ~War();

	virtual WarType_t	getWarType() const = 0;
	virtual string 		getWarType2DBString() const = 0;
	virtual string		getWarName()  = 0;

	WarID_t			getWarID()	const				{ return m_WarID; }
	void			setWarID( WarID_t warID )		{ m_WarID = warID; }

	WarState		getState()	const				{ return m_State; }
	const string&	getState2DBString() const;
	void			setState( WarState warState )	{ m_State = warState; }

	const VSDateTime&	getWarStartTime() const		{ return m_StartTime; }
	void				setWarStartTime(VSDateTime dt) { m_StartTime = dt; }

public:
	virtual bool	isModifyCastleOwner( PlayerCreature* pPC )  { return false; }

	virtual void	sendWarStartMessage() ;
	virtual void	sendWarEndMessage() ;

public:
	static void		initWarIDRegistry();

public:
	virtual void 	execute();
	virtual bool    endWar(PlayerCreature* pPC)  { return false; }

protected :
	virtual void 	executeStart()  = 0;
	virtual void 	executeEnd()  = 0;


public :
	virtual void	makeWarScheduleInfo( WarScheduleInfo* pWSI )  = 0;
	virtual void 	makeWarInfo(WarInfo* pWarInfo)  = 0;

	virtual string	toString()  = 0;

private:
	WarID_t				m_WarID;
	WarState 			m_State;				// ������ ���� ����.
	VSDateTime			m_StartTime;			// ���� ���� �ð�

	static Mutex		m_Mutex;
	static WarID_t		m_WarIDRegistry;
};

#endif // __WAR_H__
