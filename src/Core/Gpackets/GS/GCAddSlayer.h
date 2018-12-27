//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlayer.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_SLAYER_H__
#define __GC_ADD_SLAYER_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayer;
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ� 
// �����̾ ������ �̵��� ���,(1) �̹� �� �����̾ ���� ������ ���� �ִ� 
//(�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ�� 
// ��ε�ĳ��Ʈ�Ѵ�. �׷���,(2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ� 
// PC�鿡�Դ� GCAddSlayer ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����,(3) �� �����̾�� 
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddSlayer�� 
// ��Ƽ� �ް� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayer : public Packet 
{
public:
	GCAddSlayer();
	GCAddSlayer(const PCSlayerInfo3 & slayerInfo);
	virtual ~GCAddSlayer() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_GC_ADD_SLAYER; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCAddSlayer"; }
	string toString() ;

public:
	PCSlayerInfo3 & getSlayerInfo()  { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo()  { return m_SlayerInfo; }
	void setSlayerInfo(const PCSlayerInfo3 & slayerInfo)  { m_SlayerInfo = slayerInfo; }

	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo)  { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo()  { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo)  { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo()  { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo)  { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

private:
	PCSlayerInfo3  m_SlayerInfo;  // �����̾��� �ܸ� ����
	EffectInfo*    m_pEffectInfo; // �ɷ��ִ� ����Ʈ ����
	PetInfo*	   m_pPetInfo;	  // �� ���� ����
	NicknameInfo*	   m_pNicknameInfo;	  // �� ���� ����
	StoreOutlook		m_StoreOutlook;	// ���λ��� ���� ����
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayerFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayerFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCAddSlayer(); }
	string getPacketName()  { return "GCAddSlayer"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_SLAYER; }
	PacketSize_t getPacketMaxSize() 
	{ 
		return PCSlayerInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize();
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlayerHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddSlayerHandler 
{
public:
	static void execute(GCAddSlayer* pPacket, Player* pPlayer);
};

#endif
