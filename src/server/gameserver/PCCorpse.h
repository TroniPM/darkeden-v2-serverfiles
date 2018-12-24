//////////////////////////////////////////////////////////////////////////////
// Filename    : PCCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_CORPSE_H__
#define __PC_CORPSE_H__

#include "Corpse.h"

//////////////////////////////////////////////////////////////////////////////
// class PCCorpse;
// PC �� ���� ���, ����� ��ü��.
//////////////////////////////////////////////////////////////////////////////

class PCCorpse : public Corpse 
{
// methods from Object
public:
	virtual string toString() const throw();

// methods from Item
public:
	// ũ��ó�� �κ��丮���� �������� ������, ��ü�� ����ִ´�.
	void transportItems(Creature* pCreature) throw(Error);

// data members
private:
	// PC ��ü���� ���������� �͵��� ������ ������?
	// ��Ÿ�� - �Ӹ��� - �Ǻλ� - �Ӹ� - ���� - ���� - ����1 - ����2
	HairStyle m_HairStyle;
	Color_t   m_HairColor;
	Color_t   m_SkinColor;
	Color_t   m_UpperColors[2];
	Color_t   m_LowerColors[2];
	
};

#endif
