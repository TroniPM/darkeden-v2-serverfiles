//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRemoveEffect.h 
// Written By  : crazydog
// Description : Effect ����.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __REMOVE_EFFECT_H__
#define __REMOVE_EFFECT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveEffect;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ������ �����͸� �˷��ֱ� ���� ��ä
// RemoveEffectrmation, SkillToObjectOK � �Ƿ��� ���ư���.
//
//////////////////////////////////////////////////////////////////////

class GCRemoveEffect : public Packet
{

public :
	
	// constructor
	GCRemoveEffect() throw();
	
	// destructor
	~GCRemoveEffect() throw();
	
public :
    PacketID_t getPacketID() const throw() { return PACKET_GC_REMOVE_EFFECT; }
    string getPacketName() const throw() { return "GCRemoveEffect"; }
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE + szEffectID* m_ListNum; }
	static PacketSize_t getPacketMaxSize() throw() { return 255;}

	// get packet's debug string
	string toString() const throw();

	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum(BYTE ListNum) throw() { m_ListNum = ListNum; }

	// get&set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID;}
	void setObjectID(ObjectID_t id) throw() { m_ObjectID = id;}

	// add / delete / clear S List
	void addEffectList(EffectID_t id) throw(); 

	// ClearList
	void clearList() throw() { m_EffectList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	WORD popFrontListElement() throw() { EffectID_t effectID = m_EffectList.front(); m_EffectList.pop_front(); return effectID; }

protected :
	
	ObjectID_t m_ObjectID;
	// StatusList Element Number
	BYTE m_ListNum;

	// Status List
	list<EffectID_t> m_EffectList;

};

//////////////////////////////////////////////////////////////////////
//
// class GCRemoveEffectFactory;
//
// Factory for GCRemoveEffect
//
//////////////////////////////////////////////////////////////////////

class GCRemoveEffectFactory : public PacketFactory {

public :
	
	// constructor
	GCRemoveEffectFactory() throw() {}
	
	// destructor
	virtual ~GCRemoveEffectFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRemoveEffect(); }

	// get packet name
	string getPacketName() const throw() { return "GCRemoveEffect"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_REMOVE_EFFECT; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return 255;}

};


//////////////////////////////////////////////////////////////////////
//
// class GCRemoveEffectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRemoveEffectHandler {

public :

	// execute packet's handler
	static void execute(GCRemoveEffect* pGCRemoveEffect, Player* pPlayer) throw(Error);

};


#endif
