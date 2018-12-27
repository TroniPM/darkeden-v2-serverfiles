//////////////////////////////////////////////////////////////////////////////
// Filename    : RideMotorcycleSlotInfo.h
// Written By  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __RIDE_MOTORCYCLE_SLOT_INFO_H__
#define __RIDE_MOTORCYCLE_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// RideMotorcycle ������ ��� �ִ� ��ü.
/////////////////////////////////////////////////////////////////////////////

class RideMotorcycleSlotInfo : public PCItemInfo
{
public:
    void read (SocketInputStream &iStream);
    void write (SocketOutputStream &oStream) ;

    uint getSize ()
    {
        return PCItemInfo::getSize() + szCoordInven * 2;
    }

    static uint getMaxSize ()
    {
        return PCItemInfo::getMaxSize() + szCoordInven * 2;
    }

    string toString () ;

public:
    void setInvenX(CoordInven_t InvenX)
    {
        m_InvenX = InvenX;
    }
    CoordInven_t getInvenX()
    {
        return m_InvenX;
    }

    void setInvenY(CoordInven_t InvenY)
    {
        m_InvenY = InvenY;
    }
    CoordInven_t getInvenY()
    {
        return m_InvenY;
    }

private:
    CoordInven_t m_InvenX;
    CoordInven_t m_InvenY;

};

#endif
