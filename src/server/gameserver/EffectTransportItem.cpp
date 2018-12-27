//----------------------------------------------------------------------
//
// Filename    : EffectTransportItem.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectTransportItem.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectTransportItem::EffectTransportItem (Zone* pZone , ZoneCoord_t sx, ZoneCoord_t sy, Zone* pTargetZone, ZoneCoord_t x , ZoneCoord_t y , Item* pItem , Turn_t delay) 
	
: Effect(pZone,x,y,pItem,delay) 
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
EffectTransportItem::~EffectTransportItem () 
	
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
void EffectTransportItem::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectTransportItem::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	//cout << "EffectTransportItem unaffect(pZone,x,y,pTarget)" << endl;

	// pTargetZone, x, y
	// m_pZone, m_StartX, m_StartY

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

			if (pTempItem != NULL) {
				// ObjectID�� ���ٴ� ���� ���� �������̶� ���̴�.
				//if (pTempItem->getObjectID() == m_ObjectID) {
				if (pTempItem->getObjectID() == m_ObjectID) {

					pZone->deleteItem(pTempItem , m_StartX, m_StartY);

					// �������� ������ٴ� ��Ŷ�� ������.
					GCDeleteObject gcDeleteObject;
					gcDeleteObject.setObjectID(m_ObjectID);

					pZone->broadcastPacket(m_StartX, m_StartY , &gcDeleteObject);

					// �ٸ� ���� �߰��Ѵ�.
					// Multi-thread�̹Ƿ�.. ��������..
					// ���� ZoneGroup�̸� �� �ִ´�.
					if (pZone->getZoneGroup()==m_pTargetZone->getZoneGroup())
					//if (pZone==m_pTargetZone)
					{
						//cout << "Zone->addItem" << endl;
						m_pTargetZone->addItem(pTempItem, x, y);
					}
					else
					{
						//cout << "Zone->addItemDelayed" << endl;
						m_pTargetZone->addItemDelayed(pTempItem, x, y);
					}

					//cout << "addItemDelayed OK" << endl;
				}
			}
		}
	}
	else
	{
		filelog("motorBug.txt", "ZoneID=%d, x=%d, y=%d", (int)pZone->getZoneID(), (int)m_StartX, (int)m_StartY);
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectTransportItem::unaffect ()
	
{
	__BEGIN_TRY

	//cout << "EffectTransportItem unaffect" << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectTransportItem::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectTransportItem::toString () const 
	
{
	StringStream msg;

	msg << "EffectTransportItem("
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
