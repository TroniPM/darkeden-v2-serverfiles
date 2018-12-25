//----------------------------------------------------------------------
//
// Filename    : SubOustersSkillInfo.h
// Written By  :
// Description :
//
//----------------------------------------------------------------------

#ifndef __SUB_OUSTERS_SKILL_INFO_H__
#define __SUB_OUSTERS_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

class SubOustersSkillInfo {

public :

	// read data from socket input stream
	void read (SocketInputStream & iStream);

	// write data to socket output stream
	void write (SocketOutputStream & oStream) ;

	// get size of object
	uint getSize ()  { return szSkillType + szTurn + szTurn; }
	// get max size of object
	static uint getMaxSize () throw () { return szSkillType + szTurn + szTurn; }

	// get debug string
	string toString () ;

public :

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get /set Skill ExpLevel
	ExpLevel_t getExpLevel()  { return m_ExpLevel; }
	void setExpLevel( ExpLevel_t ExpLevel ) throw() { m_ExpLevel = ExpLevel; }

	// get / set Turn
	Turn_t getSkillTurn()  { return m_Interval ; }
	void setSkillTurn(Turn_t SkillTurn) throw() { m_Interval = SkillTurn; }

	// get / set CastingTime
	Turn_t getCastingTime()  { return m_CastingTime; }
	void setCastingTime(Turn_t CastingTime) throw() { m_CastingTime = CastingTime; }

private :

	// ��ų Ÿ��
	SkillType_t m_SkillType;

	// ��ų ����
	ExpLevel_t m_ExpLevel;

	// �ѹ����� ������ �� ������
	Turn_t m_Interval;

	// ĳ���� Ÿ��
	Turn_t m_CastingTime;

};

#endif
