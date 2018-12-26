//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDecayCorpse.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Assert.h"
#include "EffectDecayCorpse.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Corpse.h"
#include "SlayerCorpse.h"
#include "VampireCorpse.h"
#include "MonsterCorpse.h"
#include "ZoneUtil.h"

EffectDecayCorpse::EffectDecayCorpse (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Corpse* pCorpse , Turn_t delay) 
	
: Effect(pZone,x,y,pCorpse,delay) 
{
	__BEGIN_TRY

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	m_ObjectID = pCorpse->getObjectID();

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

EffectDecayCorpse::~EffectDecayCorpse () 
	
{
	__BEGIN_TRY

	unaffect(m_pZone , m_X , m_Y , m_pTarget);

	__END_CATCH
}
			
void EffectDecayCorpse::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

void EffectDecayCorpse::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget)
	
{
	__BEGIN_TRY

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
	Assert(isValidZoneCoord(pZone, x, y));

	// ��ü�� �����Ѵ�.
	if (pZone->getTile(x,y).hasItem()) 
	{
		Item* pItem = pZone->getTile(x,y).getItem();

		if (pItem != NULL) 
		{
			// Ÿ������ �������� �ְ� �� �������� ������Ʈ ���̵� �Ȱ��ƾ߸� �� ���� ��ü�̴�.
			if (pItem->getObjectID() == m_ObjectID) 
			{
				Corpse* pCorpse = dynamic_cast<Corpse*>(pTarget);
				try 
				{
					// ��ü�� ������ �����Ѵ�.
					Assert(pZone->getTile(x,y).getItem() == pCorpse);
					pZone->deleteItem(pCorpse , x, y);
				} 
				catch (NoSuchElementException & nsee) 
				{
					cerr << "EffectDecayCorpse::unaffect() : NoSuchElementException" << endl;
					throw Error(nsee.toString());
				}

				GCDeleteObject gcDeleteObject;
				gcDeleteObject.setObjectID(pCorpse->getObjectID());
				pZone->broadcastPacket(x, y , &gcDeleteObject);

				// ��ü ��ü�� �����Ѵ�.
				SAFE_DELETE(pCorpse);
			}
		}
	}

	pTarget = NULL;

	__END_CATCH
}

void EffectDecayCorpse::unaffect ()
	
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectDecayCorpse::unaffect (Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectDecayCorpse::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectDecayCorpse("
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
