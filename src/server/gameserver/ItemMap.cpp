////////////////////////////////////////////////////////////////////////////////
// Filename : ItemMap.h
// Written by : �輺��
// Description : 
// Ŭ���̾�Ʈ���� ������ ��Ʈ�� �������� ���̴�.
////////////////////////////////////////////////////////////////////////////////

#include "ItemMap.h"
#include "Inventory.h"
#include "Item.h"

#define TWO_BY_TWO_PACKING_SIZE 12

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
ItemMap::ItemMap() 
	throw()
{
	__BEGIN_TRY

	m_Num2x2     = 0;
	m_Num2x2Temp = 0;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// ������ ��ü ��ü�� ����⸦ ������ �ʴ´ٸ�,
// �ݵ�� clearAll()�� ȣ���� �Ŀ� �θ� ��.
////////////////////////////////////////////////////////////
ItemMap::~ItemMap()
	throw()
{
	__BEGIN_TRY

	clear();

	__END_CATCH
}

////////////////////////////////////////////////////////////
// ���� ������ ���� ����ϴ� 2x2 �������� ���� ����
////////////////////////////////////////////////////////////
void ItemMap::set2x2(int n) 
	throw()
{
	__BEGIN_TRY

	// 2x2 �������� 3���� ���� ���, 
	// �켱 ������ ���� ����. �׷��� 3�� ������
	// ���� ���� �������ش�.
	m_Num2x2 = n;
	m_Num2x2Temp = (n/3)*3;

	__END_CATCH
}

////////////////////////////////////////////////////////////
// �������� �ʿ��� ���Ѵ�.
////////////////////////////////////////////////////////////
bool ItemMap::addItem(Item* pItem)
	throw()
{
	__BEGIN_TRY

	ulonglong key = getKey(pItem);

	ITEM_MAP::const_iterator itr = find(key);
	
	if (itr == end()) // ������ �߰��Ѵ�.
	{
		insert(ITEM_MAP::value_type(key, pItem));
		return true;
	}

	return false;

	__END_CATCH
}


////////////////////////////////////////////////////////////
// �������� �����ϱ� ���� Ű�� �����.
//
// key�� 8 byte�̰� ����byte����..
//
// 4 Byte : gridWidth* gridHeight
// 4 Byte : ObjectID
//
// �� ǥ���ȴ�.
////////////////////////////////////////////////////////////
ulonglong ItemMap::getKey(Item* pItem)
	throw()
{
	__BEGIN_TRY

	ObjectID_t objectID   = pItem->getObjectID();
	int        gridWidth  = pItem->getVolumeWidth();
	int        gridHeight = pItem->getVolumeHeight();
	int        gridSize   = gridWidth* gridHeight;

	// 2x2 �������� �������� �켱������ ���� ���� ���ش�.
	if (gridSize == 4)
	{
		if (m_Num2x2Temp > 0)
		{
			m_Num2x2Temp--;
			gridSize = TWO_BY_TWO_PACKING_SIZE;
		}
	}

	gridSize = 0xFF - gridSize;

	ulonglong  key = gridSize;
	key = (key << 32) | objectID;

	return key;

	__END_CATCH
}

