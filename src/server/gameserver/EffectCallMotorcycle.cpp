//----------------------------------------------------------------------
//
// Filename    : EffectCallMotorcycle.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectCallMotorcycle.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectCallMotorcycle::EffectCallMotorcycle (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay, bool bDeleteFromDB) 
	throw (Error)
: Effect(pZone,x,y,pItem,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pItem->getObjectID();
	m_bDeleteFromDB = bDeleteFromDB;

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectCallMotorcycle::~EffectCallMotorcycle () 
	throw (Error)
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
void EffectCallMotorcycle::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectCallMotorcycle::unaffect (Motorcycle* pMotorcycle, Slayer* pSlayer)
	throw (Error)
{
	__BEGIN_TRY

	// Slayer�� ����(Zone, x, y)�� ���Ѵ�.
	Zone* pZone = pSlayer->getZone();
	Coord_t  x  = pSlayer->getX();
	Coord_t  y  = pSlayer->get();

	// Slayer�� ������ ��ȿ���� �˻��Ѵ�.
	
	// ���� Ÿ�� ������ �����´�.
	Tile & tile = pZone->getTile(x, y);

	// ���� �ش� ���� �������� �ִٸ�??
	if(tile.hasItem())
	{
	}
	else
	{
		pZone->addItem(pMotorcycle, x, y);

		// �������� �̵��ߴٴ� ��Ŷ�� ������.

	}

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectCallMotorcycle::unaffect ()
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectCallMotorcycle::unaffect (Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectCallMotorcycle::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectCallMotorcycle("
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
