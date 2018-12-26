//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddEffect.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_EFFECT_H__
#define __GC_ADD_EFFECT_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffect;
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//////////////////////////////////////////////////////////////////////////////

class GCAddEffect : public Packet 
{
public:
	GCAddEffect() ;
	~GCAddEffect() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_EFFECT; }
	PacketSize_t getPacketSize()  { return szObjectID + szEffectID + szTurn; }
	string getPacketName()  { return "GCAddEffect"; }
	string toString() ;

public:
	EffectID_t getEffectID()  { return m_EffectID; }
	void setEffectID(EffectID_t e) throw() { m_EffectID = e; }
	
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t o) throw() { m_ObjectID = o; }

	Turn_t getDuration()  { return m_Duration; }
	void setDuration(Turn_t d) throw() { m_Duration = d; }
	
private :
	ObjectID_t m_ObjectID;
	EffectID_t m_EffectID;
	Turn_t m_Duration;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectFactory : public PacketFactory 
{
public :
	GCAddEffectFactory() throw() {}
	virtual ~GCAddEffectFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCAddEffect(); }
	string getPacketName()  { return "GCAddEffect"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_EFFECT; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szEffectID + szTurn; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddEffectHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddEffectHandler 
{
public:
	static void execute(GCAddEffect* pGCAddEffect, Player* pPlayer);

};

#endif
