#ifndef __GUILD_UNION_H__
#define __GUILD_UNION_H__

#include "Types.h"
#include "Exception.h"
#include <list>
#include <hash_map>
#include "Gpackets/GCUnionOfferList.h"

#include "Mutex.h"

class GuildUnionManager;
class GuildUnion
{
public:
	GuildUnion(GuildID_t master) : m_MasterGuildID(master) { }
	~GuildUnion();
		
	GuildID_t	getMasterGuildID() const { return m_MasterGuildID; }

	uint		getUnionID() const { return m_UnionID; }
	void		setUnionID( uint ID ) { m_UnionID = ID; }

	bool		hasGuild( GuildID_t gID ) const;
	bool		addGuild( GuildID_t gID ) throw(Error);
	bool		removeGuild( GuildID_t gId ) throw(Error);

	void		create() throw(Error);
	void		destroy() throw(Error);

	list<GuildID_t>	getGuildList()	const	{ return m_Guilds; }
	
protected:
	list<GuildID_t>::const_iterator findGuildItr( GuildID_t gID ) const { return find( m_Guilds.begin(), m_Guilds.end(), gID ); }
	list<GuildID_t>::iterator findGuildItr( GuildID_t gID ) { return find( m_Guilds.begin(), m_Guilds.end(), gID ); }

private:
	uint		m_UnionID;
	GuildID_t	m_MasterGuildID;
	list<GuildID_t>	m_Guilds;

	friend class GuildUnionManager;
};

class GuildUnionManager
{
public:
	GuildUnionManager();
	~GuildUnionManager();

	void	reload()	throw(Error);
	void	load() throw(Error);
	void	addGuildUnion( GuildUnion* pUnion );
	GuildUnion*	getGuildUnion( GuildID_t gID ) { return m_GuildUnionMap[gID]; }
	GuildUnion* getGuildUnionByUnionID( uint uID ) { return m_UnionIDMap[uID]; }

	bool	addGuild( uint uID, GuildID_t gID ) throw(Error);
	bool 	removeMasterGuild(GuildID_t gID) throw(Error);
	bool	removeGuild( uint uID, GuildID_t gID ) throw(Error);

	void	sendRefreshCommand()	throw(Error);
	void	sendModifyUnionInfo(uint gID)	throw(Error);
	
	static GuildUnionManager& Instance()
	{
		static GuildUnionManager theInstance;
		return theInstance;
	}

private:
	list<GuildUnion*>					m_GuildUnionList;
	hash_map<GuildID_t, GuildUnion*>	m_GuildUnionMap;
	hash_map<uint, GuildUnion*>			m_UnionIDMap;


	// Mutex
	mutable Mutex m_Mutex;
};

class GuildUnionOffer
{
public:
	enum OfferType
	{
		JOIN,
		QUIT
	};
	BYTE	m_Type;
	GuildID_t	m_GuildID;
	string		m_MasterID;
	string		m_GuildName;
	string		m_MasterName;

};

class GuildUnionOfferManager
{
public:
	enum ErrorType
	{
		OK = 0,
		ALREADY_IN_UNION,
		ALREADY_OFFER_SOMETHING,
		TARGET_IS_NOT_MASTER,	// ������ �����Ͱ� �ƴ϶��;;
		NOT_IN_UNION,
		MASTER_CANNOT_QUIT,		// ������ ������ ���� ������ Ż��Ұ�(������尡 �������� ����-�ڵ��̷�)
		NO_TARGET_UNION,
		NOT_YOUR_UNION,
		SOURCE_IS_NOT_MASTER,	// ��û�� ����� �����Ͱ� �ƴϴ�
		YOU_HAVE_PENALTY,		// ������ Ż���� ����� �ִ�. ��û�� �� ����
		NOT_ENOUGH_SLOT,			// OfferJoin��...������ �� �ִ� Slot�� ���� �ִ�.
		TOO_MANY_MEMBER				// ����� 50�� �̻��̶� ������ �� ����.
			
		
	};
	uint	offerJoin( GuildID_t gID, GuildID_t MasterGID ) throw(Error);	// ���հ��� ��û
	uint	offerQuit( GuildID_t gID ) throw(Error);						// ����Ż�� ��û

	uint	acceptJoin( GuildID_t gID ) throw(Error);						// ���հ��� ����
	uint	acceptQuit( GuildID_t gID ) throw(Error);						// ����Ż�� ����

	uint	denyJoin( GuildID_t gID ) throw(Error);							// ���հ��� �ź�
	uint	denyQuit( GuildID_t gID ) throw(Error);							// ����Ż�� �ź�

	void	clearOffer( GuildID_t gID ) throw(Error);	
	bool	hasOffer( GuildID_t gID ) throw(Error);

	bool	makeOfferList( uint uID, GCUnionOfferList& offerList ) throw(Error);	// ��Ͽ�û

	static GuildUnionOfferManager& Instance()
	{
		static GuildUnionOfferManager theInstance;
		return theInstance;
	}
};

#endif
