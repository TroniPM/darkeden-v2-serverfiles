////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWanderZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionWanderZone.h"
#include "Creature.h"
#include "NPC.h"
#include "Utility.h"

static const POINT d [] = {
    POINT(-1, 0),   // 0 == LEFT
    POINT(-1, 1),   // 1 == LEFTDOWN
    POINT(0, 1),   // 2 == DOWN
    POINT(1, 1),   // 3 == RIGHTDOWN
    POINT(1, 0),   // 4 == RIGHT
    POINT(1,-1),   // 5 == RIGHTUP
    POINT(0,-1),   // 6 == UP
    POINT(-1,-1),   // 7 == LEFTUP
};


////////////////////////////////////////////////////////////////////////////////
// read from PropertyBuffer
////////////////////////////////////////////////////////////////////////////////
void ActionWanderZone::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try
	{
		m_MovePercentage = propertyBuffer.getPropertyInt("MovePercentage");

		Assert(m_MovePercentage <= 100);
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionWanderZone::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 == NULL);

	Assert(pCreature1->isNPC() || pCreature1->isMonster());

	Zone * pZone = pCreature1->getZone();
	Assert( pZone != NULL );

	const int left = 5;
	const int top = 5;
	const int right = pZone->getWidth() - 5;
	const int bottom = pZone->getHeight() - 5;

	// �̹� �Ͽ� ������ ������ üũ�Ѵ�.
	uint diceResult = Dice(1,100);
	
	if (diceResult < m_MovePercentage)
	{
		bool        movableDir[8];
		uint        movableDirCount = 0;
		ZoneCoord_t cx = pCreature1->getX();
		ZoneCoord_t cy = pCreature1->getY();
		ZoneCoord_t nx = 0;
		ZoneCoord_t ny = 0;

		// �����̱�� �ߴٸ�, ��� �������� ������ ������ üũ�Ѵ�.
		// �ϴ� �� �� �ִ� ������ ��Ϻ��� �ۼ��Ѵ�.
		for (uint i = 0 ; i < 8 ; i ++)
		{
			nx = cx + d[i].x;
			ny = cy + d[i].y;

			// ���� ���� ������ (x,y,r) ���� �ȿ� �����ϸ鼭,
			// NPC�� ������ �� �ִ� - ������� ���� - Ÿ���̾�� �Ѵ�.
			if (pCreature1->canMove(nx,ny)
				&& ( nx >= left && nx <= right )
				&& ( ny >= top && ny <= bottom ) )
			{
				movableDir[i] = true;
				movableDirCount++;
			}
			else
			{
				movableDir[i] = false;
			}
		}

		// ���� ���� ��ġ���� ������ �� ���ٸ�, �����Ѵ�.
		// ������ �� �ִٸ�.. �����δ�.
		if (movableDirCount > 0)
		{
			Dir_t nextDir = pCreature1->getDir();
			bool changeDir = false;

			if ( movableDir[nextDir] )
			{
				if ( rand() % 10 == 0 ) changeDir = true;
			}
			else
			{
				changeDir = true;
			}

			if ( changeDir )
			{
				uint j = rand() % movableDirCount + 1;

				uint k = 0;	// movableDir[l] == true �� ������ �ε���
				for (uint l = 0 ; l < 8 ; l ++)
				{
					if (movableDir[l] && ++k == j)
					{
						nextDir = l;
						break;
					}
				}
			}

			nx = cx + d[nextDir].x;
			ny = cy + d[nextDir].y;
			// move creature
			pZone->moveCreature(pCreature1 , nx , ny , nextDir);
		}
		
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionWanderZone::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionWanderZone("
		<< "MovePercentage:" << (int)m_MovePercentage
		<< ")";

	return msg.toString();

	__END_CATCH
}
