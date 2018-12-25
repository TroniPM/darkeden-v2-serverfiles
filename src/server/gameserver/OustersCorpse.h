//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersCorpse.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_CORPSE_H__
#define __OUSTERS_CORPSE_H__

#include "Item.h"
#include "ItemFactory.h"
#include "Corpse.h"
#include "PCOustersInfo3.h"

class Ousters;

//////////////////////////////////////////////////////////////////////////////
// class OustersCorpse;
// 뱀파이어가 죽었을 경우, 남기는 시체이다.
//////////////////////////////////////////////////////////////////////////////

class OustersCorpse : public Corpse 
{
public:
	OustersCorpse(Ousters* pOusters);
	virtual ~OustersCorpse() throw();

public:
	virtual void create(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error) {}
	virtual bool destroy() throw(Error) { return true; }
	virtual void save(const string & ownerID, Storage storage, DWORD storageID, BYTE x, BYTE y) throw(Error) {}
	void tinysave(const string & field)  { tinysave(field.c_str()); }
    void tinysave(const char* field)  {}


public:
	virtual ItemClass getItemClass()  { return ITEM_CLASS_CORPSE; }

	virtual ItemType_t getItemType()  { return OUSTERS_CORPSE; }
	virtual void setItemType(ItemType_t itemType) throw() { throw UnsupportedError(__PRETTY_FUNCTION__); }

	virtual string toString() ;

public:
	PCOustersInfo3 & getOustersInfo() throw() { return m_OustersInfo; }
	const PCOustersInfo3 & getOustersInfo()  { return m_OustersInfo; }
	void setOustersInfo(const PCOustersInfo3 & slayerInfo) throw() { m_OustersInfo = slayerInfo; }

	void setXY(ZoneCoord_t X, ZoneCoord_t Y) { m_OustersInfo.setX(X); m_OustersInfo.setY(Y); }

protected:
	PCOustersInfo3 m_OustersInfo; // 시체의 외모에 대한 정보
};

#endif
