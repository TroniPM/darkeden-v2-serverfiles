#ifndef __FINITE_STATE_MACHINE_H__
#define __FINITE_STATE_MACHINE_H__

#include "Types.h"
#include "Timeval.h"
#include <hash_map>
#include "Assert.h"
#include "VSDateTime.h"

/**
 * �⺻ abstract class��
 **/
class State
{
public:
	State() { }
	virtual ~State() { }

	virtual DWORD		getStateType() const = 0;

	// ���� ���¸� return �Ѵ�. StateType 0 �� ���°� ������ �ʴ´ٴ� �ǹ�.
	virtual DWORD		heartbeat(Timeval currentTime) = 0;

	virtual void		start() { }
	virtual void		end() { }

	virtual State*		clone() = 0;
	virtual string		toString() const = 0;

private:
};

class StateFactory
{
public:
	virtual ~StateFactory() { }
	virtual State*	makeState(DWORD sType) = 0;
	virtual void	wasteState(State* pState) { }
};

class FiniteStateMachine
{
public:
	FiniteStateMachine() : m_pCurrentState(NULL), m_pStateFactory(NULL), m_bReset(false), m_ResetState(0) { }
	virtual ~FiniteStateMachine() { }

	virtual void init() = 0;
	virtual void heartbeat(Timeval currentTime);

	DWORD	getCurrentState() const { return m_pCurrentState->getStateType(); }
	State*	getCurrentState_Object() const { return m_pCurrentState; }

	void	reset() { m_bReset = true; }

protected:
	State*			m_pCurrentState;
	StateFactory*	m_pStateFactory;

	bool			m_bReset;
	DWORD			m_ResetState;
};

/**
 * ���� ���ɸ��� �⺻ class��
 **/
class TimerState : public State
{
public:
	// ������ �ʴ����̴�.
	TimerState( DWORD nState, Turn_t life ) : m_TimeOutState(nState), m_LifeSpan(life) { }
	void		start();
	DWORD		heartbeat(Timeval currentTime);
	void		expire();

private:
	DWORD		m_TimeOutState;
	Turn_t		m_LifeSpan;
	Timeval		m_Deadline;
};

class SetTimeState : public State
{
public:
	SetTimeState( DWORD nState, const VSDateTime& date ) : m_TimeOutState(nState), m_SetTime(date) { }

	void	start();
	DWORD	heartbeat(Timeval currentTime);
	void	expire();

protected:
	void				setTimer( const VSDateTime& date ) { m_SetTime = date; }
	const VSDateTime&	getTimer() const { return m_SetTime; }
private:
	DWORD		m_TimeOutState;
	VSDateTime	m_SetTime;
	Timeval		m_Deadline;
};

// �׳� ��� state�� ���� �ְ� ���� �ִ� ��ü�� �Ѱ��ش�.
// ��ü �ȿ� ���°� ������� ��� ���� �ٸ� FSM���� ������ �ȵǹǷ� ����
class FlyweightStateFactory : public StateFactory
{
public:
	void	registerState( State* pState ) { Assert(m_StateMap[pState->getStateType()] == NULL); m_StateMap[pState->getStateType()] = pState; }
	State*	makeState(DWORD sType) { return m_StateMap[sType]; }

private:
	hash_map<DWORD, State*>	m_StateMap;
};

#endif
