//--------------------------------------------------------------------------------
// 
// Filename    : PacketFactoryManager.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "Assert.h"
#include "PacketFactoryManager.h"
#include "StringStream.h"

#include "TOpackets/GTOAcknowledgement.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
PacketFactoryManager::PacketFactoryManager () 
	throw ()
: m_Factories(NULL) , m_Size(Packet::PACKET_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// ��Ŷ���丮�迭�� �����Ѵ�.
	m_Factories = new PacketFactory*[ m_Size ];
	
	// ���丮�� ���� �����͵��� NULL �� �ʱ�ȭ�Ѵ�.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
			
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
PacketFactoryManager::~PacketFactoryManager () 
	throw ()
{
	__BEGIN_TRY
		
	Assert(m_Factories != NULL);

	// ������ ��Ŷ���丮���� �����Ѵ�.
	for (int i = 0 ; i < m_Size ; i ++) 
	{
#ifdef __GAME_CLIENT__
		if (m_Factories[i] != NULL)
		{
			delete m_Factories[i];
			m_Factories[i] = NULL;
		}
#else
		SAFE_DELETE(m_Factories[i]);
#endif
	}
	
	// ��Ŷ���丮�迭�� �����Ѵ�.
#ifdef __GAME_CLIENT__
	if (m_Factories != NULL)
	{
		delete [] m_Factories;
		m_Factories = NULL;
	}
#else
	SAFE_DELETE_ARRAY(m_Factories);
#endif
			
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ���ǵ� ��� ��Ŷ���丮���� ���⿡ �߰��Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void PacketFactoryManager::init ()
	 
{
	__BEGIN_TRY
		
	addFactory( new GTOAcknowledgementFactory() );

#if __OUTPUT_INIT__
	cout << toString() << endl;
#endif
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// ���丮 ��ü�� Ư�� �ε����� �߰��Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void PacketFactoryManager::addFactory (PacketFactory * pFactory) 
	 
{
	__BEGIN_TRY
		
	if (m_Factories[ pFactory->getPacketID() ] != NULL) {
		StringStream msg;
#ifdef __GAME_CLIENT__
	#ifdef __DEBUG_OUTPUT__
		msg << "duplicate packet factories, " << pFactory->getPacketName() ;
	#else	
		msg << "duplicate packet factories ";
	#endif
#else
		msg << "duplicate packet factories, " << pFactory->getPacketName() ;
#endif
		throw Error(msg.toString());
	}
	
	// ��Ŷ���丮�� ����Ѵ�.
	m_Factories[ pFactory->getPacketID() ] = pFactory;
			
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
//
// ��Ŷ���̵�� ��Ŷ��ü�� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
Packet * PacketFactoryManager::createPacket (PacketID_t packetID) 
	   throw (InvalidProtocolException , Error)
{
	__BEGIN_TRY

	// ��Ŷ ���̵� ������ �Ѿ���� ���ؼ� Seg.Fault �� �߻����� �ʵ���.
	// �̷� ����ڴ� ���� ©��� �Ѵ�.
	if (packetID >= m_Size || m_Factories[packetID] == NULL) {
		StringStream msg;
		msg << "packet factory [" << packetID << "] not exist.";
		throw InvalidProtocolException(msg.toString());
	}

	return m_Factories[packetID]->createPacket();
			
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ��Ŷ���̵�� Ư�� ��Ŷ�� �ִ� ũ�⸦ �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
PacketSize_t PacketFactoryManager::getPacketMaxSize (PacketID_t packetID) 
	   throw (InvalidProtocolException , Error)
{
	__BEGIN_TRY

	// ��Ŷ ���̵� ������ �Ѿ���� ���ؼ� Seg.Fault �� �߻����� �ʵ���.
	// �̷� ����ڴ� ���� ©��� �Ѵ�.
	if (packetID >= m_Size || m_Factories[packetID] == NULL) {
		StringStream msg;
		msg << "invalid packet id(" << packetID << ")";
		throw InvalidProtocolException(msg.toString());
	}

	return m_Factories[packetID]->getPacketMaxSize();
			
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ��Ŷ���̵�� Ư�� ��Ŷ�� �̸��� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__GAME_CLIENT__) || defined(__GAME_CLIENT__) && defined(__DEBUG_OUTPUT__)
string PacketFactoryManager::getPacketName (PacketID_t packetID) 
	   throw (InvalidProtocolException , Error)
{
	__BEGIN_TRY

	// ��Ŷ ���̵� ������ �Ѿ���� ���ؼ� Seg.Fault �� �߻����� �ʵ���.
	// �̷� ����ڴ� ���� ©��� �Ѵ�.
	if (packetID >= m_Size || m_Factories[packetID] == NULL) {
		StringStream msg;
		msg << "invalid packet id(" << packetID << ")";
		throw InvalidProtocolException(msg.toString());
	}

	return m_Factories[packetID]->getPacketName();
			
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string PacketFactoryManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "PacketFactoryManager(\n";

	for (int i = 0 ; i < m_Size ; i ++)
		msg << "PacketFactories[" << i << "] == " << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getPacketName()) << "\n";

	msg << ")";

	return msg.toString();

	__END_CATCH
}
#endif

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////

PacketFactoryManager * g_pPacketFactoryManager = NULL;
