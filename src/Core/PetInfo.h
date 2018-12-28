#ifndef __PET_INFO_H__
#define __PET_INFO_H__

#include "Types.h"
#include "types/PetTypes.h"
#include "Exception.h"

#include "Packet.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#include "VSDateTime.h"
#include <algorithm>

class PetItem;

class PetInfo
{
public:
    PetInfo();
    virtual ~PetInfo() { }

    virtual void read(SocketInputStream &iStream) ;
    virtual void write(SocketOutputStream &oStream) ;

    virtual PacketSize_t getSize() const
    {
        if ( m_PetType == PET_NONE ) return szPetType;

        //		if ( type == MY_INFO )
        return szPetType + szMonsterType + szPetLevel + szPetExp + szPetHP + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szBYTE + szBYTE + szBYTE + szBYTE + szObjectID + szBYTE + m_Nickname.size() + szint + szint + szCEffectID + szOptionType + szBYTE + m_OptionType.size() * szOptionType + szBYTE + m_MixOptionType.size() * szOptionType;
        //		else
        //			return szPetType + szMonsterType + szPetLevel + szPetExp + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szObjectID;
    }
    static PacketSize_t getMaxSize()
    {
        //		if ( type == MY_INFO )
        return szPetType + szMonsterType + szPetLevel + szPetExp + szPetHP + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szBYTE + szBYTE + szBYTE + szBYTE + szObjectID + szBYTE + 22 + szint + szint + szCEffectID + szOptionType + szBYTE + 10 * szOptionType + szBYTE + 10 * szOptionType;
        //		else
        //			return szPetType + szMonsterType + szPetLevel + szPetExp + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szObjectID;
    }

public:
    void		setPetType(PetType_t PetType)
    {
        m_PetType = PetType;
    }
    PetType_t	getPetType() const
    {
        return m_PetType;
    }

    void			setPetCreatureType(MonsterType_t CreatureType)
    {
        m_PetCreatureType = CreatureType;
    }
    MonsterType_t	getPetCreatureType() const
    {
        return m_PetCreatureType;
    }

    void		setPetLevel(PetLevel_t PetLevel)
    {
        m_PetLevel = PetLevel;
    }
    PetLevel_t	getPetLevel() const
    {
        return m_PetLevel;
    }

    void		setPetExp(PetExp_t PetExp)
    {
        m_PetExp = PetExp;
    }
    PetExp_t	getPetExp() const
    {
        return m_PetExp;
    }

    void		setPetHP(PetHP_t PetHP)
    {
        m_PetHP = PetHP;
    }
    PetHP_t		getPetHP() const
    {
        return m_PetHP;
    }

    void		setPetAttr(PetAttr_t PetAttr)
    {
        m_PetAttr = PetAttr;
    }
    PetAttr_t	getPetAttr() const
    {
        return m_PetAttr;
    }

    void		setPetAttrLevel(PetAttrLevel_t PetAttrLevel)
    {
        m_PetAttrLevel = PetAttrLevel;
    }
    PetAttrLevel_t	getPetAttrLevel() const
    {
        return m_PetAttrLevel;
    }

    void			setPetOption(OptionType_t PetOption)
    {
        m_PetOption = PetOption;
    }
    OptionType_t	getPetOption() const
    {
        return m_PetOption;
    }

    void		setFoodType(ItemType_t FoodType)
    {
        m_PetFoodType = FoodType;
    }
    ItemType_t	getFoodType() const
    {
        return m_PetFoodType;
    }

    BYTE		canGamble() const
    {
        return m_CanGamble;
    }
    void		setGamble(BYTE bGamble)
    {
        m_CanGamble = bGamble;
    }

    BYTE		canCutHead() const
    {
        return m_CanCutHead;
    }
    void		setCutHead(BYTE bCutHead)
    {
        m_CanCutHead = bCutHead;
    }

    BYTE		canAttack() const
    {
        return m_CanAttack;
    }
    void		setAttack(BYTE bAttack)
    {
        m_CanAttack = bAttack;
    }

    void		setPetItem(PetItem *pPetItem)
    {
        m_pPetItem = pPetItem;
    }
    PetItem	*getPetItem() const
    {
        return m_pPetItem;
    }

    BYTE		isSummonInfo() const
    {
        return m_IsSummonInfo;
    }
    void		setSummonInfo( BYTE isSummon )
    {
        m_IsSummonInfo = isSummon;
    }

    // -_- 게임서버쪽에 정의해야쥐 PetItem.cpp 에 있음
    ObjectID_t	getItemObjectID() const;

    VSDateTime	&getLastFeedTime()
    {
        return m_LastFeedTime;
    }
    void		setFeedTime(const VSDateTime &time)
    {
        m_LastFeedTime = time;
    }

