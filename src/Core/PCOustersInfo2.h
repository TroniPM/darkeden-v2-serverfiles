//////////////////////////////////////////////////////////////////////////////
// Filename    : PCOustersInfo2.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_OUSTERS_INFO_2_H__
#define __PC_OUSTERS_INFO_2_H__

#include "PCInfo.h"

//////////////////////////////////////////////////////////////////////////////
// Ousters ������ ��� �ִ� ��ü.
// GCPCList ��Ŷ�� ��ܼ� Ŭ���̾�Ʈ���� ���۵ȴ�.
// �������̳� �ɷ��ִ� ���� ���� ������ ������� �ʴ�.
//////////////////////////////////////////////////////////////////////////////

class PCOustersInfo2 : public PCInfo 
{
public:
	PCType getPCType ()  { return PC_OUSTERS; }

	void read (SocketInputStream & iStream);
	void write (SocketOutputStream & oStream) ;

	uint getSize () 
	{
		uint size;
		size = szObjectID					// ObjectID
			+ szBYTE + m_Name.size() 		// �ƿ콺�ͽ� �̸�
			+ szLevel
			+ szSex							// ����
			+ szBYTE;						// Slyph Type
		switch( m_WingSylphType )
		{
		case 2 : // SLYPH_TYPE_WING
			size += szItemType;				// Wing ItemType
			size += szColor * 2;
			break;
		case 1 : // SLYPH_TYPE_LEGACY
		case 0 : // SLYPH_TYPE_NONE
		default :
			break;
		}	
			size += szColor						// �Ӹ� ����
			+ szBYTE						// ������ ����Ʈ
			+ szAlignment					// ����
			+ szAttr * 3 * 3				// �ɷ�ġ
			+ szHP* 2						// HP
			+ szMP* 2						// MP
			+ szRank + szRankExp			// ��� ����ġ
			+ szExp							// ����ġ
			+ szGold 						// ��
			+ szFame						// Fame
			+ szFame						// Fame
			+ szSight						// �þ�
			+ szBonus						// ���ʽ� ����Ʈ
			+ szSkillBonus					// ��ų ���ʽ� ����Ʈ
			+ szSilver						// �ǹ� ������
			+ szBYTE						// ����
			+ szGuildID						// ��� ���̵�
			+ szBYTE + m_GuildName.size()	// ��� �̸�
			+ szGuildMemberRank				// guild member rank
			+ szuint
			+ szAttr
			+ szAttr
			+ szAttr						// ����
			+ szLevel
			+ szExp;
		return size;
	}

	static uint getMaxSize () throw ()
	{
		uint size;
		size = szObjectID				// ObjectID
			+ szBYTE + 20				// �ƿ콺�ͽ� �̸�
			+ szLevel
			+ szSex						// ����
			+ szBYTE					// Slyph Type
			+ szItemType					// Wing ItemType
			+ szColor * 2
			+ szColor					// ����
			+ szBYTE
			+ szAlignment				// ����
			+ szAttr * 3 * 3			// �ɷ�ġ
			+ szHP* 2					// HP
			+ szMP* 2					// MP
			+ szRank + szRankExp		// ��� ����ġ
			+ szExp						// ����ġ
			+ szGold					// ��
			+ szFame					// Fame
			+ szFame						// Fame
			+ szSight					// �þ�
			+ szBonus					// ���ʽ� ����Ʈ
			+ szSkillBonus				// ��ų ���ʽ� ����Ʈ
			+ szSilver					// �ǹ� ������
			+ szBYTE					// ����
			+ szGuildID					// ��� ���̵�
			+ szBYTE + 30				// ��� �̸�
			+ szGuildMemberRank	 		// guild member rank
			+ szuint
			+ szAttr
			+ szAttr
			+ szAttr					// ����
			+ szLevel
			+ szExp;
		return size;
	}

	string toString () ;

public:
	ObjectID_t getObjectID ()  { return m_ObjectID; }
	void setObjectID (ObjectID_t objectID) throw () { m_ObjectID = objectID; }

    string getName ()  { return m_Name; }
    void setName (string name) throw () { m_Name = (name.size() > 20) ? name.substr(0,20) : name; }

    Level_t getLevel ()  { return m_Level; }
    void setLevel (Level_t Level) throw () { m_Level = Level; }

