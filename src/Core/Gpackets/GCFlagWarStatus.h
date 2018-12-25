//////////////////////////////////////////////////////////////////////////////
// Filename    : GCFlagWarStatus.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_FLAG_WAR_STATUS_H__
#define __GC_FLAG_WAR_STATUS_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCFlagWarStatus;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCFlagWarStatus : public Packet 
{
public:
	GCFlagWarStatus() throw();
	~GCFlagWarStatus() throw();
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_FLAG_WAR_STATUS; }
	PacketSize_t getPacketSize()  { return szWORD + szBYTE*3; }
	string getPacketName()  { return "GCFlagWarStatus"; }
	string toString() ;

public:
	WORD	getTimeRemain() const { return m_TimeRemain; }
	void	setTimeRemain( WORD remainTime ) { m_TimeRemain = remainTime; }

	BYTE	getFlagCount( Race_t race ) const { return m_FlagCount[(int)race]; }
	void	setFlagCount( Race_t race, BYTE count ) { m_FlagCount[(int)race] = count; }

private :
	WORD	m_TimeRemain;
	BYTE	m_FlagCount[3];
};


//////////////////////////////////////////////////////////////////////////////
// class GCFlagWarStatusFactory;
//////////////////////////////////////////////////////////////////////////////

class GCFlagWarStatusFactory : public PacketFactory 
{
public :
	GCFlagWarStatusFactory() throw() {}
	virtual ~GCFlagWarStatusFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCFlagWarStatus(); }
	string getPacketName()  { return "GCFlagWarStatus"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_FLAG_WAR_STATUS; }
	PacketSize_t getPacketMaxSize()  { return szWORD + szBYTE * 3; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCFlagWarStatusHandler;
//////////////////////////////////////////////////////////////////////////////

class GCFlagWarStatusHandler 
{
public:
	static void execute(GCFlagWarStatus* pGCFlagWarStatus, Player* pPlayer) throw(Error);

};

#endif
