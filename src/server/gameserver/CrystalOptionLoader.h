//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemMineInfo.h
// Written By  : bezz, sequoia, dew
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CRYSTAL_OPTION_LODER_H__
#define __CRYSTAL_OPTION_LODER_H__

#include "Exception.h"
#include "Types.h"
#include "Item.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// Class ItemMineInfo
//////////////////////////////////////////////////////////////////////////////

class CrystalOptionLoader 
{
public:
	CrystalOptionLoader();
	~CrystalOptionLoader();

public:
	int getID() const { return m_ID; }
	void setID( int id ) { m_ID = id; }

	int getItemOptions() const { return m_ItemOptions; }
	void setItemOptions( int itemOptions ) { m_ItemOptions = itemOptions; }

	int getItemOptionRatio() const { return m_ItemOptionRatio; }
	void setItemOptionRatio( int ItemOptionRatio) { m_ItemOptionRatio = ItemOptionRatio; }


	string toString() const;

private:
	int					m_ID;			// CrystalOptionLoader ID
	int	m_ItemOptions;	// Item Options
	int	m_ItemOptionRatio;
};

//////////////////////////////////////////////////////////////////////////////
// Class CrystalOptionLoaderManager
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<int, CrystalOptionLoader*>			HashMapCrystalOptionLoader;
typedef HashMapCrystalOptionLoader::iterator			HashMapCrystalOptionLoaderItor;
typedef HashMapCrystalOptionLoader::const_iterator		HashMapCrystalOptionLoaderConstItor;

class CrystalOptionLoaderManager 
{
public:
	CrystalOptionLoaderManager();
	~CrystalOptionLoaderManager();

public:

	// void load() throw();
	void load();
	
	// get CrystalOptionLoader
	CrystalOptionLoader* getCrystalOptionLoader(int id) const;

	// add CrystalOptionLoader
	void addCrystalOptionLoader(CrystalOptionLoader* pCrystalOptionLoader) throw(DuplicatedException, Error);

	int getRandomItem(int minID, int maxID);

	// toString for Debug
	string toString() const;

private:
	HashMapCrystalOptionLoader m_CrystalOptionLoaders;
};

// Global Variable Definition
extern CrystalOptionLoaderManager* g_pCrystalOptionLoaderManager;

#endif	// __ITEM_MINE_INFO_MANAGER_H__
