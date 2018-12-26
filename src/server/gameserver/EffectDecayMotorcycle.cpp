//----------------------------------------------------------------------
//
// Filename    : EffectDecayMotorcycle.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectDecayMotorcycle.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectDecayMotorcycle::EffectDecayMotorcycle (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay, bool bDeleteFromDB)
	
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
EffectDecayMotorcycle::~EffectDecayMotorcycle () 
	
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
void EffectDecayMotorcycle::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectDecayMotorcycle::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget, Slayer* pSlayer)
	
{
	__BEGIN_TRY

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
	Assert(isValidZoneCoord(pZone, x, y));

	// TempItem ������ ��´�.
	Item* pTempItem = NULL;

	// ���⼭�� ���� �������� ���� �� ������, �� �ٸ� �������� ���� ���� ���� �ִ�.
	// �� ���� �������� �����۰� ���� ���� �ٴڿ� �ִ� �������� ���Ͽ� �����ؾ� �Ѵ�.
	// ���� ���� �����ϸ� �ȴ�.
	Tile & tile = pZone->getTile(x, y);

	if (tile.hasItem()) {

		pTempItem = tile.getItem();

		if (pTempItem != NULL) {
			// ObjectID�� ���ٴ� ���� ���� �������̶� ���̴�.
			//if (pTempItem->getObjectID() == m_ObjectID) {
			if (pTempItem->getObjectID() == m_ObjectID) {

				pZone->deleteItem(pTempItem , x, y);

				// �������� ������ٴ� ��Ŷ�� ������.
				GCDeleteObject gcDeleteObject;
				gcDeleteObject.setObjectID(m_ObjectID);

				pZone->broadcastPacket(x, y , &gcDeleteObject);

				if (m_bDeleteFromDB)
				{
					pTempItem->destroy();
				}

				SAFE_DELETE(pTempItem);
			}
		}
	}

	// heartbeat�� EffectDecayMotorcycle�� ó���ȴ�. �� ���� ���� heartbeat�ÿ� 
	// ����ڿ��� ������̸� ȣ���� �־�� �Ѵ�.
	// ����ڴ� ��������� ������Ʈ�� 

	//EffectCallMotorcycle* pEffectCallMotorcycle = new EffectCallMotorcycle(pMotorcycleObject, pSlayer);
	//pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDecayMotorcycle::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectDecayMotorcycle::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectDecayMotorcycle::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectDecayMotorcycle("
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
