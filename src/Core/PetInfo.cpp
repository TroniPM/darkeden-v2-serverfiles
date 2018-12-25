#include "PetInfo.h"

PetInfo::PetInfo()
{
	m_PetType=PET_NONE;
	m_PetLevel=0;
	m_PetLevel=0;
	m_PetExp=0;
	m_PetHP=0;
	m_PetAttr=0;
	m_PetOption=0;
	m_PetVersionOption=0;
	m_IsSummonInfo = 0;

	m_CanCutHead = 0;
	m_CanAttack = 0;
	m_CanGamble = 0;

	m_MagicRemainSec = 0;
	m_ExpertPetChangerRemainSec = 0;
	m_EnchantSkillType = 0;
//#ifdef __GAME_SERVER__
	m_FeedTurn = 1;
	m_CurrentFeedTurn = 0;
//#endif
}

void PetInfo::read(SocketInputStream& iStream) throw(ProtocolException, Error)
{
	__BEGIN_TRY

	iStream.read( m_PetType );

	if ( m_PetType == PET_NONE ) return;

	iStream.read( m_PetCreatureType );
	iStream.read( m_PetLevel );
	iStream.read( m_PetExp );

	iStream.read( m_PetHP );
	iStream.read( m_PetAttr );
	iStream.read( m_PetAttrLevel );
	iStream.read( m_PetOption );
	iStream.read( m_PetFoodType );

	iStream.read( m_CanGamble );
	iStream.read( m_CanCutHead );
	iStream.read( m_CanAttack );

	iStream.read( m_IsSummonInfo );
	
	BYTE szSTR;
	iStream.read( szSTR );
	if ( szSTR != 0 ) iStream.read( m_Nickname, szSTR );

	iStream.read( m_MagicRemainSec );
	iStream.read( m_ExpertPetChangerRemainSec );
	iStream.read( m_EnchantSkillType );

	iStream.read( m_PetVersionOption );

	BYTE optionSize;
	iStream.read( optionSize );

	m_OptionType.clear();

	for ( int j=0; j < optionSize ; ++j )
	{
		OptionType_t optionType;
		iStream.read( optionType );
		m_OptionType.push_back( optionType );
	}

	BYTE mixOptionSize;
	iStream.read( mixOptionSize );

	m_MixOptionType.clear();

	for ( int k=0; k < mixOptionSize ; ++k )
	{
		OptionType_t mixOptionType;
		iStream.read( mixOptionType );
		m_MixOptionType.push_back( mixOptionType );
	}

	ObjectID_t ItemObjectID;
	iStream.read( ItemObjectID );

	__END_CATCH
}

void PetInfo::write(SocketOutputStream& oStream) 
{
	__BEGIN_TRY

	oStream.write( m_PetType );

	if ( m_PetType == PET_NONE ) return;

	oStream.write( m_PetCreatureType );
	oStream.write( m_PetLevel );
	oStream.write( m_PetExp );

	oStream.write( m_PetHP );
	oStream.write( m_PetAttr );
	oStream.write( m_PetAttrLevel );
	oStream.write( m_PetOption );
	oStream.write( m_PetFoodType );

	oStream.write( m_CanGamble );
	oStream.write( m_CanCutHead );
	oStream.write( m_CanAttack );

	oStream.write( m_IsSummonInfo );

	BYTE szSTR = m_Nickname.size();
	oStream.write( szSTR );
	if ( szSTR != 0 ) oStream.write( m_Nickname );

	oStream.write( m_MagicRemainSec );
	oStream.write( m_ExpertPetChangerRemainSec );
	oStream.write( m_EnchantSkillType );

	oStream.write( m_PetVersionOption );

	BYTE optionSize = m_OptionType.size();
	oStream.write( optionSize );
	std::list<OptionType_t>::const_iterator itr = m_OptionType.begin();
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
		oStream.write( optionType );
	}

	BYTE mixOptionSize = m_MixOptionType.size();
	oStream.write( mixOptionSize );
	std::list<OptionType_t>::const_iterator mixitr = m_MixOptionType.begin();
	for (; mixitr!=m_MixOptionType.end(); mixitr++)
	{
		OptionType_t mixOptionType = *mixitr;
		oStream.write( mixOptionType );
	}


	ObjectID_t ItemObjectID = getItemObjectID();
	oStream.write( ItemObjectID );

	__END_CATCH
}

string PetInfo::toString() const
{
	StringStream msg;
	
	msg << "PetInfo("
		<< "PetType : " << (int)m_PetType
		<< ", PetLevel : " << (int)m_PetLevel
		<< ", PetExp : " << (int)m_PetExp
		<< ", PetHP : " << (int)m_PetHP
		<< ", PetAttr : " << (int)m_PetAttr
		<< ", PetOption : " << (int)m_PetOption
		<< ", PetFoodType : " << (int)m_PetFoodType
		<< ")";

	return msg.toString();
}
