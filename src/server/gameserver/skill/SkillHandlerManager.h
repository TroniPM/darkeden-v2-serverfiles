//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillHandlerManager.h 
// Wrrtten by  : elca@ewestsoft.com
// Description : ��ų �ڵ鷯�� �����ϴ� Manager�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HANDLER_MANAGER_H__
#define __SKILL_HANDLER_MANAGER_H__

#include "Skill.h"
#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SkillHandlerManager
//////////////////////////////////////////////////////////////////////////////

class SkillHandlerManager 
{
public :
	SkillHandlerManager() throw();
	~SkillHandlerManager() throw();
	
public:
	// ���Ӽ�����ü�� init()���� ȣ��ȴ�.
	void init() throw(Error);
	
	// ��ų �ڵ鷯 ��ü�� �ʱ�ȭ�Ѵ�.
	void addSkillHandler(SkillHandler* pSkillHandler) throw(Error);

	// ��ų �ڵ鷯�� ����.
	SkillHandler* getSkillHandler(SkillType_t SkillType) throw(Error);

	// toString
	string toString() const throw();
	
private:
	SkillHandler** m_SkillHandlers;  // ��ų �ڵ鷯 �迭
	ushort         m_Size;           // ��ų �ڵ鷯 �迭�� ũ��

};

extern SkillHandlerManager* g_pSkillHandlerManager;

#endif
