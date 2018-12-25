//////////////////////////////////////////////////////////////////////
// 
// Filename    : WorldInfo.h 
// Written By  : elca@ewestsoft.com
// Description : �κ��丮 �������� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __WORLD_INFO_H__
#define __WORLD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class WorldInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class WorldInfo {

public :
	
	// constructor
	WorldInfo () throw ();
	
	// destructor
	~WorldInfo () throw ();

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return (szBYTE + szBYTE + 20 + szBYTE)* 37;
	}

	// get packet's debug string
	string toString () const throw ();

	// get / set ID
	BYTE getID()  { return m_ID; }
	void setID(WorldID_t ID) throw() { m_ID = ID; }

	// get / set Name
	string getName()  { return m_Name; }
	void setName(string Name) throw() { m_Name = Name; }

	// get / set  Stat
	BYTE getStat()  { return m_Stat; }
	void setStat(BYTE Stat) throw() { m_Stat = Stat; }

private :

	// �׷� ���̵�
	WorldID_t m_ID;

	// �׷� �̸�
	string m_Name;

	// �׷��� ����
	BYTE	m_Stat;

};

#endif
