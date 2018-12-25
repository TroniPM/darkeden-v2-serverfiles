//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_CORPSE_H__
#define __VAMPIRE_CORPSE_H__

#include "Item.h"
#include "ItemFactory.h"
#include "Corpse.h"
#include "PCVampireInfo3.h"

class Vampire;

//////////////////////////////////////////////////////////////////////////////
// class VampireCorpse;
// �����̾ �׾��� ���, ����� ��ü�̴�.
//////////////////////////////////////////////////////////////////////////////

class VampireCorpse : public Corpse 
{
public:
	VampireCorpse(Vampire* pVampire) throw(Error);
	virtual ~VampireCorpse() throw();

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error) {}
	virtual bool destroy() throw(Error) { return true; }
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y) throw(Error) {}
	void tinysave(const string & field) const throw (Error) { tinysave(field.c_str()); }
    void tinysave(const char* field) const throw (Error) {}


public:
	virtual ItemClass getItemClass()  { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType()  { return VAMPIRE_CORPSE; }
	virtual void setItemType(ItemType_t itemType) throw() { throw UnsupportedError(__PRETTY_FUNCTION__); }

	virtual string toString() ;

public:
	PCVampireInfo3 & getVampireInfo() throw() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo()  { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & slayerInfo) throw() { m_VampireInfo = slayerInfo; }

	void setXY(ZoneCoord_t X, ZoneCoord_t Y) { m_VampireInfo.setX(X); m_VampireInfo.setY(Y); }

protected:
	PCVampireInfo3 m_VampireInfo; // ��ü�� �ܸ� ���� ����
};

#endif
