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
	virtual ~GCAddSlayer() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_SLAYER; }
	PacketSize_t getPacketSize() const throw();
	string getPacketName() const throw() { return "GCAddSlayer"; }
	string toString() const throw();

public:
	PCSlayerInfo3 & getSlayerInfo() throw() { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo() const throw() { return m_SlayerInfo; }
	void setSlayerInfo(const PCSlayerInfo3 & slayerInfo) throw() { m_SlayerInfo = slayerInfo; }

	EffectInfo* getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo() const throw() { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) throw() { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo() const throw() { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw() { m_pNicknameInfo = pNicknameInfo; }

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
	Packet* createPacket() throw() { return new GCAddSlayer(); }
	string getPacketName() const throw() { return "GCAddSlayer"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_SLAYER; }
	PacketSize_t getPacketMaxSize() const throw()
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
	static void execute(GCAddSlayer* pPacket, Player* pPlayer) throw(Error);
};

#endif
