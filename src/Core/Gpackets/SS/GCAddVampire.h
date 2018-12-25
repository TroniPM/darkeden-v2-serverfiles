//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddVampire.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_VAMPIRE_H__
#define __GC_ADD_VAMPIRE_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCVampireInfo3.h"
#include "EffectInfo.h"
#include "PetInfo.h"
#include "NicknameInfo.h"
#include "StoreInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampire;
//
// �α����̳� ��Ż, �ڷ���Ʈ ������ �����̾ ���� ���� ���� ���, �Ǵ�
// �����̾ ������ �̵��� ���,(1) �̹� �� �����̾ ���� ������ ���� �ִ�
//(�� �� �����̾ ���� �ִ�..) ������ �����ϴ� PC�鿡�Դ� GCMove ��Ŷ��
// ��ε�ĳ��Ʈ�Ѵ�. �׷���,(2) �� �����̾ ó�� ���� �Ǵ� ������ �����ϴ�
// PC�鿡�Դ� GCAddVampire ��Ŷ�� ��ε�ĳ��Ʈ�Ѵ�. ����,(3) �� �����̾��
// �ڽ��� ���� ��ô�� �þ�(?) �ȿ� �����ϴ� �����̾���� ������ GCAddVampire��
// ��Ƽ� �ް� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class GCAddVampire : public Packet 
{
public:
	GCAddVampire() throw() : m_pEffectInfo(NULL), m_pPetInfo(NULL), m_pNicknameInfo(NULL) { m_FromFlag = 0; }
	GCAddVampire(const PCVampireInfo3 & vampireInfo) throw() : m_VampireInfo(vampireInfo), m_pEffectInfo(NULL), m_pPetInfo(NULL), m_pNicknameInfo(NULL) { m_FromFlag = 0; }
	virtual ~GCAddVampire() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_ADD_VAMPIRE; }
	PacketSize_t getPacketSize() 
	{
		PacketSize_t ret = m_VampireInfo.getSize() + m_pEffectInfo->getSize() + ((m_pPetInfo!=NULL)?m_pPetInfo->getSize():szPetType) + szBYTE;

		if ( m_pNicknameInfo == NULL )
		{
			NicknameInfo noNick;
			noNick.setNicknameType( NicknameInfo::NICK_NONE );
			ret += noNick.getSize();
		}
		else
		{
			ret += m_pNicknameInfo->getSize();
		}

		ret += m_StoreOutlook.getSize();

		return ret;
	}
	string getPacketName()  { return "GCAddVampire"; }
	string toString() ;

public:
	PCVampireInfo3 & getVampireInfo() throw() { return m_VampireInfo; }
	const PCVampireInfo3 & getVampireInfo()  { return m_VampireInfo; }
	void setVampireInfo(const PCVampireInfo3 & vampireInfo) throw() { m_VampireInfo = vampireInfo; }

	EffectInfo* getEffectInfo()  { return m_pEffectInfo; }
	void setEffectInfo(EffectInfo* pEffectInfo) throw() { m_pEffectInfo = pEffectInfo; }

	PetInfo* getPetInfo()  { return m_pPetInfo; }
	void setPetInfo(PetInfo* pPetInfo) throw() { m_pPetInfo = pPetInfo; }

	NicknameInfo* getNicknameInfo()  { return m_pNicknameInfo; }
	void setNicknameInfo(NicknameInfo* pNicknameInfo) throw() { m_pNicknameInfo = pNicknameInfo; }

	StoreOutlook	getStoreOutlook() const { return m_StoreOutlook; }
	void		setStoreInfo(StoreInfo* pInfo) { pInfo->makeStoreOutlook(m_StoreOutlook); }

	BYTE getFromFlag(void) const { return m_FromFlag; }
	void setFromFlag(BYTE flag) { m_FromFlag = flag; }

private:
	PCVampireInfo3 m_VampireInfo; // �����̾� �ܸ� ����
	EffectInfo*    m_pEffectInfo; // ����Ʈ ����
	PetInfo*	   m_pPetInfo;	  // �� ����
	NicknameInfo*	   m_pNicknameInfo;	  // �� ����
	StoreOutlook		m_StoreOutlook;	// ���λ��� ����
	BYTE           m_FromFlag;    // ���κ����ΰ�? ������ ��쿡�� 0, ��Ż�� ������ ��쿡�� 1
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddVampireFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampireFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddVampire(); }
	string getPacketName()  { return "GCAddVampire"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_VAMPIRE; }
	PacketSize_t getPacketMaxSize()  { return PCVampireInfo3::getMaxSize() + EffectInfo::getMaxSize() + PetInfo::getMaxSize() + NicknameInfo::getMaxSize() + StoreOutlook::getMaxSize() + szBYTE; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddVampireHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampireHandler 
{
public:
	static void execute(GCAddVampire* pPacket, Player* pPlayer) throw(Error);

};

#endif
