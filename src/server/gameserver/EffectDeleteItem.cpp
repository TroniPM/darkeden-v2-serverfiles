//----------------------------------------------------------------------
//
// Filename    : EffectDeleteItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include fies
#include "Assert.h"
#include "EffectDeleteItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectDeleteItem::EffectDeleteItem (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject , Turn_t delay)
	
: Effect(pZone,x,y,pObject,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pObject->getObjectID();

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectDeleteItem::~EffectDeleteItem () 
	
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
void EffectDeleteItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectDeleteItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
	//Assert(pTarget!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));

	//pZone->deleteFromItemList(pTarget->getObjectID());
	//(pZone->getTile( x, y)).deleteItem();
	//pZone->deleteItem( pTarget, x, y );

	Item* pItem = NULL;

	Tile& tile = pZone->getTile(x,y);

	if ( tile.hasItem() )
	{
		pItem = tile.getItem();

		if ( pItem != NULL )
		{
			if ( pItem->getObjectID() == m_ObjectID )
			{
				pZone->deleteItem( pItem, x, y );

				GCDeleteObject gcDO;
				gcDO.setObjectID(pTarget->getObjectID());
				pZone->broadcastPacket(x, y, &gcDO);

				SAFE_DELETE(pTarget);
			}
		}
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDeleteItem::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDeleteItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectDeleteItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectDeleteItem("
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
