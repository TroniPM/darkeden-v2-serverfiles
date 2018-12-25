//////////////////////////////////////////////////////////////////////////////
// Filename    : PCOustersInfo3.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_OUSTERS_INFO_3_H__
#define __PC_OUSTERS_INFO_3_H__

#include "PCInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class PCOustersInfo3;
// �����̾��� �ܸ� ������ ��� �ִ� ��ü
// GCAddOusters, GCAddOustersCorpse �� ��ܼ� ���۵ȴ�.
//////////////////////////////////////////////////////////////////////////////

class PCOustersInfo3 : public PCInfo 
{
public:
	// Ousters Color Informations
	enum OustersColors 
	{
		OUSTERS_COLOR_COAT,
		OUSTERS_COLOR_HAIR,
		OUSTERS_COLOR_ARM,
		OUSTERS_COLOR_BOOTS,
		OUSTERS_COLOR_WINGBODY,
		OUSTERS_COLOR_WINGEFFECT,
		OUSTERS_COLOR_MAX
	};

public:
	PCOustersInfo3 () throw () 
	{
	}

	PCOustersInfo3 (const PCOustersInfo3 & oustersInfo) throw ()
		: m_ObjectID(oustersInfo.m_ObjectID), m_Name(oustersInfo.m_Name), 
		m_X(oustersInfo.m_X), m_Y(oustersInfo.m_Y), m_Dir(oustersInfo.m_Dir),
		m_Sex(oustersInfo.m_Sex), m_CoatType(oustersInfo.m_CoatType), m_ArmType(oustersInfo.m_ArmType), m_SylphType(oustersInfo.m_SylphType),
		m_WingSylphType(oustersInfo.m_WingSylphType),
		m_WingItemType(oustersInfo.m_WingItemType),
		m_MasterEffectColor(oustersInfo.m_MasterEffectColor),
		m_CurrentHP(oustersInfo.m_CurrentHP), m_MaxHP(oustersInfo.m_MaxHP), m_AttackSpeed(oustersInfo.m_AttackSpeed),
		m_Alignment(oustersInfo.m_Alignment), m_GuildID(oustersInfo.m_GuildID),
		m_Rank(oustersInfo.m_Rank), m_AdvancementLevel(oustersInfo.m_AdvancementLevel)
	{
		for (uint i = 0 ; i < OUSTERS_COLOR_MAX ; i ++)
			m_Colors[i] = oustersInfo.m_Colors[i];

		m_Competence = oustersInfo.m_Competence;
	}
	
public:
	PCType getPCType ()  { return PC_OUSTERS; }

	void read (SocketInputStream & iStream);
	void write (SocketOutputStream & oStream) ;

	uint getSize () 
	{
		return szObjectID					// ObjectID
			+ szBYTE + m_Name.size() 		// �����̾� �̸�
			+ szCoord + szCoord + szDir 	// ��ǥ�� ����				
			+ szSex							// ����
			+ szBYTE						// shape
			+ szBYTE						// wingSylphType
			+ szItemType					// Wing ItemType
			+ szColor* OUSTERS_COLOR_MAX	// ����
			+ szBYTE
			+ szHP* 2						// �ִ� ü��
			+ szAlignment					// ����
			+ szSpeed						// ���� �ӵ�
			+ szGuildID						// ��� ���̵�
			+ szRank						// ���
			+ szBYTE						// ����
			+ szuint
			+ szLevel;
	}

	// get max size of object
	static uint getMaxSize () throw ()
	{
		return szObjectID					// ObjectID
			+ szBYTE + 20 					// �����̾� �̸�
			+ szCoord + szCoord + szDir 	// ��ǥ�� ����				
			+ szSex							// ����
			+ szBYTE						// shape
			+ szBYTE						// wingSylphType
			+ szItemType					// Wing ItemType
			+ szColor* OUSTERS_COLOR_MAX	// ����
			+ szBYTE
			+ szHP* 2						// �ִ� ü��
			+ szSpeed						// ���� �ӵ�
			+ szGuildID						// ��� ���̵�
			+ szRank						// ���
			+ szBYTE						// ����
			+ szuint
			+ szLevel;
	}

	PCOustersInfo3 & operator = (const PCOustersInfo3 & oustersInfo) throw ()
	{
		if (&oustersInfo == this)
			return *this;

		m_ObjectID = oustersInfo.m_ObjectID;
		m_Name = oustersInfo.m_Name;
		m_X = oustersInfo.m_X;
		m_Y = oustersInfo.m_Y;
		m_Dir = oustersInfo.m_Dir;
		m_Sex = oustersInfo.m_Sex;
		m_CoatType = oustersInfo.m_CoatType;
		m_ArmType = oustersInfo.m_ArmType;
		m_SylphType = oustersInfo.m_SylphType;
		m_CurrentHP = oustersInfo.m_CurrentHP;
		m_MaxHP = oustersInfo.m_MaxHP;
		m_AttackSpeed = oustersInfo.m_AttackSpeed;
		m_Alignment = oustersInfo.m_Alignment;
		m_WingSylphType = oustersInfo.m_WingSylphType;
		m_WingItemType = oustersInfo.m_WingItemType;
		for (uint i = 0 ; i < OUSTERS_COLOR_MAX ; i ++)
			m_Colors[i] = oustersInfo.m_Colors[i];

		m_MasterEffectColor = oustersInfo.m_MasterEffectColor;

		m_Competence = oustersInfo.m_Competence;

		m_GuildID = oustersInfo.m_GuildID;
		m_UnionID = oustersInfo.m_UnionID;
		m_Rank = oustersInfo.m_Rank;
		m_AdvancementLevel = oustersInfo.m_AdvancementLevel;

		return *this;
	}

