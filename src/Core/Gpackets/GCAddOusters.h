//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddOusters.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_OUSTERS_H__
#define __GC_ADD_OUSTERS_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCOustersInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddOusters;
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ� 
// �����̾ ������ �̵��� ���,(1) �̹� �� �����̾ ���� ������ ���� �ִ� 
//(�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ�� 
// ��ε�ĳ��Ʈ�Ѵ�. �׷���,(2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ� 
// PC�鿡�Դ� GCAddOusters ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����,(3) �� �����̾�� 
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddOusters�� 
// ��Ƽ� �ް� �ȴ�.
// ��~~
//////////////////////////////////////////////////////////////////////////////

class GCAddOusters : public Packet 
{
public:
	GCAddOusters();
	GCAddOusters(const PCOustersInfo3 & slayerInfo);
	virtual ~GCAddOusters() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_OUSTERS; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCAddOusters"; }
	string toString() ;

public:
	PCOustersInfo3 & getOustersInfo() throw() { return m_OustersInfo; }
	const PCOustersInfo3 & getOustersInfo()  { return m_OustersInfo; }
	void setOustersInfo(const PCOustersInfo3 & slayerInfo) throw() { m_OustersInfo = slayerInfo; }

	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo()  { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) throw() { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo()  { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw() { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

private:
	PCOustersInfo3  m_OustersInfo;  // �����̾��� �ܸ� ����
	EffectInfo*    m_pEffectInfo; // �ɷ��ִ� ����Ʈ ����
	PetInfo*    m_pPetInfo; // �ɷ��ִ� ����Ʈ ����
	NicknameInfo*	m_pNicknameInfo;
	StoreOutlook	m_StoreOutlook;
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddOustersFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddOustersFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddOusters(); }
	string getPacketName()  { return "GCAddOusters"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_OUSTERS; }
	PacketSize_t getPacketMaxSize() 
	{ 
		return PCOustersInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddOustersHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddOustersHandler 
{
public:
	static void execute(GCAddOusters* pPacket, Player* pPlayer);
};

#endif
