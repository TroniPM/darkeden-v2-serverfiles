//////////////////////////////////////////////////////////////////////////////
// Filename    : GCExecuteElement.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_EXECUTE_ELEMENT_H__
#define __GC_EXECUTE_ELEMENT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElement;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElement : public Packet 
{
public:
	GCExecuteElement() ;
	~GCExecuteElement() ;
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error) { iStream.read(m_QuestID); iStream.read(m_Condition); iStream.read(m_Index); }
    void write(SocketOutputStream & oStream)  { oStream.write(m_QuestID); oStream.write(m_Condition); oStream.write(m_Index); }
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_EXECUTE_ELEMENT; }
	PacketSize_t getPacketSize()  { return szDWORD + szBYTE + szWORD; }
	string getPacketName()  { return "GCExecuteElement"; }
	string toString() ;

public:
	DWORD	getQuestID() const { return m_QuestID; }
	void	setQuestID(DWORD id) { m_QuestID = id; }

	BYTE	getCondition() const { return m_Condition; }
	void	setCondition(BYTE cond) { m_Condition = cond; }

	WORD	getIndex() const { return m_Index; }
	void	setIndex(WORD idx) { m_Index = idx; }

private:
	DWORD	m_QuestID;
	BYTE	m_Condition;	// ��� ���ǿ� �ִ°� 0 : Happen, 1 : Complete, 2 : Fail, 3 : Reward
	WORD	m_Index;		// �ش� ������ ���° element�ΰ�
};


//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElementFactory;
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElementFactory : public PacketFactory 
{
public :
	GCExecuteElementFactory() throw() {}
	virtual ~GCExecuteElementFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCExecuteElement(); }
	string getPacketName()  { return "GCExecuteElement"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_EXECUTE_ELEMENT; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + szWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElementHandler;
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElementHandler 
{
public:
	static void execute(GCExecuteElement* pGCExecuteElement, Player* pPlayer);

};

#endif
