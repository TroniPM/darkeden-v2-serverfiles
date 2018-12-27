//-------------------------------------------------------------------------------- // 
// Filename    : GCNPCInfo.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//--------------------------------------------------------------------------------

// include files
#include "GCNPCInfo.h"
#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "Assert.h"

// for client.. by sigi
#ifndef SAFE_DELETE
	#define SAFE_DELETE(p)	if (p!=NULL) { delete p; p=NULL; }
#endif

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
GCNPCInfo::GCNPCInfo ()
	
{
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
GCNPCInfo::~GCNPCInfo ()
	
{
#ifdef __GAME_CLIENT__
	list<NPCInfo*>::iterator itr = m_NPCInfos.begin();
	for (; itr != m_NPCInfos.end(); itr++)
	{
		NPCInfo* pInfo = *itr;
		SAFE_DELETE(pInfo);
	}
#else

	m_NPCInfos.clear();
#endif
}

//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void GCNPCInfo::read ( SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY
		
	//////////////////////////////////////////////////
	// read npc info
	//////////////////////////////////////////////////
	BYTE NPCInfoCount = 0;
	iStream.read(NPCInfoCount);
	for (BYTE nc=0; nc<NPCInfoCount; nc++)
	{
		NPCInfo* pInfo = new NPCInfo;
		pInfo->read(iStream);
		addNPCInfo(pInfo);
	}

	__END_CATCH
}

		    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void GCNPCInfo::write ( SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY

	//////////////////////////////////////////////////
	// write npc info
	//////////////////////////////////////////////////
	BYTE NPCInfoCount = m_NPCInfos.size();
	oStream.write(NPCInfoCount);

	list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
	for (; itr != m_NPCInfos.end(); itr++)
	{
		NPCInfo* pInfo = *itr;
		pInfo->write(oStream);
	}
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void GCNPCInfo::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	GCNPCInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
string GCNPCInfo::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCNPCInfo("
		<< "NPCInfos:";

	list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
	for (; itr != m_NPCInfos.end(); itr++)
	{
		NPCInfo* pInfo = *itr;
		msg << pInfo->toString();
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
