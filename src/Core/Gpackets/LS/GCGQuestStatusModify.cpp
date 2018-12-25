//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGQuestStatusModify.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCGQuestStatusModify.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCGQuestStatusModify::GCGQuestStatusModify () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCGQuestStatusModify::~GCGQuestStatusModify () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCGQuestStatusModify::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCGQuestStatusModifyHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCGQuestStatusModify::toString () 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCGQuestStatusModify("
		<< ")";
	return msg.toString();

	__END_CATCH
}

