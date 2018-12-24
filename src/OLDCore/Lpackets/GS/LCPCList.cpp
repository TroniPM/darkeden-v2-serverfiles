//----------------------------------------------------------------------
// 
// Filename    : LCPCList.cpp 
// Written By  : Reiot
// Description :
// 
//----------------------------------------------------------------------

// include files
#include "LCPCList.h"
#include "PCSlayerInfo.h"
#include "PCVampireInfo.h"
#include "PCOustersInfo.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
LCPCList::LCPCList ()
	throw ()
{
	for ( uint i = 0 ; i < SLOT_MAX ; i ++ )
		m_pPCInfos[i] = NULL;
}


//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
LCPCList::~LCPCList ()
	throw ()
{
	// heap �� ������ PC Type �������� �����ؾ� �Ѵ�.
	for ( uint i = 0 ; i < SLOT_MAX ; i ++ ) 
	{
		SAFE_DELETE(m_pPCInfos[i]);
	}
}


//----------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//----------------------------------------------------------------------
void LCPCList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// PC Ÿ�� ������ �޾ƿ´�.
	//
	// *OPTMIZATION*
	//
	// ���߿��� �� ������ 1 ����Ʈ�� �־ ��Ʈ ������ �ϵ��� �Ѵ�.
	//
	//--------------------------------------------------
	char pcTypes[SLOT_MAX];

	for ( uint i = 0 ; i < SLOT_MAX ; i ++ )
		iStream.read(pcTypes[i]);

	//--------------------------------------------------
	// PC ���� ��ü�� �д´�.
	//--------------------------------------------------
	for ( uint j = 0 ; j < SLOT_MAX ; j ++ ) {

		switch ( pcTypes[j] ) {

			case 'S' :
				{
					PCSlayerInfo * pPCSlayerInfo = new PCSlayerInfo();	
					pPCSlayerInfo->read( iStream );
					m_pPCInfos[ pPCSlayerInfo->getSlot() ] = pPCSlayerInfo;
				}
				break;

			case 'V' :
				{
					PCVampireInfo * pPCVampireInfo = new PCVampireInfo();	
					pPCVampireInfo->read( iStream );
					m_pPCInfos[ pPCVampireInfo->getSlot() ] = pPCVampireInfo;
				}
				break;

			case 'O' :
				{
					PCOustersInfo * pPCOustersInfo = new PCOustersInfo();	
					pPCOustersInfo->read( iStream );
					m_pPCInfos[ pPCOustersInfo->getSlot() ] = pPCOustersInfo;
				}
				break;

			case '0' :
				break;

			default :
				throw InvalidProtocolException("invalid pc type");
		}

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void LCPCList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// �ϴ� PC Ÿ���� ����. 
	//
	// ���߿��� �� ������ 1 ����Ʈ�� �־ ��Ʈ ������ �ϵ��� �Ѵ�.
	//
	// ex>
	// 	S0V : Slayer-EMPTY-VAMPIRE
	// 	00S : EMPTY-EMPTY-SLAYER
	//
	//--------------------------------------------------
	for ( uint i = 0 ; i < SLOT_MAX ; i ++ ) {

		if ( m_pPCInfos[i] ) {	// m_pPCInfos[i] != NULL

			if ( m_pPCInfos[i]->getPCType() == PC_SLAYER ) {
				oStream.write( 'S' );
			} else if ( m_pPCInfos[i]->getPCType() == PC_VAMPIRE ) {	// case of PC_VAMPIRE
				oStream.write( 'V' );
			} else {
				oStream.write( 'O' );
			}

		} else {				// m_pPCInfos[i] == NULL
			oStream.write( '0' );
		}
	}

	//--------------------------------------------------
	// �״��� PCType ��ü ��ü�� ����.
	//--------------------------------------------------
	for ( uint j = 0 ; j < SLOT_MAX ; j ++ ) {
		if ( m_pPCInfos[j] != NULL ) {
			m_pPCInfos[j]->write( oStream );
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void LCPCList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	LCPCListHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
PacketSize_t LCPCList::getPacketSize () const 
	throw ()
{
	PacketSize_t packetSize = 0;
	for ( uint i = 0 ; i < SLOT_MAX ; i ++ ) {
		if ( m_pPCInfos[i] ) { // m_pPCInfos[i] != NULL
			packetSize += m_pPCInfos[i]->getSize();
		}
	}
	return packetSize;
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string LCPCList::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "LCPCList(\n";

	for ( uint i = 0 ; i < SLOT_MAX ; i ++ )
		if ( m_pPCInfos[i] != NULL )
			msg << m_pPCInfos[i]->toString() << "\n";
		else
			msg << "EMPTY SLOT\n";

	msg << ")";

	return msg.toString();

	__END_CATCH
}


