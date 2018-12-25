//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddressListVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADDRESS_LIST_VERIFY_H__
#define __GC_ADDRESS_LIST_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddressListVerify
//////////////////////////////////////////////////////////////////////////////

class GCAddressListVerify : public Packet 
{
public:
	enum VerifyCodes
	{
		ADDRESS_LIST_ADD_OK = 0,
		ADDRESS_LIST_DELETE_OK,
		ADDRESS_LIST_ADD_FAIL,
		ADDRESS_LIST_DELETE_FAIL,

		SMS_SEND_OK,
		SMS_SEND_FAIL,

		SMS_CHARGE_OK,

		ADDRESS_LIST_VERIFY_MAX
	};

	enum ErrorParameters
	{
		ADD_FAIL_MAX_NUM_EXCEEDED = 1,
		ADD_FAIL_INVALID_DATA,
		DELETE_FAIL_NO_SUCH_EID,

		SMS_SEND_FAIL_NOT_ENOUGH_CHARGE,
	};

	GCAddressListVerify() throw() { m_Code = ADDRESS_LIST_VERIFY_MAX; m_Parameter = 0;}
	virtual ~GCAddressListVerify() throw() {}

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t getPacketID()  { return PACKET_GC_ADDRESS_LIST_VERIFY; }
	PacketSize_t getPacketSize()  { return szBYTE + szDWORD; }
	string getPacketName()  { return "GCAddressListVerify"; }
	string toString() ;
	
public:
	BYTE getCode(void)  { return m_Code;}
	void setCode(BYTE code) throw() { m_Code = code;}

	DWORD getParameter(void)  { return m_Parameter; }
	void setParameter(uint parameter) throw() { m_Parameter = parameter; }

private: 
	BYTE m_Code;
	DWORD m_Parameter;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddressListVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddressListVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddressListVerify(); }
	string getPacketName()  { return "GCAddressListVerify"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADDRESS_LIST_VERIFY; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + szDWORD; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddressListVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCAddressListVerifyHandler 
{
public:
	static void execute( GCAddressListVerify* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
