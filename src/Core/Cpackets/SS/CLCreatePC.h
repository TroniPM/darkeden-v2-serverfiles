//----------------------------------------------------------------------
// 
// Filename    : CLCreatePC.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __CL_CREATE_PC_H__
#define __CL_CREATE_PC_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include <bitset>

//----------------------------------------------------------------------
//
// class CLCreatePC;
//
// �����̾� ĳ���͸� ���� ���� ���, �� ��Ŷ�� ������ ��Ƽ� ������ �����Ѵ�.
//
//----------------------------------------------------------------------

class CLCreatePC : public Packet {

public:

    enum {
        SLAYER_BIT_SEX ,
		SLAYER_BIT_HAIRSTYLE ,
		SLAYER_BIT_HAIRSTYLE2 ,
		SLAYER_BIT_MAX
    };

	enum {
		SLAYER_COLOR_HAIR ,
		SLAYER_COLOR_SKIN ,
		SLAYER_COLOR_SHIRT ,
		SLAYER_COLOR_SHIRT2 ,
		SLAYER_COLOR_JEANS ,
		SLAYER_COLOR_JEANS2 ,
		SLAYER_COLOR_MAX
	};


public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CL_CREATE_PC; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CLCreatePCPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  
	{ 
		return szBYTE + m_Name.size() 	// �̸�
			+ szSlot					// ����
			+ szBYTE					// �����̾� �÷���(3 bit)
			+ szAttr* 3
			+ szColor* SLAYER_COLOR_MAX ; // ���� ����
	}

	// get packet's name
	string getPacketName()  { return "CLCreatePC"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set name
	string getName()  { return m_Name; }
	void setName(string name) throw() { m_Name = name; }

	// get/set slot
	Slot getSlot()  { return m_Slot; }
	void setSlot(Slot slot) throw() { m_Slot = slot; }

	// get/set sex
    Sex getSex()  { return m_BitSet.test(SLAYER_BIT_SEX)?MALE:FEMALE; }
    void setSex(Sex sex) throw() { m_BitSet.set(SLAYER_BIT_SEX,(sex==MALE?true:false)); }

	// get/set hair style
	HairStyle getHairStyle()  { return HairStyle((m_BitSet.to_ulong() >> 1) & 3); }
	void setHairStyle(HairStyle hairStyle) throw() { m_BitSet |= bitset<SLAYER_BIT_MAX>(hairStyle << 1); }

	// get/set race. by sigi. 2002.10.31
	//bool isSlayer()  { return ((m_BitSet.to_ulong() >> 3) & 1)==0; }
	//void setSlayer(bool bSlayer=true) throw() { m_BitSet |= bitset<SLAYER_BIT_MAX>((int)(bSlayer==false) << 3); }

	// get/set hair color
	Color_t getHairColor()  { return m_Colors[ SLAYER_COLOR_HAIR ]; }
	void setHairColor(Color_t hairColor) throw() { m_Colors[ SLAYER_COLOR_HAIR ] = hairColor; }

	// get/set skin color
	Color_t getSkinColor()  { return m_Colors[ SLAYER_COLOR_SKIN ]; }
	void setSkinColor(Color_t skinColor) throw() { m_Colors[ SLAYER_COLOR_SKIN ] = skinColor; }

	// get/set shirt color
	Color_t getShirtColor(ColorType colorType = MAIN_COLOR)  { return m_Colors[ SLAYER_COLOR_SHIRT +(uint)colorType ]; }
	void setShirtColor(Color_t shirtColor, ColorType colorType = MAIN_COLOR) throw() { m_Colors[ SLAYER_COLOR_SHIRT +(uint)colorType ] = shirtColor; }

	// get/set jeans color
	Color_t getJeansColor(ColorType colorType = MAIN_COLOR)  { return m_Colors[ SLAYER_COLOR_JEANS +(uint)colorType ]; }
	void setJeansColor(Color_t jeansColor, ColorType colorType = MAIN_COLOR) throw() { m_Colors[ SLAYER_COLOR_JEANS +(uint)colorType ] = jeansColor; }

	// get/set STR
	Attr_t getSTR()  { return m_STR; }
	void setSTR(Attr_t str) throw() { m_STR = str; }
	// get/set DEX
	Attr_t getDEX()  { return m_DEX; }
	void setDEX(Attr_t dex) throw() { m_DEX = dex; }
	// get/set INT
	Attr_t getINT()  { return m_INT; }
	void setINT(Attr_t inte) throw() { m_INT = inte; }

	// get/set Race
	Race_t getRace()  { return m_Race; }
	void setRace( Race_t race ) throw() { m_Race = race; }

	// get/set Domain
	Race_t getDomainType()  { return m_domaintype; }
	void setDomainType( Race_t domaintype ) throw() { m_domaintype = domaintype; }


private :

    // PC�� �̸�
    string m_Name;

	// ����
	Slot m_Slot;

	// �����̾� �÷��� 
	bitset<SLAYER_BIT_MAX> m_BitSet; 

	// �����̾� ���� ����
	Color_t m_Colors[SLAYER_COLOR_MAX ];

	// STR, DEX, INTE
	Attr_t m_STR;
	Attr_t m_DEX;
	Attr_t m_INT;

	// ����
	Race_t m_Race;
	Race_t m_domaintype;
};


//////////////////////////////////////////////////////////////////////
//
// class CLCreatePCFactory;
//
// Factory for CLCreatePC
//
//////////////////////////////////////////////////////////////////////

class CLCreatePCFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLCreatePC(); }

	// get packet name
	string getPacketName()  { return "CLCreatePC"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_CREATE_PC; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CLCreatePCPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() 
	{ 
		return szBYTE + 20 								// �̸�
			+ szSlot									// ����
			+ szBYTE									// �����̾� �÷���(3 bit)
			+ szAttr* 3
			+ szColor* CLCreatePC::SLAYER_COLOR_MAX 	// ���� ����
			+ szRace;									// ����
			+ szRace;									// ����
	}

};


//////////////////////////////////////////////////////////////////////
//
// class CLCreatePCHandler;
//
//////////////////////////////////////////////////////////////////////

class CLCreatePCHandler {

public:

	// execute packet's handler
	static void execute(CLCreatePC* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
