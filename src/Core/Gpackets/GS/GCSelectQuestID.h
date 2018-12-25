//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSelectQuestID.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SELECT_QUEST_ID_H__
#define __GC_SELECT_QUEST_ID_H__

#include <list>
#include "Packet.h"
#include "PacketFactory.h"

#ifdef __GAME_SERVER__
#include <algorithm>
#endif

const BYTE maxQuestNum = 255;

//////////////////////////////////////////////////////////////////////////////
// class GCSelectQuestID;
//////////////////////////////////////////////////////////////////////////////

class GCSelectQuestID : public Packet
{
public:
#ifdef __GAME_SERVER__
	// inItr�� container<QuestID_t>::input_iterator ���� �Ѵ�.
	template<class inItr>
	explicit GCSelectQuestID( inItr b, inItr e ) throw()
	{
		copy( b, e, back_inserter( m_QuestIDList ) );
	}
#endif
	GCSelectQuestID() throw() { }
	virtual ~GCSelectQuestID() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_SELECT_QUEST_ID; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCSelectQuestID"; }
	string toString() ;

public:
	bool		empty() const { return m_QuestIDList.empty(); }
	QuestID_t	popQuestID() { QuestID_t qID = m_QuestIDList.front(); m_QuestIDList.pop_front(); return qID; }
	
private:
	list<QuestID_t>	m_QuestIDList;
};

//////////////////////////////////////////////////////////////////////////////
// class GCSelectQuestIDFactory;
//////////////////////////////////////////////////////////////////////////////

class GCSelectQuestIDFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCSelectQuestID(); }
	string getPacketName()  { return "GCSelectQuestID"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SELECT_QUEST_ID; }
	PacketSize_t getPacketMaxSize() 
	{
		return szBYTE
			 + szQuestID * maxQuestNum;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCSelectQuestIDHandler;
//////////////////////////////////////////////////////////////////////////////

class GCSelectQuestIDHandler 
{
public:
	static void execute(GCSelectQuestID* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
