//----------------------------------------------------------------------
//
// Filename    : EffectAddMonster.cpp
// Written by  : Reiot
//
//----------------------------------------------------------------------

// include files
#include "Assert.h"
#include "EffectAddMonster.h"
#include "Gpackets/GCDeleteObject.h"
#include "Tile.h"
#include "Zone.h"
#include "Item.h"
#include "ZoneUtil.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
EffectAddMonster::EffectAddMonster (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pCreature , Turn_t delay)
	throw (Error)
: Effect(pZone,x,y,pCreature,delay) 
{
	__BEGIN_TRY

	// ���� ���� Effect�̴�. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	Assert(getZone() != NULL);
	Assert(getTarget() != NULL);

	//m_ObjectID = pItem->getObjectID();
	m_ObjectID = pCreature->getObjectID();

	__END_CATCH
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
EffectAddMonster::~EffectAddMonster () 
	throw (Error)
{
	__BEGIN_TRY

	unaffect(m_pZone , m_X , m_Y , (Creature*)m_pTarget);

	__END_CATCH
}
			

//----------------------------------------------------------------------
// affect to target
// �� ����Ʈ�� Ÿ�Ͽ� ���ӵ��� �����Ƿ�, affect()�� ȣ����� �ʴ´�.
// �ֳ��ϸ�, target�� �����ڿ��� �����Ǹ�, �ƹ��� �ϵ� ���� �ʱ� �����̴�.
//----------------------------------------------------------------------
void EffectAddMonster::affect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pTarget)
	throw (Error)
{
	__BEGIN_TRY

//	throw UnsupportedError();
	
	__END_CATCH
}


//----------------------------------------------------------------------
// remove effect from target
//----------------------------------------------------------------------
void EffectAddMonster::unaffect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Creature* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	// �ùٸ� ��ǥ�̾�� �Ѵ�.
	Assert(pTarget!=NULL);
	Assert(isValidZoneCoord(pZone, x, y));

	Monster* pMonster = dynamic_cast<Monster*>(pTarget);

	if (pMonster!=NULL)
	{
		//pZone->getObjectRegistry().registerObject(pMonster);

		TPOINT pt = pZone->addCreature(pMonster, x, y, 2);

		cout << pZone->getZoneID() << "���� (" << x << "," << y << ")�� ���Ͱ� �߰��Ǿ����ϴ�" << endl;

		if (pt.x == -1)
		{
			SAFE_DELETE(pMonster);
			throw Error("Zone�� ���� �� �ڸ��� ����");
		}
	}
	else
	{
		SAFE_DELETE(pMonster);
		throw Error("EffectAddMonster�ε� item�� �ƴѰ�?");
	}

	pTarget = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddMonster::unaffect ()
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// unaffect()
//----------------------------------------------------------------------
void EffectAddMonster::unaffect (Creature* pCreature)
	throw (Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string EffectAddMonster::toString () const 
	throw ()
{
	StringStream msg;

	msg << "EffectAddMonster("
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
