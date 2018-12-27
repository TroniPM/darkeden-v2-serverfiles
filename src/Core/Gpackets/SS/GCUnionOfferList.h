
//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUnionOfferList.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNION_OFFER_LIST_H__
#define __GC_UNION_OFFER_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////
//
// class GCUnionOfferList;
//
// Ŭ���̾�Ʈ���� ������ ��û�� ��� ����Ʈ�� ���� �����ش�.
//
//////////////////////////////////////////////////////////////////////


class SingleGuildUnionOffer
{
public:
    enum OfferType
    {
        JOIN,
        QUIT
    };

	PacketSize_t getSize() 
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// Guild Type
			   szBYTE +					// Guild Name length
			   m_GuildName.size() +		// Guild Name
			   szBYTE +					// Guild Master length
			   m_MasterName.size() + 	// Guild Master
			   szDWORD;			// Date
	}

	static PacketSize_t getMaxSize() 
	{
		return szGuildID +		// Guild ID
			   szBYTE +			// Guild Type
			   szBYTE +			// Guild Name length
			   30 +				// Guild Name
			   szBYTE +			// Guild Master length
			   20 +				// Guild Master
			   szDWORD;			// Date
	}

    void read(SocketInputStream & iStream) 
	{
		__BEGIN_TRY

		BYTE szGuildName, szGuildMaster;

		iStream.read( m_GuildID );
		iStream.read( m_Type );
		iStream.read( szGuildName );
	
		if ( szGuildName == 0 )
			throw InvalidProtocolException( "szGuildName == 0" );
		if ( szGuildName > 30 )
			throw InvalidProtocolException( "too long szGuildName length" );

		iStream.read( m_GuildName, szGuildName );
		iStream.read( szGuildMaster );

		if ( szGuildMaster == 0 )
			throw InvalidProtocolException( "szGuildMaster == 0" );
		if ( szGuildMaster > 20 )
			throw InvalidProtocolException( "too long szGuildMaster length" );

		iStream.read( m_MasterName, szGuildMaster );

		iStream.read( m_Date );

		__END_CATCH
	}
		    
    void write(SocketOutputStream & oStream) 
	{
		__BEGIN_TRY
			
		BYTE szGuildName = m_GuildName.size();
		BYTE szGuildMaster = m_MasterName.size();

		if ( szGuildName == 0 )
			throw InvalidProtocolException( "szGuildName == 0" );
		if ( szGuildName > 30 )
			throw InvalidProtocolException( "too long szGuildName length" );

		if ( szGuildMaster == 0 )
			throw InvalidProtocolException( "szGuildMaster == 0" );
		if ( szGuildMaster > 20 )
			throw InvalidProtocolException( "too long szGuildMaster length" );

		oStream.write( m_GuildID );
		oStream.write( m_Type);
		oStream.write( szGuildName );
		oStream.write( m_GuildName );
		oStream.write( szGuildMaster );
		oStream.write( m_MasterName);

		oStream.write( m_Date );

		__END_CATCH
	}

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID )  { m_GuildID = GuildID; }

	// get/set OfferGuild Type (JOIN-��û�� ���, QUIT-Ż���û�� ���)
	BYTE	getGuildType()	 { return m_Type; }
	void	setGuildType( BYTE Type )  { m_Type = Type; }

	// get/set Guild Name
	const string& getGuildName()  { return m_GuildName; }
	void setGuildName( const string& GuildName )  { m_GuildName = GuildName; }

	// get/set Guild Master
	const string& getGuildMaster()  { return m_MasterName; }
	void setGuildMaster( const string& GuildMaster )  { m_MasterName = GuildMaster; }

	// get/set Date
	const DWORD getDate()  { return m_Date; }
	void setDate( DWORD date  )  { m_Date = date; }

private :

    BYTE    	m_Type;
    GuildID_t   m_GuildID;
    string      m_GuildName;
    string      m_MasterName;
	DWORD		m_Date;

};


class GCUnionOfferList : public Packet {

public :

    ~GCUnionOfferList() ;

	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_UNION_OFFER_LIST;}
	
	// get packet's body size
	PacketSize_t getPacketSize() ;

	// get packet name
	string getPacketName()  { return "GCUnionOfferList"; }
	
	// get packet's debug string
	string toString() ;

	list<SingleGuildUnionOffer*>	getUnionOfferList()  { return m_UnionOfferList; }
	
	void	addUnionOfferList(SingleGuildUnionOffer* pUnionOffer) 
	{
		m_UnionOfferList.push_back(pUnionOffer);
	}
	
private :
	list<SingleGuildUnionOffer*>	m_UnionOfferList;
};


//////////////////////////////////////////////////////////////////////
//
// class GCUnionOfferListFactory;
//
// Factory for GCUnionOfferList
//
//////////////////////////////////////////////////////////////////////

class GCUnionOfferListFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCUnionOfferList(); }

	// get packet name
	string getPacketName()  { return "GCUnionOfferList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_UNION_OFFER_LIST; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return SingleGuildUnionOffer::getMaxSize() * 20; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUnionOfferList;
//
//////////////////////////////////////////////////////////////////////

class GCUnionOfferListHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCUnionOfferList* pPacket, Player* pPlayer) ;

};

#endif
