// 
// Filename    : SweeperBonusInfo.cpp 
// Written By  :
// Description :
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "SweeperBonusInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SweeperBonusInfo::SweeperBonusInfo () 
     throw ()
{
	__BEGIN_TRY
	
	m_Type = 0;
	m_Race = 0;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SweeperBonusInfo::~SweeperBonusInfo () 
    throw ()
{
	__BEGIN_TRY

	clearOptionTypeList();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void SweeperBonusInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
//	BYTE szOptionList;

//	iStream.read( m_Type );
	iStream.read( m_Race );

/*	iStream.read( szOptionList );
	for ( int i = 0 ; i < szOptionList; i++ )
	{
		OptionType_t optionType;
		iStream.read( optionType );
		m_OptionTypeList.push_back( optionType );
	}
*/
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void SweeperBonusInfo::write ( SocketOutputStream & oStream ) 
     
{
	__BEGIN_TRY
	
//	oStream.write( m_Type );
	oStream.write( m_Race );

/*	BYTE szOptionList = m_OptionTypeList.size();
	oStream.write( szOptionList );

	OptionTypeListConstItor itr = m_OptionTypeList.begin();
	for ( ; itr != m_OptionTypeList.end(); itr++ )
	{
		OptionType_t optionType = *itr;
		oStream.write( optionType );
	}
*/		
	__END_CATCH
}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string SweeperBonusInfo::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "SweeperBonusInfo( "
//		<< "Type:" << (int)m_Type
		<< "Race:" << (int)m_Race
//		<< "OptionTypeListSize:" << (int)m_OptionTypeList.size()
		<< ")";

	return msg.toString();

	__END_CATCH
}

