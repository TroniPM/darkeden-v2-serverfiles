//--------------------------------------------------------------------------------
// 
// Filename    : RaceWarInfo.h 
// Written By  : 
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __RACE_WAR_LIST_H__
#define __RACE_WAR_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "WarInfo.h"

//--------------------------------------------------------------------------------
//
// class WarInfo;
//
// �ϳ��� ���￡ ���� ����
//
//--------------------------------------------------------------------------------

class RaceWarInfo : public WarInfo {

public :
	typedef ValueList<ZoneID_t>	ZoneIDList;

public :
	RaceWarInfo() {}
	~RaceWarInfo() {}
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	PacketSize_t getSize() const throw() 
	{ 
		return WarInfo::getSize() + m_CastleIDs.getPacketSize();
	}

	static PacketSize_t getMaxSize() throw() 
	{
		return WarInfo::getMaxSize() + ZoneIDList::getPacketMaxSize();
	}

	// get packet's debug string
	string toString() const throw();

public :
	WarType_t 			getWarType() const 			{ return WAR_RACE; }

	ZoneIDList& 		getCastleIDs() 				{ return m_CastleIDs; }
	void 				addCastleID(ZoneID_t zid) 	{ m_CastleIDs.addValue( zid ); }

	void	operator = (const RaceWarInfo& RWI)
	{
		m_StartTime = RWI.m_StartTime;
		m_RemainTime = RWI.m_RemainTime;
		m_CastleIDs = RWI.m_CastleIDs;
	}

private :
	ZoneIDList			m_CastleIDs;		// �������� ��
};

#endif
