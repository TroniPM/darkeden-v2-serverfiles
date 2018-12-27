////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPacketRequestIntervalValidationBody.h
//
////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PACKET_REQUEST_INTERVAL_VALIDATION_BODY__
#define __CBILLING_PACKET_REQUEST_INTERVAL_VALIDATION_BODY__

//include files
#include "Exception.h"
#include "CBillingInfo.h"

// forward declaration
class SocketInputStream;
class SocketOutputStream;

///////////////////////////////////////////////////
// class CBillingPacketRequestIntervalValidationBody
///////////////////////////////////////////////////
class CBillingPacketRequestIntervalValidationBody : public CBillingPacketRequestIntervalValidationBodyInfo
{
public:
	// constructor
	CBillingPacketRequestIntervalValidationBody();

public:
	void read( SocketInputStream& iStream ) ;
	void write( SocketOutputStream& oStream ) ;

	string toString() ;
};

#endif

