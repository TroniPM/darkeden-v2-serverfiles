#ifndef __GDR_LAIR_MANAGER_H__
#define __GDR_LAIR_MANAGER_H__

#include "Types.h"
#include "FiniteStateMachine.h"
#include "GDRLairAbstractStates.h"
#include "Thread.h"

class Monster;

enum GDRLairStatus
{
	GDR_LAIR_IDLE = 1,
	GDR_LAIR_ENTRANCE,
	GDR_LAIR_ILLUSIONS_WAY_ONLY,
	GDR_LAIR_ICEPOLE,
	GDR_LAIR_SCENE_1,
	GDR_LAIR_SUMMON_MONSTER,
	GDR_LAIR_SCENE_2,
	GDR_LAIR_SUMMON_GDR_DUP,
	GDR_LAIR_SCENE_3,
	GDR_LAIR_GDR_FIGHT,
	GDR_LAIR_SCENE_4,
	GDR_LAIR_AWAKENED_GDR_FIGHT,
	GDR_LAIR_SCENE_5,
	GDR_LAIR_MINION_FIGHT,
	GDR_LAIR_SCENE_6,
	GDR_LAIR_ENDING,
	GDR_LAIR_KILL_ALL,
};

// ���. ����� ���� �ְ� �ð��� �Ǹ� ��� �����ش�.
class GDRLairIdle : public SetTimeState
{
public:
	DWORD	getStateType() const { return GDR_LAIR_IDLE; }
	GDRLairIdle( const VSDateTime& date ) : SetTimeState( GDR_LAIR_ENTRANCE, date ) { }

	void start();

	State*	clone() { return new GDRLairIdle( getTimer() ); }
	string	toString() const { return "GDRLairIdle"; }
private:
};

// 20�а� ��� �����鼭 �Ϸ����� ���� ������ Ȱ��ȭ�ȴ�.
class GDRLairEntrance : public TimerState
{
public:
	DWORD	getStateType() const { return GDR_LAIR_ENTRANCE; }
	GDRLairEntrance() : TimerState( GDR_LAIR_ICEPOLE, 1210 ) { }

	void start();
	DWORD heartbeat(Timeval currentTime);

	State*	clone() { return new GDRLairEntrance(); }
	string	toString() const { return "GDRLairEntrance"; }
};

// ���� �Ա��� ���� �ڿ��� 5�а� �Ϸ����� ���̸� ����� �� �ִ� �ð��� �ִ�.
// �׳� 5�� �ð����°Ű� �Ϸ����� ���̸� �Ѹ��̶� ����ϸ� �ٷ� Icepole
// State�� �Ѿ��.
/*class GDRLairIllusionsWayOnly : public TimerState
{
public:
	DWORD	getStateType() const { return GDR_LAIR_ILLUSIONS_WAY_ONLY; }
	GDRLairIllusionsWayOnly() : TimerState( GDR_LAIR_ICEPOLE, 600 ) { }
	DWORD	heartbeat(Timeval currentTime);

	void start();
	void end();

	State*	clone() { return new GDRLairIllusionsWayOnly(); }
	string	toString() const { return "GDRLairIllusionsWayOnly"; }
};*/

// �Ϸ����� ���̸� ����� �÷��̾ �ִٸ� ���� ����� �� �� �ִ� �ð���
// �ش�. ������ �� ���� ����� ��ȯ�ϰ� ���� ��� ������ �� �ڸ��� 1�еڿ�
// �������� �ִ� ������� ����Ʈ��.. (--)
class GDRLairIcepole : public State
{
public:
	void start();
	DWORD	getStateType() const { return GDR_LAIR_ICEPOLE; }
	DWORD	heartbeat(Timeval currentTime);

	State*	clone() { return new GDRLairIcepole(); }
	string	toString() const { return "GDRLairIcepole"; }

private:
	Timeval	m_BroadcastTime;
};

