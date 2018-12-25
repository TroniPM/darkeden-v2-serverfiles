//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddBat.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_BAT_H__
#define __GC_ADD_BAT_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddBat;
//
// 시야 안에 Bat 가 들어왔을 경우, 이 패킷에 Bat 정보를 담아서 전송받는다.
//////////////////////////////////////////////////////////////////////////////

class GCAddBat : public Packet 
{
public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_ADD_BAT; }
	PacketSize_t getPacketSize()  
	{ 
		PacketSize_t PacketSize;
		PacketSize = szObjectID 
			+ szBYTE + m_Name.size() 
			//+ szSpriteType 
			//+ szColor + szColor
			+ szItemType
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ sizeof(int);
		switch(m_BatType)
		{
		case 1:
		case 2:
			PacketSize += szColor + szColor; 
			break;
		default :
			break;
		}
	PacketSize +=  szLevel;
		return PacketSize;
	}

	string getPacketName()  { return "GCAddBat"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	string getName()  { return m_Name; }
	void setName(string name) throw() { m_Name = name; }

	/*
	// get/set sprite type
	SpriteType_t getSpriteType()  { return m_SpriteType; }
	void setSpriteType(SpriteType_t spriteType) throw() { m_SpriteType = spriteType; }

	// get/set main color
	Color_t getMainColor()  { return m_MainColor; }
	void setMainColor(Color_t color) throw() { m_MainColor = color; }

	// get/set sub color
	Color_t getSubColor()  { return m_SubColor; }
	void setSubColor(Color_t color) throw() { m_SubColor = color; }
	*/

	// get/set X
	Coord_t getX()  { return m_X; }
	void setXYDir(Coord_t x, Coord_t y, Dir_t Dir) throw() { m_X = x; m_Y = y; m_Dir = Dir;}
	
	// get/set Y
	Coord_t getY()  { return m_Y; }

	// get/set Dir
	Dir_t getDir()  { return m_Dir; }

	// get /set MaxHP
	HP_t getMaxHP()  { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) throw() { m_MaxHP = MaxHP; }

	// get /set CurrentHP
	HP_t getCurrentHP()  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

	// get / set ItemType
    ItemType_t getItemType()  { return m_ItemType; }
    void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID(GuildID_t GuildID) throw() { m_GuildID = GuildID; }

	Color_t getColor()  { return m_Color; }
	void setColor(Color_t color) throw() { m_Color = color; }

	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t CLevel) throw() { m_Level = CLevel; }

	Color_t		getAdvanceBatColor()  { return m_AdvanceBatColor; }
	void		setAdvanceBatColor(WORD set) { m_AdvanceBatColor = set; }

	unsigned char getBatType() { return m_BatType; }
	void setBatType(uchar Type) { m_BatType = Type; }

	Color_t getWingColor1() { return m_WingColor1; }
	void setWingColor1(Color_t Color) { m_WingColor1 = Color; }
	
	Color_t getWingColor2() { return m_WingColor2; }
	void setWingColor2(Color_t Color) { m_WingColor2 = Color; }

private:
	ObjectID_t   m_ObjectID;
	string       m_Name;       // Bat의 이름
	
	/*
	SpriteType_t m_SpriteType; // 스프라이트 타입
	Color_t      m_MainColor;  // 메인 칼라
	Color_t      m_SubColor;   // 서브 칼라
	*/

	// 변신 아이템의 종류
	ItemType_t	 m_ItemType;

	Coord_t      m_X;          // X
	Coord_t      m_Y;          // Y
	Dir_t        m_Dir;        // Direction
	HP_t         m_CurrentHP;  // current hp
	HP_t         m_MaxHP;      // max hp
	GuildID_t	 m_GuildID;    // GuildID
	Color_t	 	 m_Color;      // Color
	Level_t	m_Level;	// Level
	Color_t		 m_AdvanceBatColor;
	unsigned char m_BatType;
	Color_t m_WingColor1;
	Color_t m_WingColor2;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddBatFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddBatFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddBat(); }
	string getPacketName()  { return "GCAddBat"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_BAT; }
	PacketSize_t getPacketMaxSize()  
	{
		return szObjectID 
			+ szBYTE + 20 
			+ szItemType
			//+ szSpriteType 
			//+ szColor + szColor
			+ szCoord + szCoord + szDir
			+ szHP
			+ szGuildID
			+ szColor
			+ szLevel
			+ szColor
			;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddBatHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddBatHandler 
{
public:
	static void execute(GCAddBat* pPacket, Player* pPlayer) throw(Error);

};

#endif
