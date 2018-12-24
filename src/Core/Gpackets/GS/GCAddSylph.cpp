//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlyph.cpp
// Written By  : rappi76
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "GCAddSylph.h"


//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyph member methods
//////////////////////////////////////////////////////////////////////////////

void GCAddSylph::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );

	iStream.read( m_SylphType );

	switch(m_SylphType)
	{
		case 2:
			iStream.read( m_WingItemType );
			iStream.read( m_WingBodyColor );
			iStream.read( m_WingEffectColor );
			break;
		case 1:
		default :
			break;
	}

	__END_CATCH
}

void GCAddSylph::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );

	oStream.write( m_SylphType );

	switch(m_SylphType)
	{
		case 2 :
			oStream.write( m_WingItemType );
			oStream.write( m_WingBodyColor );
			oStream.write( m_WingEffectColor );
			break;
		case 1 :
		default :
			break;
	}

	__END_CATCH
}

PacketSize_t GCAddSylph::getPacketSize() const throw() 
{ 
	PacketSize_t PacketSize;

	PacketSize = szObjectID 
		+ sizeof(uchar);

	switch(m_SylphType)
	{
		case 2 :
			PacketSize += szColor + szColor;
			PacketSize += szItemType;
			break;
		case 1 :
		default :
			break;
	}

	return PacketSize;
}

void GCAddSylph::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddSylphHandler::execute( this , pPlayer );
		
	__END_CATCH
}
string GCAddSylph::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddSylph("
		<< "ObjectID:"   << m_ObjectID 
		<< ",SylphType: "  << (int)m_SylphType;

	switch(m_SylphType)
	{
		case 2 :
			msg 
				<< ",WingItemType: "  << (int)m_WingItemType
				<< ",WingBodyColor: "  << (int)m_WingBodyColor
				<< ",WingEffectColor: "  << (int)m_WingEffectColor
				<< ")" ;
			break;

		case 1 :
		default :
			break;
	}
	return msg.toString();

	__END_CATCH
}
PacketSize_t GCAddSylphFactory::getPacketMaxSize() const throw() 
{
	PacketSize_t MaxPacketSize;

	MaxPacketSize = szObjectID 
		+ sizeof(uchar);

	MaxPacketSize += 
		szItemType +
		szColor + szColor;

	return MaxPacketSize;
}