// ���� ����� ����� ���� �ִٸ� ���巹�� �����Ѵ�.
// ���巹�� ��ȯ�ǰ� ����Ʈ�� �߻��ϰ� ���巹 ��� 1�� �Ѵ�.
class GDRLairScene1 : public GDRScene
{
public:
	GDRLairScene1() : GDRScene( GDR_LAIR_SUMMON_MONSTER ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_1; }
	void	end();

	State*	clone() { return new GDRLairScene1(); }
	string	toString() const { return "GDRLairScene1"; }
};

// ���巹 ��� �Ϲ� ���͸� 10ȸ ��ȯ�Ѵ�.
// ��Ƴ��� ���� �������� Idle��
// 10ȸ ��ȯ�� �ڿ��� ��Ƴ��� ���� ������ Scene2��
class GDRLairSummonMonster : public MonsterSummonState
{
public:
	GDRLairSummonMonster();
	DWORD	getStateType() const { return GDR_LAIR_SUMMON_MONSTER; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairSummonMonster(); }
	string	toString() const { return "GDRLairSummonMonster"; }
};

// ���巹�� ��� 2�� �ϰ� ����Ʈ ���� �� ���� ��ġ�� �̵��� ��
// ��� 3�� �Ѵ�.
class GDRLairScene2 : public GDRScene
{
public:
	GDRLairScene2() : GDRScene( GDR_LAIR_SUMMON_GDR_DUP ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_2; }
	void	end();

	State*	clone() { return new GDRLairScene2(); }
	string	toString() const { return "GDRLairScene2"; }
};

// ���巹�� �н��� ��ȯ�Ѵ�.
class GDRLairSummonGDRDup : public MonsterSummonState
{
public:
	GDRLairSummonGDRDup();
	DWORD	getStateType() const { return GDR_LAIR_SUMMON_GDR_DUP; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairSummonGDRDup(); }
	string	toString() const { return "GDRLairSummonGDRDup"; }
};

// ���巹�� ��� 4�� �ϰ� ����Ʈ�� �����Ѵ�.
class GDRLairScene3 : public GDRScene
{
public:
	GDRLairScene3() : GDRScene( GDR_LAIR_GDR_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_3; }
	void	end();

	State*	clone() { return new GDRLairScene3(); }
	string	toString() const { return "GDRLairScene3"; }
};

// ���巹�� Ȱ��ȭ�Ǿ� �÷��̾��� �ο��.
class GDRLairGDRFight : public State
{
public:
	DWORD	getStateType() const { return GDR_LAIR_GDR_FIGHT; }
	void	start();
	DWORD	heartbeat(Timeval currentTime);
	void	end();

	State*	clone() { return new GDRLairGDRFight(); }
	string	toString() const { return "GDRLairGDRFight"; }
};

// ���巹�� ��� 5�� �ϰ� ���� ������ ���´�.
// ���� ���巹 �ھ�� �÷��̾ ���� �Űܹ�����
// ���巹 ����ü�� ��� 6�� �Ѵ�.
class GDRLairScene4 : public GDRScene
{
public:
	GDRLairScene4() : GDRScene( GDR_LAIR_AWAKENED_GDR_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_4; }

	State*	clone() { return new GDRLairScene4(); }
	string	toString() const { return "GDRLairScene4"; }
};

// ���巹 ����ü�� Ȱ��ȭ�Ǿ� �÷��̾��� �ο��.
// HP�� 50% �Ʒ��� �������� Scene5��, ������ Scene6����.
class GDRLairAwakenedGDRFight : public State
{
	bool	m_bGDRDamaged;
public:
	GDRLairAwakenedGDRFight(bool damaged = false) : m_bGDRDamaged(damaged) { }
	DWORD	getStateType() const { return GDR_LAIR_AWAKENED_GDR_FIGHT; }
	void	start();
	DWORD	heartbeat(Timeval currentTime);

