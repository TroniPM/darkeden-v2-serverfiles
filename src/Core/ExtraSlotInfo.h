//////////////////////////////////////////////////////////////////////////////
// Filename    : ExtraSlotInfo.h
// Written By  : elca
// Description :
// �÷��̾��� ���콺�� �޷��ִ� �����ۿ� ���� ������ ������ ���۵Ǵ�
// ��Ŷ�̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EXTRA_SLOT_INFO_H__
#define __EXTRA_SLOT_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "PCItemInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class ExtraSlotInfo
//////////////////////////////////////////////////////////////////////////////

class ExtraSlotInfo : public PCItemInfo 
{
public:
	ExtraSlotInfo();
	virtual ~ExtraSlotInfo();

public:
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	string toString () const throw ();
};

#endif
