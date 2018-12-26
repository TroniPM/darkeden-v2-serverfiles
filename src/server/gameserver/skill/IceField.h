//////////////////////////////////////////////////////////////////////////////
// Filename    : IceField.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_FIELD_HANDLER_H__
#define __SKILL_ICE_FIELD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceField;
//////////////////////////////////////////////////////////////////////////////

class IceField : public SkillHandler 
{
public:
	IceField() ;
	~IceField() throw() {}
	
public:
    string getSkillHandlerName()  { return "IceField"; }
	SkillType_t getSkillType()  { return SKILL_ICE_FIELD; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT		m_IceFieldMask[4][9];	// 4�ܰ�, 9����
	int			m_MaskNum[4];
};

// global variable declaration
extern IceField g_IceField;

#endif // __SKILL_ICE_FIELD_HANDLER_H__
