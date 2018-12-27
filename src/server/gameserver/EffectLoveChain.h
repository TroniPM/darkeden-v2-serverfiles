//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoveChain.h
// Written by  : elca@ewestsoft.com
// Description : 
// ���α�� Sniping �Ǵ� �����̾� ��� Invisibility�� ���ؼ�
// ���� ���� ����������� �ִ�(������� �ִ�) ũ���Ŀ� �ٴ� ����Ʈ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LOVE_CHAIN__
#define __EFFECT_LOVE_CHAIN__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLoveChain
//////////////////////////////////////////////////////////////////////////////

class EffectLoveChain : public Effect 
{
public:
	EffectLoveChain(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_LOVE_CHAIN; }

	void affect() {}
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:

	// get/set Target Name
	const string& getTargetName()  { return m_TargetName; }
	void setTargetName( const string& targetName )  { m_TargetName = targetName; }

	Zone* getZone()  { return m_pZone; }
	void setZone( Zone* pZone )  { m_pZone = pZone; }

	ObjectID_t getItemObjectID()  { return m_ItemObjectID; }
	void setItemObjectID( ObjectID_t itemObjectID )  { m_ItemObjectID = itemObjectID; }
	
private:

	ObjectID_t	m_OwnerOID;			// ����Ʈ �ɸ� ���� OwnerID
	Zone*		m_pZone;			// Zone ������
	string		m_TargetName;		// Target Name
	ObjectID_t	m_ItemObjectID;		// �������� ������Ʈ ���̵�
};

#endif