    //#ifdef __GAME_SERVER__
    BYTE		getFeedTurn() const
    {
        return m_FeedTurn;
    }
    void		setFeedTurn(BYTE turn)
    {
        m_FeedTurn = turn;
    }

    BYTE		getCurrentFeedTurn() const
    {
        return m_CurrentFeedTurn;
    }
    void		setCurrentFeedTurn(BYTE turn)
    {
        m_CurrentFeedTurn = turn;
    }
    //#endif

    string		getNickname() const
    {
        return m_Nickname;
    }
    void		setNickname(const string &name)
    {
        m_Nickname = name;
    }

    int			getMagicRemainSec() const
    {
        return m_MagicRemainSec;
    }
    void		setMagicRemainSec( int sec )
    {
        m_MagicRemainSec = sec;
    }

    int			getExpertPetChangerRemainSec() const
    {
        return m_ExpertPetChangerRemainSec;
    }
    void		setExpertPetChangerRemainSec( int sec )
    {
        m_ExpertPetChangerRemainSec = sec;
    }

    CEffectID_t	getEnchantSkillType() const
    {
        return m_EnchantSkillType;
    }
    void		setEnchantSkillType(CEffectID_t type)
    {
        m_EnchantSkillType = type;
    }

    void			setPetVersionOption(OptionType_t PetOption)
    {
        m_PetVersionOption = PetOption;
    }
    OptionType_t	getPetVersionOption() const
    {
        return m_PetVersionOption;
    }

    // 펫 옵션

    void						setOptionType(const list<OptionType_t> &OptionType)
    {
        m_OptionType = OptionType;
    }
    int							getOptionTypeSize()
    {
        return m_OptionType.size();
    }
    const list<OptionType_t>	&getOptionType()
    {
        return m_OptionType;
    }
    OptionType_t				getFirstOptionType()
    {
        if (m_OptionType.empty()) return 0;
        return m_OptionType.front();
    }
    void						removeOptionType(OptionType_t OptionType)
    {
        std::list<OptionType_t>::iterator itr = std::find(m_OptionType.begin(), m_OptionType.end(), OptionType);
        if (itr != m_OptionType.end()) m_OptionType.erase(itr);
    }
    void						addOptionType(OptionType_t OptionType)
    {
        m_OptionType.push_back(OptionType);
    }

    void						setMixOptionType(const list<OptionType_t> &mixOptionType)
    {
        m_MixOptionType = mixOptionType;
    }
    int							getMixOptionTypeSize()
    {
        return m_MixOptionType.size();
    }
    const list<OptionType_t>	&getMixOptionType()
    {
        return m_MixOptionType;
    }
    OptionType_t				getMixFirstOptionType()
    {
        if (m_MixOptionType.empty()) return 0;
        return m_MixOptionType.front();
    }
    void						removeMixOptionType(OptionType_t mixOptionType)
    {
        std::list<OptionType_t>::iterator itr = std::find(m_MixOptionType.begin(), m_MixOptionType.end(), mixOptionType);
        if (itr != m_MixOptionType.end()) m_MixOptionType.erase(itr);
    }
    void						addMixOptionType(OptionType_t mixOptionType)
    {
        m_MixOptionType.push_back(mixOptionType);
    }
    void						changeMixOptionType(OptionType_t currentOptionType, OptionType_t newOptionType)
    {
        list<OptionType_t>::iterator itr = find(m_MixOptionType.begin(), m_MixOptionType.end(), currentOptionType);
        if (itr != m_MixOptionType.end()) *itr = newOptionType;
    }


    string		toString();

private:
    PetType_t		m_PetType;
    MonsterType_t	m_PetCreatureType;
    PetLevel_t		m_PetLevel;
    PetExp_t		m_PetExp;
    PetHP_t			m_PetHP;
    PetAttr_t		m_PetAttr;
    PetAttrLevel_t	m_PetAttrLevel;
    OptionType_t	m_PetOption;
    OptionType_t	m_PetVersionOption;
    ItemType_t		m_PetFoodType;
    BYTE			m_CanGamble;
    BYTE			m_CanCutHead;
    BYTE			m_CanAttack;
    CEffectID_t		m_EnchantSkillType;

    BYTE			m_IsSummonInfo;
    VSDateTime		m_LastFeedTime;

    int				m_MagicRemainSec;
    int				m_ExpertPetChangerRemainSec;

    //#ifdef __GAME_SERVER__
    BYTE			m_FeedTurn;
    BYTE			m_CurrentFeedTurn;
    string			m_Nickname;
    //#endif

    list<OptionType_t> m_OptionType;       // item option type
    list<OptionType_t> m_MixOptionType;       // item option type

    PetItem		*m_pPetItem;
};

#endif
