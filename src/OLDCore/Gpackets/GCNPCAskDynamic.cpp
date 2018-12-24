//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCAskDynamic.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCNPCAskDynamic.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCNPCAskDynamic::GCNPCAskDynamic() 
	throw ()
{
	__BEGIN_TRY 

	m_ContentsCount = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCNPCAskDynamic::~GCNPCAskDynamic() 
	throw ()
{
	__BEGIN_TRY 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskDynamic::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	WORD size = 0;
		
	iStream.read( m_ObjectID );
	iStream.read( m_ScriptID );

	iStream.read( size );
	if (size == 0) throw InvalidProtocolException("subject size == 0");
	iStream.read( m_Subject , size );

	// read countents count
	iStream.read(m_ContentsCount);

	for (int i=0; i<m_ContentsCount; i++)
	{
		// ���ڿ� ���̸� �о���δ�.
		iStream.read(size);

		// ������ �ִ� ���ڿ��̶�� ���� ��ü�� �о���δ�.
		if (size > 0)
		{
			string msg = "";
			iStream.read(msg, size);
			m_Contents.push_back(msg);
		}
	}
	
	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskDynamic::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	WORD size = 0;

	oStream.write( m_ObjectID );
	oStream.write( m_ScriptID );
	
	size = m_Subject.size();
	if (size == 0) throw InvalidProtocolException("subject size == 0");
	oStream.write( size );
	oStream.write( m_Subject );

	oStream.write( m_ContentsCount );

	list<string>::const_iterator itr = m_Contents.begin();

	for (; itr != m_Contents.end(); itr++)
	{
		// ���ڿ��� ���̸� �����Ѵ�.
		size = (*itr).size();
		oStream.write(size);

		// ������ �ִ� ���ڿ��̶�� ���ڿ� ��ü�� �����Ѵ�.
		if (size > 0) oStream.write(*itr);
	}
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskDynamic::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCNPCAskDynamicHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCNPCAskDynamic::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	int          i = 0;
	
	msg << "GCNPCAskDynamic("
		<< "ObjectID:" << m_ObjectID 
		<< ",ScriptID: " << m_ScriptID
		<< ",Subject:" << m_Subject;

	list<string>::const_iterator itr = m_Contents.begin();
	for (; itr != m_Contents.end(); itr++)
	{
		msg << ",Contents[" << i++ << "]:" << *itr;
	}
	msg << ")" ;
	
	return msg.toString();
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void GCNPCAskDynamic::addContent(string content)
	throw()
{
	__BEGIN_TRY

	m_Contents.push_back(content);
	m_ContentsCount++;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string GCNPCAskDynamic::popContent(void)
	throw()
{
	__BEGIN_TRY

	string rValue = m_Contents.front();
	m_Contents.pop_front();
	m_ContentsCount--;
	return rValue;

	__END_CATCH
}
