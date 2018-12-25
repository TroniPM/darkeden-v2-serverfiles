//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToItemVerify.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_ITEM_TO_ITEM_VERIFY_H__
#define __GC_ADD_ITEM_TO_ITEM_VERIFY_H__

#include "Packet.h"
#include "PacketFactory.h"

enum 
{
	ADD_ITEM_TO_ITEM_VERIFY_ERROR,					// error

	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE,		// enchant 완전 불가
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH,		// enchant 실패: 아이템 부서짐
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE,	// enchant 실패: 옵션 떨어짐
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK,				// enchant 성공
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_IMPOSSIBLE_NO_PREMIUM,	// enchant 불가 : 프리미엄 아님

	ADD_ITEM_TO_ITEM_VERIFY_TRANS_OK,
	ADD_ITEM_TO_ITEM_VERIFY_TRANS_IMPOSSIBLE,
	
	ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK,
	ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK,

	ADD_ITEM_TO_ITEM_VERIFY_MIXING_FAILED_SAME_OPTION_GROUP,	// 아이템의 옵션 그룹이 같아서 섞을 수 없습니다.
	ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL,				// enchant 실패

	ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK,					// 펫 부활 성공

	ADD_ITEM_TO_ITEM_VERIFY_CLEAR_OPTION_OK,			// option 제거 성공
	ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK,				// grade올리기 성공

	// add by Coffee 2006.11.3
	ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_FAIL,
	ADD_ITEM_TO_ITEM_VERIFY_THIRD_ENCHANT_OK,
	ADD_ITEM_TO_ITEM_VERIFY_CHANGE_ENCHANT_OK,

	ADD_ITEM_TO_ITEM_REMOVE_OPTION_OK,
	ADD_ITEM_TO_ITEM_VERIFY_SET_ENCHANT_FAIL_DECREASE,	// enchant 실패: 옵션 떨어짐
	ADD_ITEM_TO_ITEM_VERIFY_SET_ENCHANT_OK,				// enchant 성공

	ADD_ITEM_TO_ITEM_VERIFY_PET_MIXING_OK,
	ADD_ITEM_TO_ITEM_VERIFY_PET_MIXING_FAIL,

	ADD_ITEM_TO_ITEM_VERIFY_MAX
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerify
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerify : public Packet 
{

public:
	GCAddItemToItemVerify() throw() { m_Code = ADD_ITEM_TO_ITEM_VERIFY_MAX; m_Parameter = 0;}
	virtual ~GCAddItemToItemVerify() throw() {}

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	PacketID_t getPacketID()  { return PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCAddItemToItemVerify"; }
	string toString() ;
	
public:
	BYTE getCode(void)  { return m_Code;}
	void setCode(BYTE code) throw() { m_Code = code;}

	uint getParameter(void)  { return m_Parameter; }
	void setParameter(uint parameter) throw() { m_Parameter = parameter; }

	void setThirdOptionType(const list<OptionType_t>& optionType) throw() { m_ThirdOptionType = optionType; }
	std::list<OptionType_t>& getThirdOptionType() throw() { return m_ThirdOptionType; }

private: 
	BYTE m_Code;
	uint m_Parameter;
	list<OptionType_t> m_ThirdOptionType;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerifyFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerifyFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddItemToItemVerify(); }
	string getPacketName()  { return "GCAddItemToItemVerify"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_ITEM_TO_ITEM_VERIFY; }
	PacketSize_t getPacketMaxSize()  { return szBYTE + szuint + 255; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToItemVerifyHandler
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToItemVerifyHandler 
{
public:
	static void execute( GCAddItemToItemVerify* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
