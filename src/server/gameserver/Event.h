//////////////////////////////////////////////////////////////////////////////
// Filename    : Event.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_H__
#define __EVENT_H__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class Event;
// �÷��̾� Ŭ������ �����Ǿ� ������,
// ���� �ð� �Ŀ� Ư�� �׼��� ���ϵ��� ���ش�.
//////////////////////////////////////////////////////////////////////////////

class GamePlayer;

class Event 
{
public:
	enum EventClass 
	{
		EVENT_CLASS_RESURRECT,    // ũ��ó�� �׾��� ���, ��Ȱ��Ű��..
		EVENT_CLASS_MORPH,        // �����̾� -> �����̾��
		EVENT_CLASS_RESTORE,      // �����̾� -> �����̾� ����
		EVENT_SAVE,               // �ֱ������� ũ��ó ������ �����ϱ�
		EVENT_CLASS_REGENERATION, // �����̾ �ֱ������� ȸ�����ֱ�
		EVENT_CLASS_RELOAD_INFO,  // DB���� info�� reload�Ѵ�.
		EVENT_CLASS_TRANSPORT,    // Zone�̵� �Ѵ�.
		EVENT_CLASS_KICK,    	  // �� �Ŀ� kick�Ѵ�.
		EVENT_CLASS_SYSTEM_MESSAGE,  // Incoming���� ���� System�޼����� ���� �ִٰ� �ѷ��ش�.
		EVENT_CLASS_REFRESH_HOLY_LAND_PLAYER,	// Holy Land Race Bonus ��ȭ�� ���� Holy Land Player Stat �� ����
		EVENT_CLASS_SHUTDOWN,	// ����ڵ��� ���� �����ϰ� �˴ٿ�
		EVENT_CLASS_HEAD_COUNT,	// 30�п� �ѹ��� �Ӹ� �� ���� ����
		EVENT_CLASS_CBILLING,	// �߱� ����. �ֱ������� minus point/minute ��Ŷ�� ������.
		EVENT_CLASS_AUTH,		// Nprotect ����
		EVENT_CLASS_MAX
	};

public:
	Event(GamePlayer* pGamePlayer) throw(Error);
	virtual ~Event() throw();
			
public:
	virtual EventClass getEventClass() const throw() = 0;

	// get event life-cycle
	// �⺻������ ��� �̺�Ʈ���� 1ȸ���̴�.
	virtual bool isTemporary() const throw() { return true; }
	virtual bool isPermanent() const throw() { return false; }

	virtual void activate() throw(Error) = 0;
	
	Timeval getDeadline() const throw() { return m_Deadline; }
	void setDeadline(Turn_t delay) throw();

	virtual string toString() const throw() = 0;

protected:
	GamePlayer* m_pGamePlayer; // ���� �÷��̾� ��ü
	Timeval     m_Deadline;    // ���� �ð�
	
};

#endif
