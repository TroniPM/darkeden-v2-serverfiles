//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiShot.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MULTI_SHOT_HANDLER_H__
#define __SKILL_MULTI_SHOT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MultiShot;
//////////////////////////////////////////////////////////////////////////////

class MultiShot : public SkillHandler 
{
public:
	MultiShot() throw();
	~MultiShot() throw() {}
	
public:
    string getSkillHandlerName()  { return "MultiShot"; }
	SkillType_t getSkillType()  { return SKILL_MULTI_SHOT; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	void SGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);
	void ARSMGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID);

protected:
	POINT m_pSGMask[8];    // SG ����ũ�� ������� ���谡 ����.
	POINT m_pARMask[8][3]; // AR, SMG����ũ�� ����� ���谡 �ִ�.
};

// global variable declaration
extern MultiShot g_MultiShot;

#endif // __SKILL_MULTI_SHOT_H__
