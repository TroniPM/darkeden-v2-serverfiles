//----------------------------------------------------------------------
//
// Filename    : EffectAddItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectAddItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"
#include "ParkingCenter.h"
#include "item/Motorcycle.h"
#include <stdio.h>

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectAddItem::EffectAddItem (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay, bool bAllowCreature) 
	
: Effect(pZone,x,y,pItem,delay) 
{
	__BEGIN_TRY

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pItem->getObjectID();
	m_bAllowCreature = bAllowCreature;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectAddItem::~EffectAddItem () 
	
{
	__BEGIN_TRY

	unaffect(m_pZone , m_X , m_Y , m_pTarget);

	__END_CATCH
}
			

//----------------------------------------------------------------------
// affect to target
// �� ����Ʈ�� Ÿ�Ͽ� ���ӵ��� �����Ƿ�, affect()�� ȣ����� �ʴ´�.
// �ֳ��ϸ�, target�� �����ڿ��� �����Ǹ�, �ƹ��� �ϵ� ���� �ʱ� �����̴�.
//----------------------------------------------------------------------
void EffectAddItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectAddItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	//cout << "EffectAddItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)" << endl;

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
	Assert(pTarget!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));

	Item* pItem = dynamic_cast<Item*>(pTarget);

	if (pItem!=NULL)
	{
		pZone->getObjectRegistry().registerObject(pItem);

		//TPOINT pt = 
		pZone->addItem(pItem, x, y, m_bAllowCreature);
	}
	else
	{
		SAFE_DELETE(pTarget);
		throw Error("EffectAddItem�ε� item�� �ƴѰ�?");
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItem::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectAddItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectAddItem("
			<< "ZoneID:" << (int)m_pZone->getZoneID()
			<< ",X:"     << (int)getX()
			<< ",Y:"     << (int)getY();

	if (m_pTarget) msg << ",Target:" << m_pTarget->toString();
	else           msg << ",Target:NULL";

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec;

	msg << ")";

	return msg.toString();
}
