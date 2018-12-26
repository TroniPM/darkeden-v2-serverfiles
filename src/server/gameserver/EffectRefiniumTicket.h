//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRefiniumTicket.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REFINIUM_TICKET__
#define __EFFECT_REFINIUM_TICKET__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRefiniumTicket
//////////////////////////////////////////////////////////////////////////////

class EffectRefiniumTicket : public Effect 
{
public:
	EffectRefiniumTicket(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_REFINIUM_TICKET; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	void setExit( uint exit ) { m_Exit = exit; }
	uint getExit() const { return m_Exit; }

	ZoneID_t getPrevExitZoneID(){ return m_PrevExitZoneID; }
	ZoneCoord_t getPrevExitX(){ return m_PrevExitX; }
	ZoneCoord_t getPrevExitY(){ return m_PrevExitY; }

	void setPrevExitZoneID( ZoneID_t PrevExitZoneID ) { m_PrevExitZoneID=PrevExitZoneID; }
	void setPrevExitX( ZoneCoord_t PrevExitX ) { m_PrevExitX=PrevExitX; }
	void setPrevExitY( ZoneCoord_t PrevExitY ) { m_PrevExitY=PrevExitY; }

	string toString() ;

private:
	uint m_Exit;
	ZoneID_t m_PrevExitZoneID;
	ZoneCoord_t m_PrevExitX;
	ZoneCoord_t m_PrevExitY;
};

#endif // __EFFECT_REFINIUM_TICKET__
