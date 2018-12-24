/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAskHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ASK_HANDLER_H__
#define __PKT_CONNECT_ASK_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTConnectAskHandler
class PKTConnectAskHandler : public MPacketHandler
{
public:
	// �ش� ��Ŷ�� ID
	MPacketID_t getID() const;

	// ���� �Լ�
	void execute( GameServerPlayer* pPlayer, MPacket* pPacket );
};

#endif

