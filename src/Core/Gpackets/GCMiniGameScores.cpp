//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMiniGameScores.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCMiniGameScores.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCMiniGameScores::GCMiniGameScores () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCMiniGameScores::~GCMiniGameScores () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCMiniGameScores::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_GameType);
	iStream.read(m_Level);

	BYTE count;
	iStream.read(count);

	for ( BYTE i=0; i<count; ++i )
	{
		BYTE len;
		iStream.read(len);
		string name;
		iStream.read(name, len);
		WORD score;
		iStream.read(score);

		addScore(name,score);
	}
		
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCMiniGameScores::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_GameType);
	oStream.write(m_Level);

	BYTE count = m_Scores.size();
	if ( count > 10 ) count = 10;
	oStream.write( count );

	list<pair<string,WORD> >::const_iterator itr = m_Scores.begin();

	for ( uint i=0; i<count; ++i )
	{
		oStream.write( (BYTE)(*itr).first.size() );
		oStream.write( (*itr).first );
		oStream.write( (*itr).second );
		itr++;
	}
		
	__END_CATCH
}

PacketSize_t GCMiniGameScores::getPacketSize() 
{
	PacketSize_t ret = szBYTE + szBYTE + szBYTE;

	BYTE count = m_Scores.size();
	if ( count > 10 ) count = 10;

	list<pair<string,WORD> >::const_iterator itr = m_Scores.begin();

	for ( uint i=0; i<count; ++i )
	{
		ret += szBYTE + (*itr).first.size() + szWORD;
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCMiniGameScores::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMiniGameScoresHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCMiniGameScores::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCMiniGameScores("
		<< ")";
	return msg.toString();

	__END_CATCH
}

