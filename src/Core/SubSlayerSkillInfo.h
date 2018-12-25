//----------------------------------------------------------------------
//
// Filename    : SubSlayerSkillInfo.h
// Written By  : elca
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_SLAYER_SKILL_INFO_H__
#define __SUB_SLAYER_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
// Inventory ������ ��� �ִ� ��ü.
//
// GCUpdateInfo ��Ŷ�� ��ܼ� Ŭ���̾�Ʈ���� ���۵ȴ�.
// �������̳� �ɷ��ִ� ���� ���� ������ ������� �ʴ�.
//
//----------------------------------------------------------------------

class SubSlayerSkillInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) ;

	// get size of object
	uint getSize ()  { return szSkillType + szExp + szExpLevel + szTurn + szTurn + szBYTE; }
	// get max size of object
	static uint getMaxSize () throw () { return szSkillType + szExp + szExpLevel + szTurn + szTurn + szBYTE; }

	// get debug string
	string toString () ;

public :

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Exp
	Exp_t getSkillExp()  { return m_Exp; }
	void setSkillExp(Exp_t Exp) throw() { m_Exp = Exp; }

	// get / set ExpLevel
	ExpLevel_t getSkillExpLevel()  { return m_ExpLevel; }
	void setSkillExpLevel(ExpLevel_t ExpLevel) throw() { m_ExpLevel = ExpLevel; }

	// get / set Turn
	Turn_t getSkillTurn()  { return m_Interval ; }
	void setSkillTurn(Turn_t SkillTurn) throw() { m_Interval = SkillTurn; }

	// get / set CastingTime
	Turn_t getCastingTime()  { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

	// get / set Enable
	// true �� ��� ��� ����, false�� ��� ��� �Ұ���.
	bool getEnable()  { return m_Enable; }
	void setEnable(bool Enable ) throw() { m_Enable = Enable; }

private :

	// ��ų Ÿ��
	SkillType_t m_SkillType;

	// ��ų ����ġ 
	Exp_t m_Exp;

	// ��ų ���� 
	ExpLevel_t m_ExpLevel;

	// �ѹ����� ������ �� ������
	Turn_t m_Interval;

	// ĳ���� Ÿ��
	Turn_t m_CastingTime;

	// �� ����� �� �� �ִ°� ���°��� ����
	bool m_Enable;

};

#endif
