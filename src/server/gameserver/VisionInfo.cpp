////////////////////////////////////////////////////////////////////////////////
// Filename    : Vision.cpp
// Written By  : Reiot
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "VisionInfo.h"
#include "Assert.h"
#include "LogClient.h"

////////////////////////////////////////////////////////////////////////////////
// global variable definition
////////////////////////////////////////////////////////////////////////////////
VisionInfoManager* g_pVisionInfoManager = NULL;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
VisionInfo::VisionInfo (Sight_t sight , Dir_t dir) 
	
{
	__BEGIN_TRY

	m_Sight = sight;
	m_Dir   = dir;

	// �ӽ� �þ� ����
	VisionState temp1[maxVisionWidth][maxVisionHeight];
	VisionState temp2[maxVisionWidth][maxVisionHeight];

	//--------------------------------------------------------------------------------
	// temp1, temp2, m_Rect �� ��� OUT_OF_SIGHT�� �ʱ�ȭ�Ѵ�.
	//--------------------------------------------------------------------------------
	for (int x = 0 ; x < maxVisionWidth ; x ++) {
		for (int y = 0 ; y < maxVisionHeight ; y ++) {
			m_Rect[x][y] = temp1[x][y] = temp2[x][y] = OUT_OF_SIGHT;
		}
	}

	// �߽����� (10,11)�� �ȴ�.
//	int cx = maxViewportWidth + 1;
//	int cy = maxViewportUpperHeight + 1;
	int cx = maxViewportWidth;
	int cy = maxViewportUpperHeight;

	int startx = max(0 , cx - m_Sight);
	int starty = max(0 , cy - m_Sight);
	int endx   = min(maxVisionWidth - 1 , cx + m_Sight);
	int endy   = min(maxVisionHeight - 1 , cy + m_Sight);

	//--------------------------------------------------------------------------------
	// m_Rect �� IN_SIGHT, OUT_OF_SIGHT ������ �����Ѵ�.
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			if (x >= startx && x <= endx && y >= starty && y <= endy) {
				int dist = abs(cx - x) + abs(cy - y);
				if (dist <= m_Sight + (m_Sight >> 1)) {
					m_Rect[x][y] = IN_SIGHT;
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	// temp1 = m_Rect << 1
	//--------------------------------------------------------------------------------
	int dx = 0, dy = 0;

	switch (m_Dir) {
		case LEFT : dx--; break;
		case LEFTDOWN : dx--; dy++; break;
		case DOWN : dy++; break;
		case RIGHTDOWN : dx++; dy++; break;
		case RIGHT : dx++; break;
		case RIGHTUP : dx++; dy--; break;
		case UP : dy--; break;
		case LEFTUP : dx--; dy--; break;
	}

	// ���۰� ����ǥ�� �����϶�. m_Rect �� �����̴�.
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			temp1[x+dx][y+dy] = m_Rect[x][y];
		}
	}

	//--------------------------------------------------------------------------------
	// temp1 = temp1 - m_Rect
	//--------------------------------------------------------------------------------
	for (int x = 0 ; x < maxVisionWidth ; x ++) {
		for (int y = 0 ; y < maxVisionHeight ; y ++) {
			if (temp1[x][y] == m_Rect[x][y] == IN_SIGHT)
				temp1[x][y] = OUT_OF_SIGHT;
		}
	}
	
	//--------------------------------------------------------------------------------
	// temp2 = temp1 >> 1
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			temp2[x][y] = temp1[x+dx][y+dy];
		}
	}

	//--------------------------------------------------------------------------------
	// m_Rect�� ON_SIGHT ������ �����Ѵ�.
	//
	// IN_SIGHT �����߿���, 8������ üũ�ؼ� 1�� �̻��� OUT_OF_SIGHT �� ������ ���
	// ON_SIGHT �� �����Ѵ�.
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			if (m_Rect[x][y] == IN_SIGHT) {
				if (m_Rect[ x ][y-1] == OUT_OF_SIGHT ||	// north
					 m_Rect[x+1][y-1] == OUT_OF_SIGHT || 	// northeast
					 m_Rect[x+1][ y ] == OUT_OF_SIGHT || 	// east
					 m_Rect[x+1][y+1] == OUT_OF_SIGHT || 	// southeast
					 m_Rect[ x ][y+1] == OUT_OF_SIGHT || 	// south
					 m_Rect[x-1][y+1] == OUT_OF_SIGHT || 	// southwest
					 m_Rect[x-1][ y ] == OUT_OF_SIGHT || 	// west
					 m_Rect[x-1][y-1] == OUT_OF_SIGHT) { 	// northwest
					m_Rect[x][y] = ON_SIGHT;
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	// m_Rect = m_Rect + temp2
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			if (temp2[x][y] == IN_SIGHT) {
				Assert(m_Rect[x][y] == ON_SIGHT);
				m_Rect[x][y] = NEW_SIGHT;
			}
		}
	}
	
	if ( sight == 13 ) filelog("VisionInfo.log", "%s", toString().c_str());

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// Q(cx,cy)�� �ִ� ũ��ó�� P(x,y)�� �� �� �ִ���, ������.. �� ���°��� ������.
//
// O(a,b)   - Vision Rectangle �� �߽�
// P(x,y)   - ������ �ϴ� ������Ʈ�� ��ġ
// Q(cx,cy) - ���� ũ��ó�� ��ġ
//
// Q�� O�� �����̵��� ������ ����ؼ�, P�� �����̵��� ��ǥ�� P'(x',y') �̶�� �� ��, 
//
//		x' = x + a - cx
//		y' = y + b - cy
//
// �� �ȴ�. �׷���, m_Rect[x'][y']�� ���� �����ϸ� �ȴ�. (�翬�� ����üũ�� �ؾ���)
//
//--------------------------------------------------------------------------------