	string toString () ;

public:
	ObjectID_t getObjectID ()  { return m_ObjectID; }
	void setObjectID (ObjectID_t objectID) throw () { m_ObjectID = objectID; }

    string getName ()  { return m_Name; }
    void setName (const string & name) throw (Error) { m_Name = name; Assert(m_Name != ""); }

	Coord_t getX ()  { return m_X; }
	void setX (Coord_t x) throw () { m_X = x; }

	Coord_t getY ()  { return m_Y; }
	void setY (Coord_t y) throw () { m_Y = y; }

	Dir_t getDir ()  { return m_Dir; }
	void setDir (Dir_t dir) throw () { m_Dir = dir; }

	Sex getSex ()  { return m_Sex; }
	void setSex (Sex sex) throw () { m_Sex = sex; }
	void setSex (const string & sex) throw (InvalidProtocolException)
	{
		if (sex == Sex2String[MALE]) 
			m_Sex = MALE;
		else if (sex == Sex2String[FEMALE]) 
			m_Sex = FEMALE;
		else
			throw InvalidProtocolException("invalid sex value");
	}

	Color_t getCoatColor ()  { return m_Colors[OUSTERS_COLOR_COAT]; }
	void setCoatColor (Color_t coatColor) throw () { m_Colors[OUSTERS_COLOR_COAT] = coatColor; }

	Color_t getHairColor ()  { return m_Colors[OUSTERS_COLOR_HAIR]; }
	void setHairColor (Color_t hairColor) throw () { m_Colors[OUSTERS_COLOR_HAIR] = hairColor; }

	Color_t getArmColor ()  { return m_Colors[OUSTERS_COLOR_ARM]; }
	void setArmColor (Color_t armColor) throw () { m_Colors[OUSTERS_COLOR_ARM] = armColor; }

	Color_t getBootsColor ()  { return m_Colors[OUSTERS_COLOR_BOOTS]; }
	void setBootsColor (Color_t bootsColor) throw () { m_Colors[OUSTERS_COLOR_BOOTS] = bootsColor; }

	BYTE getWingSylphType() { return m_WingSylphType; }
	void setWingSylphType(BYTE Type) throw (){ m_WingSylphType = Type; }

	ItemType_t getWingItemType()  { return m_WingItemType; }
	void setWingItemType(ItemType_t ItemType) throw() { m_WingItemType = ItemType; }

	Color_t getWingBodyColor()  { return m_Colors[OUSTERS_COLOR_WINGBODY]; }
	void setWingBodyColor(Color_t Color) throw () { m_Colors[OUSTERS_COLOR_WINGBODY] = Color; }

	Color_t getWingEffectColor()  { return m_Colors[OUSTERS_COLOR_WINGEFFECT]; }
	void setWingEffectColor(Color_t Color) throw () { m_Colors[OUSTERS_COLOR_WINGEFFECT] = Color; }

	BYTE getMasterEffectColor() const { return m_MasterEffectColor; }
	void setMasterEffectColor( BYTE color ) { m_MasterEffectColor = color; }

	OustersCoatType getCoatType()  { return m_CoatType; }
    void setCoatType(OustersCoatType CoatType) throw() { m_CoatType = CoatType; }

	OustersArmType getArmType()  { return m_ArmType; }
    void setArmType(OustersArmType ArmType) throw() { m_ArmType = ArmType; }

	OustersSylphType getSylphType()  { return m_SylphType; }
    void setSylphType(OustersSylphType SylphType) throw() { m_SylphType = SylphType; }

	HP_t getCurrentHP()  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

	HP_t getMaxHP()  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) throw() { m_MaxHP = MaxHP; }

	Speed_t getAttackSpeed()  { return m_AttackSpeed; }
	void setAttackSpeed(Speed_t AttackSpeed) throw() { m_AttackSpeed = AttackSpeed; }

	Alignment_t getAlignment()  { return m_Alignment; }
	void setAlignment(Alignment_t Alignment)  throw() { m_Alignment = Alignment; }

	BYTE getCompetence(void) const { return m_Competence; }
	void setCompetence(BYTE competence) { m_Competence = competence; }

	GuildID_t getGuildID(void) const { return m_GuildID; }
	void setGuildID(GuildID_t GuildID ) { m_GuildID = GuildID; }

	uint getUnionID(void) const { return m_UnionID; }
	void setUnionID(uint UnionID ) { m_UnionID = UnionID; }

	Rank_t getRank ()  { return m_Rank; }
	void setRank (Rank_t rank) throw () { m_Rank = rank; }

	Level_t	getAdvancementLevel() const { return m_AdvancementLevel; }
	void setAdvancementLevel( Level_t level ) { m_AdvancementLevel = level; }

private :

	// PC's object id
	ObjectID_t m_ObjectID;

	// PC name
	string m_Name;

	Coord_t m_X;
	Coord_t m_Y;
	Dir_t m_Dir;

	// PC sex
	Sex m_Sex;

	// CoatType
	OustersCoatType m_CoatType;

	// ArmType
	OustersArmType m_ArmType;

	// SylphType
	OustersSylphType m_SylphType;
	BYTE m_WingSylphType;
	ItemType_t m_WingItemType;

	// colors
	Color_t m_Colors[OUSTERS_COLOR_MAX];

	// ������ ����Ʈ ����
	BYTE m_MasterEffectColor;

	// Current HP
	HP_t m_CurrentHP;

	// Max HP
	HP_t m_MaxHP;

	// Attack Speed
	Speed_t m_AttackSpeed;

	// ����
	Alignment_t m_Alignment;

	// ����
	BYTE m_Competence; 

	// ��� ���̵�
	GuildID_t m_GuildID;

	uint m_UnionID;

	// ���
	Rank_t		m_Rank;

	Level_t		m_AdvancementLevel;

};

#endif
