//----------------------------------------------------------------------
//
// Filename    : EffectRecallMotorcycle.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectRecallMotorcycle.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"
#include "EffectRideMotorcycle.h"
#include "Slayer.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectRecallMotorcycle::EffectRecallMotorcycle (Zone* pZone , ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x , ZoneCoord_t y , Item* pItem , ObjectID_t ownerOID, Turn_t delay) 
	throw (Error)
: Effect(pZone,x,y,pItem,delay), m_OwnerOID(ownerOID)
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);
	Assert(pTargetZone != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pItem->getObjectID();

	// pTargetZone, x, y
	// m_pZone, m_StartX, m_StartY
	m_pTargetZone = pTargetZone;	
	m_StartX = sx;					
	m_StartY = sy;

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectRecallMotorcycle::~EffectRecallMotorcycle () 
	throw (Error)
{
	__BEGIN_TRY

	__END_CATCH
}
			
//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectRecallMotorcycle::unaffect ()
	throw (Error)
{
	__BEGIN_TRY

	//cout << "EffectRecallMotorcycle unaffect" << endl;

	Zone* pZone = m_pZone;
	ZoneCoord_t x = m_X;
	ZoneCoord_t y = m_Y;

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
	if (isValidZoneCoord(pZone, m_StartX, m_StartY))
	{
		//Assert(isValidZoneCoord(pZone, m_StartX, m_StartY));

		// TempItem ������ ��´�.
		Item* pTempItem = NULL;

		// ���⼭�� ���� �������� ���� �� ������, �� �ٸ� �������� ���� ���� ���� �ִ�.
		// �� ���� �������� �����۰� ���� ���� �ٴڿ� �ִ� �������� ���Ͽ� �����ؾ� �Ѵ�.
		// ���� ���� �����ϸ� �ȴ�.
		Tile & tile = pZone->getTile(m_StartX, m_StartY);

		if (tile.hasItem()) 
		{
			pTempItem = tile.getItem();

			if (pTempItem != NULL)
			{
				// ObjectID�� ���ٴ� ���� ���� �������̶� ���̴�.
				if (pTempItem->getObjectID() == m_ObjectID)
				{
					pZone->deleteItem(pTempItem , m_StartX, m_StartY);

					// �������� ������ٴ� ��Ŷ�� ������.
					GCDeleteObject gcDeleteObject;
					gcDeleteObject.setObjectID(m_ObjectID);

					pZone->broadcastPacket(m_StartX, m_StartY , &gcDeleteObject);

					if (pZone->getZoneGroup()==m_pTargetZone->getZoneGroup())
					{
						m_pTargetZone->addItem( pTempItem, x, y );

						Slayer* pOwner = dynamic_cast<Slayer*>((m_pTargetZone->getCreature(m_OwnerOID)));
						if ( pOwner != NULL )
						{
							EffectRideMotorcycle* pEffect = new EffectRideMotorcycle( pOwner, pTempItem, x, y );
							pEffect->setDeadline(0);
							m_pTargetZone->registerObject( pEffect );
							m_pTargetZone->addEffect( pEffect );
						}
					}
					else
					{
						//cout << "Zone->addItemDelayed" << endl;
						m_pTargetZone->addItemDelayed(pTempItem, x, y);

						Slayer* pOwner = dynamic_cast<Slayer*>((m_pTargetZone->getCreature(m_OwnerOID)));
						if ( pOwner != NULL )
						{
							EffectRideMotorcycle* pEffect = new EffectRideMotorcycle( pOwner, pTempItem, x, y );
							pEffect->setDeadline(0);
							m_pTargetZone->registerObject( pEffect );
							m_pTargetZone->addEffect_LOCKING( pEffect );
						}
					}
				}
			}
		}
	}
	else
	{
		filelog("motorBug.txt", "ZoneID=%d, x=%d, y=%d", (int)pZone->getZoneID(), (int)m_StartX, (int)m_StartY);
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectRecallMotorcycle::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectRecallMotorcycle("
			<< "ZoneID:" << (int)m_pZone->getZoneID()
			<< "TargetZoneID:" << (int)m_pTargetZone->getZoneID()
			<< ",X:"     << (int)getX()
			<< ",Y:"     << (int)getY();

	if (m_pTarget) msg << ",Target:" << m_pTarget->toString();
	else           msg << ",Target:NULL";

	msg << ",Deadline:" << (int)m_Deadline.tv_sec 
			<< "." << (int)m_Deadline.tv_usec;

	msg << ")";

	return msg.toString();
}
