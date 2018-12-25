//////////////////////////////////////////////////////////////////////////////
// FileName		: Tile.h
// Written By	: reiot@ewestsoft.com
// Description	: 
//////////////////////////////////////////////////////////////////////////////

#ifndef __TILE_H__
#define __TILE_H__

#include <slist>
#include "Types.h"
#include "Exception.h"
#include "Object.h"
#include "Creature.h"
#include "Item.h"
#include "Obstacle.h"
#include "Effect.h"
#include "Portal.h"
#include "Sector.h"

// macro
#define FLAG_ZERO(set)       (set=0)
#define FLAG_SET(set,flag)   (set|=(1<<(flag)))
#define FLAG_CLEAR(set,flag) (set&=~(1<<(flag)))
#define FLAG_ISSET(set,flag) (set&(1<<(flag)))

// type redefinition
typedef WORD BuildingID_t;
typedef WORD TerrainID_t;

//////////////////////////////////////////////////////////////////////////////
// Tile class:
//////////////////////////////////////////////////////////////////////////////

class Packet;

class Tile 
{
public:
	enum TileFlags 
	{
		TILE_GROUND_BLOCKED = 0 ,	// Ÿ���� ������ ������ ���
		TILE_AIR_BLOCKED ,			// Ÿ���� ������ ������ ���
		TILE_UNDERGROUND_BLOCKED ,	// Ÿ���� ���ϰ� ������ ���
		TILE_WALKING_CREATURE ,		// Ÿ���� ���� ũ��ó�� ���� ��� 
		TILE_FLYING_CREATURE ,		// Ÿ���� ���߿� ũ��ó�� ���� ��� 
		TILE_BURROWING_CREATURE ,	// Ÿ���� ���Ͽ� ũ��ó�� ���� ��� 
		TILE_ITEM, 					// Ÿ�� ���� �������� ���� ���� ���
		TILE_OBSTACLE ,				// Ÿ�� ���� ���¸� ���� ��ֹ��� ���� ���� ���
		TILE_EFFECT,				// Ÿ�� ���� ���� ��ü�� ���� ��� 
		TILE_BUILDING ,				// Ÿ�� ���� �ǹ��� ���� ���
		TILE_PORTAL ,				// Ÿ�� ���� ��Ż�� ���� ���� ��� 
		TILE_TERRAIN				// ȿ���� �ִ� ��� Ÿ���� ���
	};

public:
	Tile(WORD m_Flag = 0, WORD m_Opt = 0) throw();
	~Tile() throw();

public:
	bool addCreature(Creature* pCreature, bool bCheckEffect=true, bool bCheckPortal=true) throw(GameException, DuplicatedException, Error);
	void deleteCreature(ObjectID_t creatureID) throw(NoSuchElementException, Error);
	void deleteCreature(Creature::MoveMode mode) throw(NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t creatureID) throw(NoSuchElementException, Error);
	Creature* getCreature(Creature::MoveMode mode) throw(NoSuchElementException, Error);

