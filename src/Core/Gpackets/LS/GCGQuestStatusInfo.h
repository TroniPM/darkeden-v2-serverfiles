//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGQuestStatusInfo.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GGQUEST_STATUS_INFO_H__
#define __GC_GGQUEST_STATUS_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "QuestStatusInfo.h"

#include <numeric>
#include <functional>

#define MAX_QUEST_NUM 100

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusInfo;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusInfo : public Packet 
{
public:
	GCGQuestStatusInfo() ;
	~GCGQuestStatusInfo() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return Packet::PACKET_GC_GQUEST_STATUS_INFO; }
	PacketSize_t getPacketSize()  { return accumulate( m_Infos.begin(), m_Infos.end(), szBYTE, addSize ); }
	string getPacketName()  { return "GCGQuestStatusInfo"; }
	string toString() ;

public:
	static PacketSize_t	addSize( PacketSize_t tot, const QuestStatusInfo* pInfo ) { return tot + pInfo->getSize(); }

	list<QuestStatusInfo*>&	getInfos() { return m_Infos; }
	const list<QuestStatusInfo*>&	getInfos() const { return m_Infos; }

private:
	list<QuestStatusInfo*>	m_Infos;
};


//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusInfoFactory : public PacketFactory 
{
public :
	GCGQuestStatusInfoFactory()  {}
	virtual ~GCGQuestStatusInfoFactory()  {}
	
public:
	Packet* createPacket()  { return new GCGQuestStatusInfo(); }
	string getPacketName()  { return "GCGQuestStatusInfo"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_GQUEST_STATUS_INFO; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + QuestStatusInfo::getMaxSize() * MAX_QUEST_NUM; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusInfoHandler 
{
public:
	static void execute(GCGQuestStatusInfo* pGCGQuestStatusInfo, Player* pPlayer);

};

#endif
