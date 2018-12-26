//////////////////////////////////////////////////////////////////////////////
// Filename    : Sector.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SECTOR_H__
#define __SECTOR_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>

const int SECTOR_SIZE = 13;

//////////////////////////////////////////////////////////////////////////////
// class Sector
//////////////////////////////////////////////////////////////////////////////

class Object;

class Sector
{
public:
	Sector() ;
	~Sector() ;

public:
	void addObject(Object* pObject) throw (DuplicatedException, Error);
	void deleteObject(ObjectID_t id) throw (NoSuchElementException, Error);
	Object* getObject(ObjectID_t id) throw (NoSuchElementException, Error);

	Sector* getNearbySector(uint dir);
	void setNearbySector(uint dir, Sector* pSector);

	const hash_map<ObjectID_t, Object*>& getObjects(void) const { return m_Objects; }
	uint getSize(void)  { return m_Objects.size(); }

	string toString(void) ;

protected:
	hash_map<ObjectID_t, Object*> m_Objects;
	Sector* m_pNearbySectors[9];
};

#endif
