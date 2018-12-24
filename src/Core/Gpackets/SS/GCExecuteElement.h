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
	GCExecuteElement() throw();
	~GCExecuteElement() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error) { iStream.read(m_QuestID); iStream.read(m_Condition); iStream.read(m_Index); }
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error) { oStream.write(m_QuestID); oStream.write(m_Condition); oStream.write(m_Index); }
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_EXECUTE_ELEMENT; }
	PacketSize_t getPacketSize() const throw() { return szDWORD + szBYTE + szWORD; }
	string getPacketName() const throw() { return "GCExecuteElement"; }
	string toString() const throw();

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
	string getPacketName() const throw() { return "GCExecuteElement"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_EXECUTE_ELEMENT; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + szWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCExecuteElementHandler;
//////////////////////////////////////////////////////////////////////////////

class GCExecuteElementHandler 
{
public:
	static void execute(GCExecuteElement* pGCExecuteElement, Player* pPlayer) throw(Error);

};

#endif
