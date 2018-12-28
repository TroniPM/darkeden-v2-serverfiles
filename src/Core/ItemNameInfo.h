//--------------------------------------------------------------------------------
//
// Filename    : ItemNameInfo.h
// Written By  :
// Description :
//
//--------------------------------------------------------------------------------

#ifndef __ITEM_NAME_H__
#define __ITEM_NAME_H__

// include files
#include "Types.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "Exception.h"

//--------------------------------------------------------------------------------
//
// class ItemNameInfo;
//
//--------------------------------------------------------------------------------

class ItemNameInfo
{

public :
    ItemNameInfo() {}
    ItemNameInfo(ObjectID_t objectID, string name)
    {
        m_ObjectID = objectID;
        m_Name = name;
    }
    virtual ~ItemNameInfo() {}

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    virtual void read(SocketInputStream &iStream) ;

    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    virtual void write(SocketOutputStream &oStream) ;

    virtual PacketSize_t getSize() ;

    static PacketSize_t getMaxSize()
    {
        return (szObjectID + szBYTE + (szBYTE * 20));
    }

    // get packet's debug string
    string toString() ;

public:
    void setObjectID( ObjectID_t objectID )
    {
        m_ObjectID = objectID;
    }
    ObjectID_t getObjectID()
    {
        return m_ObjectID;
    }

    void setName( string name )
    {
        m_Name = name;
    }
    string getName()
    {
        return m_Name;
    }

protected :
    ObjectID_t		m_ObjectID;
    string			m_Name;
};

#endif
