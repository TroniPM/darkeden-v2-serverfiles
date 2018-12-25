//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHolyLandBonusInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HOLY_LAND_BONUS_INFO_H__
#define __GC_HOLY_LAND_BONUS_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "BloodBibleBonusInfo.h"
#include <list>

typedef list<BloodBibleBonusInfo*> BloodBibleBonusInfoList;
typedef BloodBibleBonusInfoList::const_iterator BloodBibleBonusInfoListConstItor;

//////////////////////////////////////////////////////////////////////
//
// class GCHolyLandBonusInfo;
//
//////////////////////////////////////////////////////////////////////

class GCHolyLandBonusInfo : public Packet {

public :

	// constructor
	GCHolyLandBonusInfo() throw();

	// destructor
	~GCHolyLandBonusInfo() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_HOLY_LAND_BONUS_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() ;

	// get packet name
	string getPacketName()  { return "GCHolyLandBonusInfo"; }
	
	// get packet's debug string
	string toString() ;

public:

	BYTE getListNum()  { return m_BloodBibleBonusInfoList.size(); }

	void addBloodBibleBonusInfo( BloodBibleBonusInfo* pBloodBibleBonusInfo ) throw() { m_BloodBibleBonusInfoList.push_back( pBloodBibleBonusInfo ); }

	void clearBloodBibleBonusInfoList() throw();

	BloodBibleBonusInfo* popFrontBloodBibleBonusInfoList() throw()
	{
		if ( !m_BloodBibleBonusInfoList.empty() )
		{
			BloodBibleBonusInfo* pBloodBibleBonusInfo = m_BloodBibleBonusInfoList.front();
			m_BloodBibleBonusInfoList.pop_front();
			return pBloodBibleBonusInfo;
		}
		return NULL;
	}


private :
	
	BloodBibleBonusInfoList m_BloodBibleBonusInfoList;	
};


//////////////////////////////////////////////////////////////////////
//
// class GCHolyLandBonusInfoFactory;
//
// Factory for GCHolyLandBonusInfo
//
//////////////////////////////////////////////////////////////////////

class GCHolyLandBonusInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCHolyLandBonusInfo(); }

	// get packet name
	string getPacketName()  { return "GCHolyLandBonusInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_HOLY_LAND_BONUS_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + BloodBibleBonusInfo::getMaxSize() * 12 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCHolyLandBonusInfo;
//
//////////////////////////////////////////////////////////////////////

class GCHolyLandBonusInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCHolyLandBonusInfo* pPacket, Player* pPlayer) ;

};

#endif