	bool hasWalkingCreature()  { return FLAG_ISSET(m_wFlags, TILE_WALKING_CREATURE) > 0; }
	bool hasFlyingCreature()  { return FLAG_ISSET(m_wFlags, TILE_FLYING_CREATURE) > 0; }
	bool hasBurrowingCreature()  { return FLAG_ISSET(m_wFlags, TILE_BURROWING_CREATURE) > 0; }
	bool hasCreature(Creature::MoveMode mode)  { return FLAG_ISSET(m_wFlags, mode + TILE_WALKING_CREATURE) > 0; }
	bool hasCreature()  { 
		return FLAG_ISSET(m_wFlags, TILE_WALKING_CREATURE) ||
			   FLAG_ISSET(m_wFlags, TILE_BURROWING_CREATURE) ||
			   FLAG_ISSET(m_wFlags, TILE_FLYING_CREATURE) ; 
	}

public:
	void addItem(Item* pItem) throw(DuplicatedException, Error);
	void deleteItem() throw(NoSuchElementException, Error);
	Item* getItem() throw(NoSuchElementException, Error);
	bool hasItem()  { return FLAG_ISSET(m_wFlags, TILE_ITEM) > 0; }
	
public:
	void addObstacle(Obstacle* pObstacle) throw(DuplicatedException, Error);
	void deleteObstacle() throw(NoSuchElementException, Error);
	Obstacle* getObstacle() throw(NoSuchElementException, Error);
	bool hasObstacle()  { return FLAG_ISSET(m_wFlags, TILE_OBSTACLE) > 0; }

public:
	void addEffect(Effect* pEffect) throw(DuplicatedException, Error);
	bool canAddEffect() throw(Error);
	void deleteEffect(ObjectID_t effectID) throw(NoSuchElementException, Error);
	Effect* getEffect(ObjectID_t effectID) throw(NoSuchElementException, Error);
	bool hasEffect()  { return FLAG_ISSET(m_wFlags, TILE_EFFECT) > 0; }
	Effect* getEffect(Effect::EffectClass effectClass) throw(Error);

public:
	void addBuilding(BuildingID_t buildingID) throw(Error);
	void deleteBuilding() throw(Error);
	BuildingID_t getBuilding() ;
	bool hasBuilding()  { return FLAG_ISSET(m_wFlags, TILE_BUILDING) > 0; }

public:
	void addPortal(Portal* pPortal) throw(Error);
	void deletePortal() throw(Error);
	Portal* getPortal() ;
	bool hasPortal()  { return FLAG_ISSET(m_wFlags, TILE_PORTAL) > 0; }

public:
	void addTerrain(TerrainID_t terrainID) throw(Error);
	void deleteTerrain() throw(Error);
	TerrainID_t getTerrain() ;
	bool isTerrain()  { return FLAG_ISSET(m_wFlags, TILE_TERRAIN) > 0; }

public:
	bool isGroundBlocked()  { return FLAG_ISSET(m_wFlags, TILE_GROUND_BLOCKED) > 0; }
	bool isAirBlocked()  { return FLAG_ISSET(m_wFlags, TILE_AIR_BLOCKED) > 0; }
	bool isUndergroundBlocked()  { return FLAG_ISSET(m_wFlags, TILE_UNDERGROUND_BLOCKED) > 0; }
	bool isBlocked(Creature::MoveMode mode)  { return FLAG_ISSET(m_wFlags, TILE_GROUND_BLOCKED + mode) > 0; }
	void setBlocked(Creature::MoveMode mode) throw() { FLAG_SET(m_wFlags, TILE_GROUND_BLOCKED + mode); }
	void clearBlocked(Creature::MoveMode mode) throw() { FLAG_CLEAR(m_wFlags, TILE_GROUND_BLOCKED + mode); }

	bool isFixedGroundBlocked()  { return isGroundBlocked() && !hasWalkingCreature(); }

public:
	void addObject(Object* pObject) throw(DuplicatedException);
	void deleteObject(ObjectID_t objectID) throw(NoSuchElementException);
	void deleteObject(ObjectPriority tilePriority) throw(NoSuchElementException);
	Object* getObject(ObjectID_t objectID) ;
	Object* getObject(ObjectPriority tilePriority) ;

public:
	WORD getOption()  { return m_wOption; }
	void setOption(WORD option) throw() { m_wOption = option; }

public:
	Sector* getSector(void) const { return m_pSector; }
	void setSector(Sector* pSector) { m_pSector = pSector; }

public:
	const slist<Object*> & getObjectList()  { return m_Objects; }
	slist<Object*> & getObjectList() throw() { return m_Objects; }

	string toString() ;

private:
	WORD           m_wFlags;  // Ÿ�� �Ӽ� �÷���
	WORD           m_wOption; // �ɼ� �÷���, Ÿ�� �Ӽ� �÷��׿� ���� �ٸ��� ���ȴ�.
	slist<Object*> m_Objects; // ������Ʈ �������� ����Ʈ
	Sector*        m_pSector; // �� Ÿ���� ���� ���Ϳ� ���� ������
};

#endif
