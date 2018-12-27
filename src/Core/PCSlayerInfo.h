//////////////////////////////////////////////////////////////////////////////
// Filename    : PCSlayerInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_SLAYER_INFO_H__
#define __PC_SLAYER_INFO_H__

#include "PCInfo.h"
#include <bitset>

//////////////////////////////////////////////////////////////////////////////
// Slayer ������ ��� �ִ� ��ü.
// GCPCList ��Ŷ�� ��ܼ� Ŭ���̾�Ʈ���� ���۵ȴ�.
// �������̳� �ɷ��ִ� ���� ���� ������ ������� �ʴ�.
//////////////////////////////////////////////////////////////////////////////

class PCSlayerInfo : public PCInfo
{
public:
    // Slayer Outlook Information
    enum SlayerBits
    {
        SLAYER_BIT_SEX,
        SLAYER_BIT_HAIRSTYLE1,
        SLAYER_BIT_HAIRSTYLE2,
        SLAYER_BIT_HELMET1,
        SLAYER_BIT_HELMET2,
        SLAYER_BIT_JACKET1,
        SLAYER_BIT_JACKET2,
        SLAYER_BIT_JACKET3,
        SLAYER_BIT_JACKET4,
        SLAYER_BIT_JACKET5,
        SLAYER_BIT_JACKET6,
        SLAYER_BIT_JACKET7,
        SLAYER_BIT_PANTS1,
        SLAYER_BIT_PANTS2,
        SLAYER_BIT_PANTS3,
        SLAYER_BIT_WEAPON1,
        SLAYER_BIT_WEAPON2,
        SLAYER_BIT_WEAPON3,
        SLAYER_BIT_WEAPON4,
        SLAYER_BIT_SHIELD1,
        SLAYER_BIT_SHIELD2,
        SLAYER_BIT_MAX
        //SLAYER_BIT_WEAPON4,
    };

    // Slayer Color Informations
    enum SlayerColors
    {
        SLAYER_COLOR_HAIR,
        SLAYER_COLOR_SKIN,
        SLAYER_COLOR_HELMET,
        SLAYER_COLOR_JACKET,
        SLAYER_COLOR_PANTS,
        SLAYER_COLOR_WEAPON,
        SLAYER_COLOR_SHIELD,
        SLAYER_COLOR_MAX
    };

public:

    // get pc type
    PCType getPCType ()
    {
        return PC_SLAYER;
    }

    // read data from socket input stream
    void read (SocketInputStream &iStream);

    // write data to socket output stream
    void write (SocketOutputStream &oStream) ;

    // get size of object
    uint getSize ()
    {
        return szBYTE + m_Name.size()
               + szSlot
               + szAlignment
               + szAttr * 3
               + szRank
               + szExp * 3
               + szHP * 2
               + szMP * 2
               + szFame
               + szFame
               //+ szGold
               + szSkillLevel * 6
               //+ szZoneID
               + szDWORD                       // �����̾� �÷���
               + szColor * SLAYER_COLOR_MAX // ���� ����
               + szLevel;
    }

    // get max size of object
    static uint getMaxSize ()
    {
        return szBYTE + 20
               + szSlot
               + szAlignment
               + szAttr * 3
               + szRank
               + szExp * 3
               + szHP * 2
               + szMP * 2
               + szFame
               + szFame
               //+ szGold
               + szSkillLevel * 6
               //+ szZoneID
               + szDWORD                       // �����̾� �÷���
               + szColor * SLAYER_COLOR_MAX // ���� ����
               + szLevel;
    }

    // get debug string
    string toString () ;

public:
    // get/set PC's name
    string getName ()
    {
        return m_Name;
    }
    void setName (const string &name)
    {
        m_Name = (name.size() > 20) ? name.substr(0, 20) : name;
    }

    // get/set Slot
    Slot getSlot ()
    {
        return m_Slot;
    }
    void setSlot (Slot slot)
    {
        m_Slot = slot;
    }
    void setSlot (string slot)
    {
        if (slot == Slot2String[SLOT1])
        {
            m_Slot = SLOT1;
        }
        else if (slot == Slot2String[SLOT2])
        {
            m_Slot = SLOT2;
        }
        else if (slot == Slot2String[SLOT3])
        {
            m_Slot = SLOT3;
        }
        else
        {
            throw InvalidProtocolException("invalid slot value");
        }
    }

