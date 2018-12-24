/////////////////////////////////////////////////////////////////////////////
// Filename : PKTConnectAcceptHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_CONNECT_ACCEPT_HANDLER_H__
#define __PKT_CONNECT_ACCEPT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTConnectAcceptHandler
class PKTConnectAcceptHandler : public MPacketHandler
{
public:
	// �ش� ��Ŷ�� ID
	MPacketID_t getID() const;

	// ���� �Լ�
	void execute( MPlayer* pPlayer, MPacket* pPacket );
};

#endif