	Sex getSex ()  { return m_Sex; }
	void setSex (Sex sex) throw () { m_Sex = sex; }
	void setSex (string sex) throw (InvalidProtocolException)
	{
		if (sex == Sex2String[MALE]) 
			m_Sex = MALE;
		else if (sex == Sex2String[FEMALE]) 
			m_Sex = FEMALE;
		else
			throw InvalidProtocolException("invalid sex value");
	}

	Fame_t getFame ()  { return m_Fame; }
	void setFame (Fame_t f) throw () { m_Fame = f; }

	Fame_t getKillPoint()  { return m_KillPoint; }
	void setKillPoint(Fame_t f) throw () { m_KillPoint = f; }
	
	Color_t getHairColor ()  { return m_HairColor; }
	void setHairColor (Color_t hairColor) throw () { m_HairColor = hairColor; }

	BYTE getWingSylphType() { return m_WingSylphType; }
	void setWingSylphType(BYTE Type) { m_WingSylphType = Type; }

	BYTE getWingItemType() { return m_WingItemType; }
	void setWingItemType(ItemID_t ItemType) { m_WingItemType = ItemType; }

	Color_t getWingBodyColor() { return m_WingBodyColor; }
	void setWingBodyColor(Color_t Color) { m_WingBodyColor = Color; }

	Color_t getWingEffectColor() { return m_WingEffectColor; }
	void setWingEffectColor(Color_t Color) { m_WingEffectColor = Color; }

	BYTE getMasterEffectColor ()  { return m_MasterEffectColor; }
	void setMasterEffectColor (BYTE color) throw () { m_MasterEffectColor = color; }

	Alignment_t getAlignment()  { return m_Alignment; }
	void setAlignment(Alignment_t Alignment) throw() { m_Alignment = Alignment; }

	Attr_t getSTR (AttrType attrType = ATTR_CURRENT) 
	{
		if (m_STR[attrType] > maxOustersAttr) throw Error("STR out of range"); 
		return m_STR[attrType]; 
	}
	void setSTR (Attr_t str, AttrType attrType = ATTR_CURRENT) throw (Error)
	{ 
		if (str > maxOustersAttr) throw Error("STR out of range"); 
		m_STR[attrType] = str; 
	}
	
	Attr_t getDEX (AttrType attrType = ATTR_CURRENT) 
	{ 
		if (m_DEX[attrType] > maxOustersAttr) throw Error("DEX out of range"); 
		return m_DEX[attrType]; 
	}
	void setDEX (Attr_t dex, AttrType attrType = ATTR_CURRENT) throw (Error)
	{ 
		if (dex > maxOustersAttr) throw Error("DEX out of range"); 
		m_DEX[attrType] = dex; 
	}
	
	Attr_t getINT (AttrType attrType = ATTR_CURRENT) 
	{ 
		if (m_INT[attrType] > maxOustersAttr) throw Error("INT out of range"); 
		return m_INT[attrType]; 
	}
	void setINT (Attr_t inte, AttrType attrType = ATTR_CURRENT) throw (Error)
	{
		if (inte > maxOustersAttr) throw Error("INT out of range"); 
		m_INT[attrType] = inte; 
	}

	HP_t getHP (AttrType attrType = ATTR_CURRENT)  { return m_HP[attrType]; }
	void setHP (HP_t hp, AttrType attrType = ATTR_CURRENT) throw () { m_HP[attrType] = hp; }
	void setHP (HP_t curHP, HP_t maxHP) throw () { m_HP[ATTR_CURRENT] = curHP; m_HP[ATTR_MAX] = maxHP; }

	HP_t getMP (AttrType attrType = ATTR_CURRENT)  { return m_MP[attrType]; }
	void setMP (MP_t mp, AttrType attrType = ATTR_CURRENT) throw () { m_MP[attrType] = mp; }
	void setMP (MP_t curMP, MP_t maxMP) throw () { m_MP[ATTR_CURRENT] = curMP; m_MP[ATTR_MAX] = maxMP; }

	Rank_t getRank ()  { return m_Rank; }
	void setRank (Rank_t rank) throw () { m_Rank = rank; }

	RankExp_t getRankExp ()  { return m_RankExp; }
	void setRankExp (RankExp_t rankExp) throw () { m_RankExp = rankExp; }

	Exp_t getExp ()  { return m_Exp; }
	void setExp (Exp_t exp) throw () { m_Exp = exp; }

