//--------------------------------------------------------------------------------
//
// Filename    : UCUpdateListHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "UCUpdateList.h"

#ifdef __UPDATE_CLIENT__
	#include <stdio.h>
	#include "Properties.h"
	#include "Upackets/CURequest.h"
	#include "Upackets/CUEndUpdate.h"
#endif

//--------------------------------------------------------------------------------
//
// (1) ������Ʈ �Ŵ����� �÷��̾� ��ü�� �����Ѵ�.
// (2) ���ҽ� �Ŵ����� ������Ʈ �Ŵ������� �����´�.
// (3) ���ҽ��� ���ҽ� �Ŵ������� �����´�.
// (4) ���ҽ��� �����ϸ�, ������ ��û�Ѵ�.
// (5) ���ҽ��� �������� ������ ������ �����Ѵ�.
//
//--------------------------------------------------------------------------------
void UCUpdateListHandler::execute ( UCUpdateList * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY
	__END_CATCH
}
