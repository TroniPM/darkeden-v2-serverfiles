/////////////////////////////////////////////////////////////////////////////
// Filename	: MPacketManager.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_MANAGER_H__
#define __MPACKET_MANAGER_H__

// include files
#include "MPacket.h"

// forward declaration
class MPlayer;
class MPacketHandler;


// class MPacketManager
class MPacketManager
{
public:
	MPacketManager();
	~MPacketManager();

public:
	void init();

public:
	// ��Ŷ �����ڸ� �߰��Ѵ�.
	void addCreator( MPacket* pPacket );

	// ��Ŷ �ڵ鷯�� �߰��Ѵ�.
	void addHandler( MPacketHandler* pHandler );

public:
	// ���ο� ��Ŷ�� �����ؼ� ��ȯ�Ѵ�.
	MPacket* createPacket( MPacketID_t ID ) const;

	// ��Ŷ�� �ڵ鷯�� �����Ѵ�.
	void execute( MPlayer* pPlayer, MPacket* pPacket );

	// ��Ŷ�� �ڵ鷯�� �ִ��� Ȯ���Ѵ�.
	bool hasHandler( MPacketID_t ID ) const;

	// ��Ŷ�� ũ�⸦ ��ȯ�Ѵ�.
	MPacketSize_t getPacketSize( MPacketID_t ID ) const;

private:
	// ���� ���� ������
	struct IMPL;
	IMPL* m_pImpl;
};


// global variable
extern MPacketManager* g_pMPacketManager;

#endif

