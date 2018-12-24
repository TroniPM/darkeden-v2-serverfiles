//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddNickname.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_NICKNAME_H__
#define __GC_ADD_NICKNAME_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "NicknameInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddNickname;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCAddNickname : public Packet 
{
public:
	GCAddNickname() throw();
	~GCAddNickname() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_NICKNAME; }
	PacketSize_t getPacketSize() const throw() { return m_NicknameInfo.getSize(); }
	string getPacketName() const throw() { return "GCAddNickname"; }
	string toString() const throw();

public:
	NicknameInfo&	getNicknameInfo() { return m_NicknameInfo; }

private :
	NicknameInfo	m_NicknameInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddNicknameFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddNicknameFactory : public PacketFactory 
{
public :
	GCAddNicknameFactory() throw() {}
	virtual ~GCAddNicknameFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCAddNickname(); }
	string getPacketName() const throw() { return "GCAddNickname"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_NICKNAME; }
	PacketSize_t getPacketMaxSize() const throw() { return NicknameInfo::getMaxSize(); }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddNicknameHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddNicknameHandler 
{
public:
	static void execute(GCAddNickname* pGCAddNickname, Player* pPlayer) throw(Error);

};

#endif
