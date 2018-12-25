//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyTunnel.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_TUNNEL_HANDLER_H__
#define __SKILL_BLOODY_TUNNEL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyTunnel;
//////////////////////////////////////////////////////////////////////////////

class BloodyTunnel: public SkillHandler 
{
public:
	BloodyTunnel() throw() {}
	~BloodyTunnel() throw() {}
	
public:
    string getSkillHandlerName()  { return "BloodyTunnel"; }
	SkillType_t getSkillType()  { return SKILL_BLOODY_TUNNEL; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyTunnel g_BloodyTunnel;

#endif // __SKILL_BLOODY_TUNNEL_HANDLER_H__
