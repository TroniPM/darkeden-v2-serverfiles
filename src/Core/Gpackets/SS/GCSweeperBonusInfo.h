//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSweeperBonusInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SWEEPER_BONUS_INFO_H__
#define __GC_SWEEPER_BONUS_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "SweeperBonusInfo.h"
#include <list>

typedef list<SweeperBonusInfo*> SweeperBonusInfoList;
typedef SweeperBonusInfoList::const_iterator SweeperBonusInfoListConstItor;

//////////////////////////////////////////////////////////////////////
//
// class GCSweeperBonusInfo;
//
//////////////////////////////////////////////////////////////////////

class GCSweeperBonusInfo : public Packet {

public :

	// constructor
	GCSweeperBonusInfo() throw();

	// destructor
	~GCSweeperBonusInfo() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SWEEPER_BONUS_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ;

	// get packet name
	string getPacketName()  { return "GCSweeperBonusInfo"; }
	
	// get packet's debug string
	string toString() ;

public:

	BYTE getListNum()  { return m_SweeperBonusInfoList.size(); }

	void addSweeperBonusInfo( SweeperBonusInfo* pSweeperBonusInfo ) throw() { m_SweeperBonusInfoList.push_back( pSweeperBonusInfo ); }

	void clearSweeperBonusInfoList() throw();

	SweeperBonusInfo* popFrontSweeperBonusInfoList() throw()
	{
		if ( !m_SweeperBonusInfoList.empty() )
		{
			SweeperBonusInfo* pSweeperBonusInfo = m_SweeperBonusInfoList.front();
			m_SweeperBonusInfoList.pop_front();
			return pSweeperBonusInfo;
		}
		return NULL;
	}


private :
	
	SweeperBonusInfoList m_SweeperBonusInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCSweeperBonusInfoFactory;
//
// Factory for GCSweeperBonusInfo
//
//////////////////////////////////////////////////////////////////////

class GCSweeperBonusInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSweeperBonusInfo(); }

	// get packet name
	string getPacketName()  { return "GCSweeperBonusInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SWEEPER_BONUS_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + SweeperBonusInfo::getMaxSize() * 12 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSweeperBonusInfo;
//
//////////////////////////////////////////////////////////////////////

class GCSweeperBonusInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCSweeperBonusInfo* pPacket, Player* pPlayer) ;

};

#endif