VisionState VisionInfo::getVisionState (ZoneCoord_t cx , ZoneCoord_t cy , ZoneCoord_t x , ZoneCoord_t y) const
	
{
	__BEGIN_TRY

	int px = x + (maxViewportWidth + 1) - cx;
	int py = y + (maxViewportUpperHeight + 1) - cy;

	// �����̵��� ��ǥ�� ������ üũ�Ѵ�.
	if (px >= 0 && px < maxVisionWidth && py >= 0 && py < maxVisionHeight)
		return m_Rect[px][py];

	return OUT_OF_SIGHT;

	__END_CATCH
}



//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VisionInfo::toString () const
	
{

	__BEGIN_TRY

	StringStream msg;

	msg << "VisionInfo("
			<< "Sight:" << (int)m_Sight
			<< ",Dir: " << Dir2String[m_Dir]
			<< "\r\n";

	for (int y = 0; y < maxVisionHeight ; y++) 
	{
		for (int x = 0; x < maxVisionWidth ; x++)
	 	{
			switch (m_Rect[x][y]) 
			{
				case OUT_OF_SIGHT:  msg << ". ";           break;
				case IN_SIGHT:      msg << "[33m:[m "; break;
				case ON_SIGHT:      msg << "[33m#[m "; break;
			 	case NEW_SIGHT:     msg << "[32m#[m "; break;
			}
		}

		msg << "\r\n";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
*/
//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
VisionInfoManager::~VisionInfoManager () 
	
{

	__BEGIN_TRY

/*	if (m_pVisionInfos)
	{
		for (Sight_t sight = 0 ; sight <= maxSight ; sight ++) 
		{
			if (m_pVisionInfos[sight])
			{
				for (Dir_t dir = 0 ; dir < DIR_MAX ; dir ++) 
				{
					SAFE_DELETE(m_pVisionInfos[sight][dir]);
				}

				SAFE_DELETE_ARRAY(m_pVisionInfos[sight]);
			}
		}

		SAFE_DELETE_ARRAY(m_pVisionInfos);
	}*/

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void VisionInfoManager::init () 
	
{

	__BEGIN_TRY

/*	m_pVisionInfos = new VisionInfo ** [ maxSight ];
	Assert(m_pVisionInfos != NULL);

	for (Sight_t sight = 0 ; sight <= maxSight ; sight ++) 
	{
		m_pVisionInfos[sight] = new VisionInfo* [8];
		Assert(m_pVisionInfos[sight] != NULL);

		for (Dir_t dir = 0 ; dir < DIR_MAX ; dir ++) 
		{
			m_pVisionInfos[sight][dir] = new VisionInfo(sight,dir);
			Assert(m_pVisionInfos[sight][dir] != NULL);
		}
	}	*/

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get vision info
//--------------------------------------------------------------------------------
/*
VisionInfo* VisionInfoManager::getVisionInfo (Sight_t sight , Dir_t dir) 
	throw (OutOfBoundException)
{
	__BEGIN_TRY

	if (sight > maxSight) throw OutOfBoundException("sight overflow");

	if (dir >= DIR_MAX) throw OutOfBoundException("dir overflow");

	return m_pVisionInfos[sight][dir];

	__END_CATCH
}
*/


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VisionInfoManager::toString () const
	
{
	__BEGIN_TRY

/*	StringStream msg;

	msg << "VisionInfoManager(";

	for (Sight_t sight = 0 ; sight <= maxSight ; sight ++)
 	{
		for (Dir_t dir = LEFT ; dir <= LEFTUP ; dir ++) 
		{
			msg << m_pVisionInfos[sight][dir]->toString();
		}
	}

	msg << ")";

	return msg.toString();*/

	__END_CATCH
}

