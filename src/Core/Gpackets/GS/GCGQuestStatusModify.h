//////////////////////////////////////////////////////////////////////////////
// Filename    : GCGQuestStatusModify.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_GQUEST_STATUS_MODIFY_H__
#define __GC_GQUEST_STATUS_MODIFY_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "QuestStatusInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusModify;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusModify : public Packet 
{
public:
	enum ModifyType
	{
		NO_MODIFY,		// ���°� �ٲ��� �ʾ���
		CURRENT,		// ����Ʈ�� ���۵Ǿ���
		SUCCESS,		// ����Ʈ�� ��������
		FAIL,			// ����Ʈ�� ��������
	};

	GCGQuestStatusModify() throw();
	~GCGQuestStatusModify() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error) { iStream.read(m_Type); m_pInfo = new QuestStatusInfo(0); m_pInfo->read(iStream); }
    void write(SocketOutputStream & oStream)  { oStream.write(m_Type); m_pInfo->write(oStream); }
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_GQUEST_STATUS_MODIFY; }
	PacketSize_t getPacketSize()  { return szBYTE + m_pInfo->getSize(); }
	string getPacketName()  { return "GCGQuestStatusModify"; }
	string toString() ;

public:
	BYTE	getType() const { return m_Type; }
	void	setType(BYTE type) { m_Type = type; }

	QuestStatusInfo* getInfo() const { return m_pInfo; }
	void setInfo(QuestStatusInfo* pInfo) { m_pInfo = pInfo; }

private:
	BYTE				m_Type;
	QuestStatusInfo*	m_pInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusModifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusModifyFactory : public PacketFactory 
{
public :
	GCGQuestStatusModifyFactory() throw() {}
	virtual ~GCGQuestStatusModifyFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCGQuestStatusModify(); }
	string getPacketName()  { return "GCGQuestStatusModify"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_GQUEST_STATUS_MODIFY; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + QuestStatusInfo::getMaxSize(); }
};

//////////////////////////////////////////////////////////////////////////////
// class GCGQuestStatusModifyHandler;
//////////////////////////////////////////////////////////////////////////////

class GCGQuestStatusModifyHandler 
{
public:
	static void execute(GCGQuestStatusModify* pGCGQuestStatusModify, Player* pPlayer) throw(Error);

};

#endif
