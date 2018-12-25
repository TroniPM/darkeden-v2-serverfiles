//////////////////////////////////////////////////////////////////////////////
// Filename    : TornadoSever.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TORNADO_SEVER_HANDLER_H__
#define __SKILL_TORNADO_SEVER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TornadoSever;
//////////////////////////////////////////////////////////////////////////////

class TornadoSever : public SkillHandler 
{
public:
	TornadoSever() throw();
	~TornadoSever() throw() {}
	
public:
    string getSkillHandlerName()  { return "TornadoSever"; }
	SkillType_t getSkillType()  { return SKILL_TORNADO_SEVER; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Monster* pMonster, Creature* pTargetCreature);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	POINT m_pTornadoSeverMask[9];

};

// global variable declaration
extern TornadoSever g_TornadoSever;

#endif // __SKILL_TORNADO_SEVER_HANDLER_H__
