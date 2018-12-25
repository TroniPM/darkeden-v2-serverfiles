///////////////////////////////////////////////////////////////////////////
// File : DragonEyeManager.h
///////////////////////////////////////////////////////////////////////////

#ifndef __DRAGON_EYE_MANAGER_H__
#define __DRAGON_EYE_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <vector>
#include "item/WarItem.h"

///////////////////////////////////////////////////////////////////////////
// class DragonEyeManager
///////////////////////////////////////////////////////////////////////////
class DragonEyeManager
{
public:
	typedef vector<WarItem*>			VectorWarItem;
	typedef vector<ZONE_COORD>			VectorZoneCoord;

public:
	// constructor & desctructor
	DragonEyeManager();
	~DragonEyeManager();

public:
	void init();
	void initDefaultPositions();
	void createAllDragonEyes();

	void addAllDragonEyesToZone();

	void removeAllDragonEyes();

	void warpToDefaultPosition( Creature* pCreature );

private:
	VectorWarItem		m_DragonEyes;
	VectorZoneCoord		m_DefaultPositions;
};

extern DragonEyeManager* g_pDragonEyeManager;

#endif

