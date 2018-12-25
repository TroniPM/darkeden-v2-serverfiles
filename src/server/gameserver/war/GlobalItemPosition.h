#ifndef __GLOBAL_ITEM_POSITION_H__
#define __GLOBAL_ITEM_POSITION_H__

#include "Types.h"
#include "Exception.h"

class Zone;
class Item;

class GlobalItemPosition
{
public:
	enum PositionType
	{
		POS_TYPE_ZONE,		// 0
		POS_TYPE_INVENTORY,	// 1
		POS_TYPE_MOUSE,		// 2
		POS_TYPE_CORPSE,	// 3
	};

protected:
	// �� Ŭ������ ���� ������ ���� ����.
	GlobalItemPosition( PositionType type ) : m_ItemPosType( type ) { }

public:
	virtual ~GlobalItemPosition(){ };

public:
	void			setType( PositionType type ) { m_ItemPosType = type; }
	PositionType	getType() const { return m_ItemPosType; }

public:
	// �������� �̾Ƴ���.
	virtual Item*	popItem( bool bLock = true ) throw(Error) = 0;
	virtual Zone*	getZone() throw(Error) = 0;

public:
	virtual string	toString() ;

private:
	PositionType	m_ItemPosType;
};

#endif // __GLOBAL_ITEM_POSITION_H__