    // get/set Alignment
    Alignment_t getAlignment()
    {
        return m_Alignment;
    }
    void setAlignment(Alignment_t Alignment)
    {
        m_Alignment = Alignment;
    }

    // get/set STR
    // *CAUTION*
    // Assert()�� �� ���, NDEBUG ��忡���� disable �ǹǷ� if �� üũ�ؾ� �Ѵ�.
    Attr_t getSTR ()
    {
        if (m_STR > maxSlayerAttr) throw Error("STR out of range");
        return m_STR;
    }
    void setSTR (Attr_t str)
    {
        if (str > maxSlayerAttr) throw Error("STR out of range");
        m_STR = str;
    }

    // get/set DEX
    Attr_t getDEX ()
    {
        if (m_DEX > maxSlayerAttr) throw Error("DEX out of range");
        return m_DEX;
    }
    void setDEX (Attr_t dex)
    {
        if (dex > maxSlayerAttr) throw Error("DEX out of range");
        m_DEX = dex;
    }

    // get/set INT
    Attr_t getINT ()
    {
        if (m_INT > maxSlayerAttr) throw Error("INT out of range");
        return m_INT;
    }
    void setINT (Attr_t inte)
    {
        if (inte > maxSlayerAttr) throw Error("INT out of range");
        m_INT = inte;
    }

    // get/set STR Exp
    Exp_t getSTRExp ()
    {
        return m_STRExp;
    };
    void setSTRExp(Exp_t STRExp)
    {
        m_STRExp = STRExp;
    }

    // get/set DEX Exp
    Exp_t getDEXExp ()
    {
        return m_DEXExp;
    };
    void setDEXExp(Exp_t DEXExp)
    {
        m_DEXExp = DEXExp;
    }

    // get/set INT Exp
    Exp_t getINTExp ()
    {
        return m_INTExp;
    };
    void setINTExp(Exp_t INTExp)
    {
        m_INTExp = INTExp;
    }


    Rank_t getRank ()
    {
        return m_Rank;
    }
    void setRank (Rank_t rank)
    {
        m_Rank = rank;
    }


    // get/set HP
    HP_t getHP (AttrType attrType = ATTR_CURRENT)
    {
        return m_HP[attrType];
    }
    void setHP (HP_t hp, AttrType attrType = ATTR_CURRENT)
    {
        m_HP[attrType] = hp;
    }
    void setHP (HP_t curHP, HP_t maxHP)
    {
        m_HP[ATTR_CURRENT] = curHP;
        m_HP[ATTR_MAX] = maxHP;
    }

    // get/set MP
    MP_t getMP (AttrType attrType = ATTR_CURRENT)
    {
        return m_MP[attrType];
    }
    void setMP (MP_t mp, AttrType attrType = ATTR_CURRENT)
    {
        m_MP[attrType] = mp;
    }
    void setMP (MP_t curMP, MP_t maxMP)
    {
        m_MP[ATTR_CURRENT] = curMP;
        m_MP[ATTR_MAX] = maxMP;
    }

    // get/set fame
    Fame_t getFame ()
    {
        return m_Fame;
    }
    void setFame (Fame_t fame)
    {
        m_Fame = fame;
    }

    // get/set fame
    Fame_t getKillPoint ()
    {
        return m_KillPoint;
    }
    void setKillPoint (Fame_t KillPoint)
    {
        m_KillPoint = KillPoint;
    }

    // get/set gold
    //Gold_t getGold ()  { return m_Gold; }
    //void setGold (Gold_t gold)  { m_Gold = gold; }

    // get/set skill domain level
    SkillLevel_t getSkillDomainLevel (SkillDomain domain)
    {
        return m_DomainLevels[ domain ];
    }
    void setSkillDomainLevel (SkillDomain domain, SkillLevel_t skillLevel)
    {
        m_DomainLevels[ domain ] = skillLevel;
    }

    // get/set zoneID
    //ZoneID_t getZoneID ()  { return m_ZoneID; }
    //void setZoneID (ZoneID_t zoneID)  { m_ZoneID = zoneID; }

    Level_t getAdvancementLevel() const
    {
        return m_AdvancementLevel;
    }
    void    setAdvancementLevel(Level_t level)
    {
        m_AdvancementLevel = level;
    }