	Gold_t getGold ()  { return m_Gold; }
	void setGold (Gold_t gold) throw () { m_Gold = gold; }

	Sight_t getSight ()  { return m_Sight; }
	void setSight (Sight_t sight) throw () { m_Sight = sight; }

	Bonus_t getBonus()  { return m_Bonus; }
	void setBonus(Bonus_t Bonus) throw() { m_Bonus = Bonus; }

	SkillBonus_t getSkillBonus()  { return m_SkillBonus; }
	void setSkillBonus(SkillBonus_t skillBonus) throw() { m_SkillBonus = skillBonus; }

	Silver_t getSilverDamage()  { return m_SilverDamage; }
	void setSilverDamage(Silver_t SilverDamage ) throw() { m_SilverDamage = SilverDamage; }

	BYTE getCompetence(void) const { return m_Competence; }
	void setCompetence(BYTE competence) { m_Competence = competence; }

	GuildID_t getGuildID(void) const { return m_GuildID; }
	void setGuildID(GuildID_t GuildID) { m_GuildID = GuildID; }

	string getGuildName() const { return m_GuildName; }
	void setGuildName( string guildName ) { m_GuildName = guildName; }

	GuildMemberRank_t getGuildMemberRank() const { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t guildMemberRank ) { m_GuildMemberRank = guildMemberRank; }

	uint getUnionID(void) const { return m_UnionID; }
	void setUnionID(uint UnionID) { m_UnionID = UnionID; }

	Level_t	getAdvancementLevel() const { return m_AdvancementLevel; }
	void setAdvancementLevel( Level_t level ) { m_AdvancementLevel = level; }

	Exp_t	getAdvancementGoalExp() const { return m_AdvancementGoalExp; }
	void setAdvancementGoalExp( Exp_t exp ) { m_AdvancementGoalExp = exp; }

	Attr_t getAttackBloodBurstPoint() const { return m_AttackBloodBurstPoint; }
	void setAttackBloodBurstPoint( Attr_t point ) { m_AttackBloodBurstPoint = point; }

	Attr_t getDefenseBloodBurstPoint() const { return m_DefenseBloodBurstPoint; }
	void setDefenseBloodBurstPoint( Attr_t point ) { m_DefenseBloodBurstPoint = point; }

	Attr_t getPartyBloodBurstPoint() const { return m_PartyBloodBurstPoint; }
	void setPartyBloodBurstPoin( Attr_t point ) { m_PartyBloodBurstPoint = point; }
private:

	// PC's object id
	ObjectID_t m_ObjectID;

	// PC name
	string m_Name;

	// PC name
	Level_t m_Level;

	// PC sex
	Sex m_Sex;

	// hair color, skin color,
	Color_t m_HairColor;
	BYTE m_MasterEffectColor;
	BYTE m_WingSylphType;
	ItemID_t m_WingItemType;
	Color_t m_WingBodyColor;
	Color_t m_WingEffectColor;

	// Alignment
	Alignment_t m_Alignment;

    // Attributes
	Attr_t m_STR[3];
	Attr_t m_DEX[3];
	Attr_t m_INT[3];

	// HP
	// HP[0] = current hp, hp[1] == max hp
	HP_t m_HP[2];

	// MP
	// MP[0] = current mp, mp[1] == max mp
	MP_t m_MP[2];

	// ���
	Rank_t			m_Rank;
	RankExp_t		m_RankExp;

	// Exp
	Exp_t m_Exp;

	// Fame
	Fame_t m_Fame;
	Fame_t m_KillPoint;

	// Gold
	Gold_t m_Gold;

	// �þ�
	Sight_t m_Sight;

	// ���ʽ� ����Ʈ
	Bonus_t m_Bonus;

	// ��ų ���ʽ� ����Ʈ
	SkillBonus_t m_SkillBonus;

	// �ǹ� ������
	Silver_t m_SilverDamage;

	// Competence
	BYTE m_Competence;

	// ��� ID
	GuildID_t m_GuildID;

	// guild name
	string m_GuildName;

	// guild member rank
	GuildMemberRank_t m_GuildMemberRank;

	uint m_UnionID;

	Level_t m_AdvancementLevel;
	Exp_t m_AdvancementGoalExp;

	Attr_t	m_AttackBloodBurstPoint;
	Attr_t	m_DefenseBloodBurstPoint;
	Attr_t	m_PartyBloodBurstPoint;
};

#endif
