//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLSelectPC.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_SELECT_PC_H__
#define __CL_SELECT_PC_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Player.h"

//////////////////////////////////////////////////////////////////////
//
// class CLSelectPC;
//
// �÷����� PC �� �����ϴ� ��Ŷ�̴�.
//
//////////////////////////////////////////////////////////////////////

class CLSelectPC : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CL_SELECT_PC; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_PCName.size() 	// pc name
			+ szPCType; 					// pc type
	}

	// get packet's name
	string getPacketName()  { return "CLSelectPC"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set creature's name
	string getPCName()  { return m_PCName; }
	void setPCName(string pcName) throw() { m_PCName = pcName; }

	// get/set pc type
	PCType getPCType()  { return m_PCType; }
	void setPCType(PCType pcType) throw() { m_PCType = pcType; }

private :
	
	// Name
	string m_PCName;

	// Slayer or Vampire?
	PCType m_PCType;

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectPCFactory;
//
// Factory for CLSelectPC
//
//////////////////////////////////////////////////////////////////////

class CLSelectPCFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLSelectPC(); }

	// get packet name
	string getPacketName()  { return "CLSelectPC"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_SELECT_PC; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() 
	{
		return szBYTE + 20		 	// name
			+ szPCType; 			// pc type
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectPCHandler;
//
//////////////////////////////////////////////////////////////////////

class CLSelectPCHandler {

public:

	// execute packet's handler
	static void execute(CLSelectPC* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