    // get/set outlook
public:
    // get/set sex
    Sex getSex ()
    {
        return m_Outlook.test(SLAYER_BIT_SEX) ? MALE : FEMALE;
    }
    void setSex (Sex sex)
    {
        m_Outlook.set(SLAYER_BIT_SEX, (sex == MALE ? true : false));
    }

    void setSex (string sex)
    {
        if (sex == Sex2String[MALE])
            m_Outlook.set(SLAYER_BIT_SEX, true);
        else if (sex == Sex2String[FEMALE])
            m_Outlook.set(SLAYER_BIT_SEX, false);
        else
            throw InvalidProtocolException("invalid sex value");
    }

    // get/set hair style
    HairStyle getHairStyle ()
    {
        return HairStyle((m_Outlook.to_ulong() >> SLAYER_BIT_HAIRSTYLE1) & 3);
    }
    void setHairStyle (HairStyle hairStyle)
    {
        m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
        m_Outlook |= bitset<SLAYER_BIT_MAX>(hairStyle << SLAYER_BIT_HAIRSTYLE1);
    }

    void setHairStyle (string hairStyle)
    {
        if (hairStyle == HairStyle2String[HAIR_STYLE1])
        {
            m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
            m_Outlook |= bitset<SLAYER_BIT_MAX>(HAIR_STYLE1 << SLAYER_BIT_HAIRSTYLE1);
        }
        else if (hairStyle == HairStyle2String[HAIR_STYLE2])
        {
            m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
            m_Outlook |= bitset<SLAYER_BIT_MAX>(HAIR_STYLE2 << SLAYER_BIT_HAIRSTYLE1);
        }
        else if (hairStyle == HairStyle2String[HAIR_STYLE3])
        {
            m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HAIRSTYLE1);
            m_Outlook |= bitset<SLAYER_BIT_MAX>(HAIR_STYLE3 << SLAYER_BIT_HAIRSTYLE1);
        }
        else
            throw InvalidProtocolException("invalid hairstyle value");
    }

    // get/set helmet
    HelmetType getHelmetType ()
    {
        return HelmetType((m_Outlook.to_ulong() >> SLAYER_BIT_HELMET1) & 3);
    }
    void setHelmetType (HelmetType helmetType)
    {
        m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_HELMET1);
        m_Outlook |= bitset<SLAYER_BIT_MAX>(helmetType << SLAYER_BIT_HELMET1);
    }

    // get/set jacket
    JacketType getJacketType ()
    {
        return JacketType((m_Outlook.to_ulong() >> SLAYER_BIT_JACKET1) & 7);
    }
    void setJacketType (JacketType jacketType)
    {
        m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_JACKET1);
        m_Outlook |= bitset<SLAYER_BIT_MAX>(jacketType << SLAYER_BIT_JACKET1);
    }

    // get/set pants
    PantsType getPantsType ()
    {
        return PantsType((m_Outlook.to_ulong() >> SLAYER_BIT_PANTS1) & 7);
    }
    void setPantsType (PantsType pantsType)
    {
        m_Outlook &= ~bitset<SLAYER_BIT_MAX>(7 << SLAYER_BIT_PANTS1);
        m_Outlook |= bitset<SLAYER_BIT_MAX>(pantsType << SLAYER_BIT_PANTS1);
    }

    // get/set weapon
    WeaponType getWeaponType ()
    {
        return WeaponType((m_Outlook.to_ulong() >> SLAYER_BIT_WEAPON1) & 31);
    }
    void setWeaponType (WeaponType weaponType)
    {
        m_Outlook &= ~bitset<SLAYER_BIT_MAX>(31 << SLAYER_BIT_WEAPON1);
        m_Outlook |= bitset<SLAYER_BIT_MAX>(weaponType << SLAYER_BIT_WEAPON1);
    }

    // get/set Shield Type
    ShieldType getShieldType ()
    {
        return ShieldType((m_Outlook.to_ulong() >> SLAYER_BIT_SHIELD1) & 3);
    }
    void setShieldType (ShieldType shieldType)
    {
        m_Outlook &= ~bitset<SLAYER_BIT_MAX>(3 << SLAYER_BIT_SHIELD1);
        m_Outlook |= bitset<SLAYER_BIT_MAX>(shieldType << SLAYER_BIT_SHIELD1);
    }

    void setShapeInfo(DWORD flag, Color_t color[SLAYER_COLOR_MAX]) ;

    // get/set color
