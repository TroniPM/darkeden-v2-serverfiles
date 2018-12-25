//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDeleteTile.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectDeleteTile.h"
#include "Zone.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteEffectFromTile.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDeleteTile::EffectDeleteTile(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDeleteTile::affect()
	throw(Error)
{
	__BEGIN_TRY

	// ������ �ѷ��ش�. -> ��� �� ��
/*	GCAddEffectToTile gcAddEffectToTile;
	gcAddEffectToTile.setEffectID( getEffectClass() );
	gcAddEffectToTile.setObjectID( getObjectID() );
	gcAddEffectToTile.setXY( m_X, m_Y );
	gcAddEffectToTile.setDuration( 999999 );

	m_pZone->broadcastPacket( m_X, m_Y, &gcAddEffectToTile );
*/
	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDeleteTile::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDeleteTile::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDeleteTile::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	cout << "delete effect " << m_X << " , " << m_Y << endl;
	Tile& EffectedTile = m_pZone->getTile(m_X, m_Y);
	EffectedTile.deleteEffect(m_ObjectID);

	// ����Ʈ�� ������ٰ� �˷��ش�.
	GCDeleteEffectFromTile gcDeleteEffectFromTile;
	gcDeleteEffectFromTile.setEffectID(Effect::EFFECT_CLASS_DELETE_TILE);
	gcDeleteEffectFromTile.setObjectID(m_ObjectID);
	gcDeleteEffectFromTile.setXY(m_X, m_Y);
	m_pZone->broadcastPacket(&gcDeleteEffectFromTile);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDeleteTile::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectDeleteTile("
		<< "ObjectID:" << (int)getObjectID()
		<< ",Zone:" << (int)m_pZone
		<< ",X:" << (int)m_X
		<< ",Y:" << (int)m_Y
		<< ")";

	return msg.toString();

	__END_CATCH

}

EffectDeleteTileLoader* g_pEffectDeleteTileLoader = NULL;
