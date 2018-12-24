/////////////////////////////////////////////////////////////////////////////
// Filename : PKTUserInfoHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_USERINFO_HANDLER_H__
#define __PKT_USERINFO_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTUserInfoHandler
class PKTUserInfoHandler : public MPacketHandler
{
public:
	// �ش� ��Ŷ�� ID
	MPacketID_t getID() const;

	// ���� �Լ�
	void execute( GameServerPlayer* pPlayer, MPacket* pPacket );
};

#endif