public:

    // get/set hair color
    Color_t getHairColor ()
    {
        return m_Colors[ SLAYER_COLOR_HAIR ];
    }
    void setHairColor (Color_t color)
    {
        m_Colors[ SLAYER_COLOR_HAIR ] = color;
    }

    // get/set skin color
    Color_t getSkinColor ()
    {
        return m_Colors[ SLAYER_COLOR_SKIN ];
    }
    void setSkinColor (Color_t color)
    {
        m_Colors[ SLAYER_COLOR_SKIN ] = color;
    }

    // get/set helmet color
    Color_t getHelmetColor (ColorType colorType = MAIN_COLOR)
    {
        return m_Colors[ SLAYER_COLOR_HELMET + (uint)colorType ];
    }
    void setHelmetColor (Color_t color, ColorType colorType = MAIN_COLOR)
    {
        m_Colors[ SLAYER_COLOR_HELMET + (uint)colorType ] = color;
    }

    // get/set jacket color
    Color_t getJacketColor (ColorType colorType = MAIN_COLOR)
    {
        return m_Colors[ SLAYER_COLOR_JACKET + (uint)colorType ];
    }
    void setJacketColor (Color_t color, ColorType colorType = MAIN_COLOR)
    {
        m_Colors[ SLAYER_COLOR_JACKET + (uint)colorType ] = color;
    }

    // get/set pants color
    Color_t getPantsColor (ColorType colorType = MAIN_COLOR)
    {
        return m_Colors[ SLAYER_COLOR_PANTS + (uint)colorType ];
    }
    void setPantsColor (Color_t color, ColorType colorType = MAIN_COLOR)
    {
        m_Colors[ SLAYER_COLOR_PANTS + (uint)colorType ] = color;
    }

    // get/set weapon color
    Color_t getWeaponColor (ColorType colorType = MAIN_COLOR)
    {
        return m_Colors[ SLAYER_COLOR_WEAPON + (uint)colorType ];
    }
    void setWeaponColor (Color_t color, ColorType colorType = MAIN_COLOR)
    {
        m_Colors[ SLAYER_COLOR_WEAPON + (uint)colorType ] = color;
    }

    // get/set shield color
    Color_t getShieldColor (ColorType colorType = MAIN_COLOR)
    {
        return m_Colors[ SLAYER_COLOR_SHIELD + (uint)colorType ];
    }
    void setShieldColor (Color_t color, ColorType colorType = MAIN_COLOR)
    {
        m_Colors[ SLAYER_COLOR_SHIELD + (uint)colorType ] = color;
    }

private:

    // PC name
    string m_Name;

    // PC slot
    Slot m_Slot;

    // Alignment
    Alignment_t m_Alignment;

    // *NOTE
    // ATTR_BASIC   : ���� �ɷ�ġ.
    Attr_t m_STR;
    Attr_t m_DEX;
    Attr_t m_INT;

    // �ɷ�ġ �ø��� ���� ����ġ
    // ���� ������ ���� ���� ��ǥ ����ġ��
    // ��Ż ����ġ�� Client���� Exp Table�� �����Ƿ�
    // Ŭ���̾�Ʈ���� ���� �ϵ��� �Ѵ�.
    Exp_t m_STRExp;
    Exp_t m_DEXExp;
    Exp_t m_INTExp;

    // ���
    Rank_t m_Rank;

    // HP/MP
    // HP[0] = current hp, hp[1] == max hp
    HP_t m_HP[2];
    MP_t m_MP[2];

    // Fame
    Fame_t m_Fame;
    Fame_t m_KillPoint;

    // skill domain levels
    SkillLevel_t m_DomainLevels[6];

    /*
    // Gold
    Gold_t m_Gold;


    // ���������� ��� ��
    ZoneID_t m_ZoneID;
    */

    bitset<SLAYER_BIT_MAX> m_Outlook;       // �����̾� �ܸ� ����
    Color_t m_Colors[SLAYER_COLOR_MAX];     // �����̾� ���� ����

    Level_t m_AdvancementLevel;
};

#endif
