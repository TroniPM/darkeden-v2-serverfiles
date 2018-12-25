//----------------------------------------------------------------------
//
// Filename    : PacketValidator
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PACKET_ID_SET_H__
#define __PACKET_ID_SET_H__

// include files
#include "Packet.h"
#include "PlayerStatus.h"

#if __LINUX__
	#include <hash_set>
	typedef hash_set<PacketID_t> PACKET_ID_SET;
#elif __WINDOWS__
	#include <set>
	typedef set<PacketID_t> PACKET_ID_SET;
#endif

//----------------------------------------------------------------------
//
// class PacketValidator;
//
// ��Ŷ�� ������ �����Ѵ�.
//
//----------------------------------------------------------------------

class PacketIDSet {

public :

	enum PacketIDSetType {
		PIST_NORMAL ,
		PIST_ANY ,
		PIST_NONE ,
		PIST_IGNORE_EXCEPT
	};

public :

	// constructor
	PacketIDSet (PlayerStatus playerStatus, PacketIDSetType packetIDSetType = PIST_NORMAL);

	// destructor
	~PacketIDSet ();

	// add packet id to set
	void addPacketID (PacketID_t packetID) throw (DuplicatedException);

	// delete packet id from set
	void deletePacketID (PacketID_t packetID) throw (NoSuchElementException);

	// has packet id?
	bool hasPacketID (PacketID_t packetID) ;

	// get player status 
	PlayerStatus getPlayerStatus ()  { return m_PlayerStatus; }

	// get debug string
	string toString () ;

private :

	// Packet ID Set Type 
	PacketIDSetType m_PacketIDSetType;

	// �÷��̾� ����
	PlayerStatus m_PlayerStatus;

	// ���Ǵ� ��Ŷ�� �ؽ���
	PACKET_ID_SET m_PacketIDSet;

};

#endif
