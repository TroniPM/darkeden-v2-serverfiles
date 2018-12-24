/////////////////////////////////////////////////////////////////////////////
// Filename : PKTLogoutHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_LOGOUT_HANDLER_H__
#define __PKT_LOGOUT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTLogoutHandler
class PKTLogoutHandler : public MPacketHandler
{
public:
	// �ش� ��Ŷ�� ID
	MPacketID_t getID() const;

	// ���� �Լ�
	void execute( GameServerPlayer* pPlayer, MPacket* pPacket );
};

#endif

