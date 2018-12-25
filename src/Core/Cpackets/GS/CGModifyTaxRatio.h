//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyTaxRatio.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_TAX_RATIO_H__
#define __CG_MODIFY_TAX_RATIO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyTaxRatio;
//
//////////////////////////////////////////////////////////////////////

class CGModifyTaxRatio : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_MODIFY_TAX_RATIO; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szuint; }

	// get packet name
	string getPacketName()  { return "CGModifyTaxRatio"; }

	// get packet's debug string
	string toString() ;

	// get/set Ratio
	uint getRatio() const { return m_Ratio; }
	void setRatio( uint ratio ) { m_Ratio = ratio; }


private :

	uint m_Ratio;
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyTaxRatioFactory;
//
// Factory for CGModifyTaxRatio
//
//////////////////////////////////////////////////////////////////////

class CGModifyTaxRatioFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyTaxRatioFactory() throw() {}
	
	// destructor
	virtual ~CGModifyTaxRatioFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGModifyTaxRatio(); }

	// get packet name
	string getPacketName()  { return "CGModifyTaxRatio"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MODIFY_TAX_RATIO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szuint; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyTaxRatioHandler;
//
//////////////////////////////////////////////////////////////////////

class CGModifyTaxRatioHandler {

public:

	// execute packet's handler
	static void execute(CGModifyTaxRatio* pCGModifyTaxRatio, Player* pPlayer) throw(Error);

};

#endif
