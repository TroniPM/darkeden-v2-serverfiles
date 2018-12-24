/////////////////////////////////////////////////////////////////////////////
// Filename : PKTPowerPointHandler.h
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

#ifndef __PKT_POWER_POINT_HANDLER_H__
#define __PKT_POWER_POINT_HANDLER_H__

// include files
#include "MPacketHandler.h"

// class PKTPowerPointHandler
class PKTPowerPointHandler : public MPacketHandler
{
public:
	// �ش� ��Ŷ�� ID
	MPacketID_t getID() const;

	// ���� �Լ�
	void execute( MPlayer* pPlayer, MPacket* pPacket );
};

#endif