	State*	clone() { return new GDRLairAwakenedGDRFight(m_bGDRDamaged); }
	string	toString() const { return "GDRLairAwakenedGDRFight"; }
};

// ��� 7�� �ϰ� ���� ��ġ�� �̵��� �� ��� 8�� �Ѵ�.
class GDRLairScene5 : public GDRScene
{
public:
	GDRLairScene5() : GDRScene( GDR_LAIR_MINION_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_5; }

	State*	clone() { return new GDRLairScene5(); }
	string	toString() const { return "GDRLairScene5"; }
};

// �߰������� ���ѵ� �ð� �ȿ� ��ƾ� �Ѵ�.
class GDRLairMinionFight : public MonsterSummonState
{
public:
	GDRLairMinionFight();
	DWORD	getStateType() const { return GDR_LAIR_MINION_FIGHT; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairMinionFight(); }
	string	toString() const { return "GDRLairMinionFight"; }
};

// ��� 9�� �ϰ� ���� ��ġ�� �̵��� �� ��� 10�� �Ѵ�.
class GDRLairScene6 : public GDRScene
{
public:
	GDRLairScene6() : GDRScene( GDR_LAIR_AWAKENED_GDR_FIGHT ) { }
	void	start();
	DWORD	getStateType() const { return GDR_LAIR_SCENE_6; }

	State*	clone() { return new GDRLairScene6(); }
	string	toString() const { return "GDRLairScene6"; }
};

// �����鼭 ��縦 �ϰ� ���� �������� �����Ѵ�.
// ��� ���� �� �� ���� -_-
class GDRLairEnding : public TimerState
{
public:
	GDRLairEnding() : TimerState( GDR_LAIR_IDLE, 10 ) { }
	DWORD	getStateType() const { return GDR_LAIR_ENDING; }

	void	start();
	void	end();

	State*	clone() { return new GDRLairEnding(); }
	string	toString() const { return "GDRLairEnding"; }
};

// ���峵��. �� �׾��
class GDRLairKillAll : public TimerState
{
public:
	GDRLairKillAll() : TimerState( GDR_LAIR_IDLE, 10 ) { }
	DWORD	getStateType() const { return GDR_LAIR_KILL_ALL; }

	void	start();
//	DWORD	heartbeat(Timeval currentTime) { return GDR_LAIR_IDLE; }
	void	end();

	State*	clone() { return new GDRLairKillAll(); }
	string	toString() const { return "GDRLairKillAll"; }
};

// ���巹 ��� �Ѱ��ϴ� �Ŵ���. ClientManager�� �����忡�� ����.
class GDRLairManager : public FiniteStateMachine, public Thread
{
public:
	enum GDRLairZones
	{
		ILLUSIONS_WAY_1,
		ILLUSIONS_WAY_2,
		GDR_LAIR,
		GDR_LAIR_CORE,

		GDR_LAIR_MAX
	};

	void init();
	void run() throw();
	string getName() const throw() { return "GDRLairManager"; }

	static GDRLairManager& Instance() { static GDRLairManager theInstance; return theInstance; }
	Zone* getZone(int index) const { return m_pZones[index]; }

	Monster*	getGDR() const { return m_pGDR; }
	void		setGDR(Monster* pGDR) { m_pGDR = pGDR; }

	VSDateTime getNextOpenTime() const;

	BYTE		getCorrectPortal() const { return m_CorrectPortal; }
	void		setCorrectPortal(BYTE pid) { m_CorrectPortal = pid; }

	int			getTotalPCs() const;
	bool		isGDRLairZone(ZoneID_t ZoneID) const;

	void		open() { m_bCanEnter = true; }
	void		close() { m_bCanEnter = false; }
	bool		canEnter() const { return m_bCanEnter; }

	friend class GDRScene;
private:
	Monster*	m_pGDR;
	Zone*		m_pZones[GDR_LAIR_MAX];
	BYTE		m_CorrectPortal;
	bool		m_bCanEnter;
};

#endif
