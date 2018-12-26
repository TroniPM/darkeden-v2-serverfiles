////////////////////////////////////////////////////////////////////////////////
// Filename    : VisionInfo.h
// Written By  : Reiot
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VISIONINFO_H__
#define __VISIONINFO_H__

#include "Types.h"
#include "Exception.h"

const Coord_t maxViewportWidth  = 10;
const Coord_t maxViewportUpperHeight = 14;
const Coord_t maxViewportLowerHeight = 14;
const Coord_t maxVisionWidth = maxViewportWidth * 2 + 1;
const Coord_t maxVisionHeight = maxViewportUpperHeight + maxViewportLowerHeight + 1;

////////////////////////////////////////////////////////////////////////////////
// class VisionInfo;
// P(x,y) �� �þ� ������ Sight �̸�, Ư�� ����(dir)�� �ٶ󺸴� O(cx,cy) ��ġ�� 
// ũ��ó�� �� �� �ִ����� ���θ� ��Ÿ�ӿ� ������� �ʰ�, �̹� ���� ���� �þ� 
// ������ ���⺰ �þ� �簢���� �����صθ� �þ� üũ�� ���� ���� �� �� �ְ� �ȴ�.
// �� Ŭ������, �� �� ���Ǵ� �þ� �簢���� ��Ÿ����.
////////////////////////////////////////////////////////////////////////////////

/*class VisionInfo 
{
public:
	VisionState getVisionState(ZoneCoord_t cx, ZoneCoord_t cy, ZoneCoord_t x, ZoneCoord_t y) 
	{
		// inline for speed. by sigi. 2002.11.8
//		int px = x + (maxViewportWidth + 1) - cx;
//		int py = y + (maxViewportUpperHeight + 1) - cy;
		int px = x + (maxViewportWidth) - cx;
		int py = y + (maxViewportUpperHeight) - cy;

		// �����̵��� ��ǥ�� ������ üũ�Ѵ�.
		if (px >= 0 && px < maxVisionWidth && py >= 0 && py < maxVisionHeight)
			return m_Rect[px][py];

		return OUT_OF_SIGHT;
	}
	string toString() ;
		
private:
	// �þ� ����(0 - 13)
	Sight_t m_Sight;

	// �ٶ󺸴� ����
	Dir_t m_Dir;

	// viewport rectangle
	VisionState m_Rect[maxVisionWidth][maxVisionHeight];
	// deprecated. �� Ŭ������ ���̻� �� ����.
	VisionInfo(Sight_t sight, Dir_t dir) ;
	~VisionInfo();
};
*/

////////////////////////////////////////////////////////////////////////////////
// class VisionInfoManager;
// �þ� ������ �����ϸ�, �þ� ������ ������ �ָ� �׿� �ش��ϴ� �þ� ������ �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////

class VisionInfoManager 
{
public:
	VisionInfoManager() throw() {}
	~VisionInfoManager() ;

public:

	// init vision info
	void init() ;

	// get vision info
/*	VisionInfo* getVisionInfo(Sight_t sight, Dir_t dir) //throw(OutOfBoundException)
	{
		// for speed. by sigi. 2002.11.8
		//__BEGIN_TRY
		//if (sight > maxSight) throw OutOfBoundException("sight overflow");
		//if (dir >= DIR_MAX) throw OutOfBoundException("dir overflow");

		return m_pVisionInfos[sight][dir];

		//__END_CATCH
	}*/

	static VisionState getVisionState( ZoneCoord_t SourceX, ZoneCoord_t SourceY, ZoneCoord_t TargetX, ZoneCoord_t TargetY )
	{
		int diffX = abs( TargetX-SourceX );
		int diffY = (int)TargetY-(int)SourceY;

		bool isInX = diffX <= maxViewportWidth;
		bool isInY = (diffY<0)?
			((-diffY)<=maxViewportUpperHeight):
			(diffY<=maxViewportLowerHeight);

		return (isInX&&isInY)?IN_SIGHT:OUT_OF_SIGHT;
	}

	// get debug string
	string toString() ;

private:

	// VisionInfo�� ������ �迭
//	VisionInfo *** m_pVisionInfos;

};

// global variable declaration
extern VisionInfoManager* g_pVisionInfoManager;

#endif

