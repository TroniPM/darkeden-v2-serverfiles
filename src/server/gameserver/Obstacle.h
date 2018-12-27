//////////////////////////////////////////////////////////////////////////////
// Filename    : Obstacle.h
// Written by  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Object.h"

//////////////////////////////////////////////////////////////////////////////
// Obstacle Type
//
// �� ���� ��ֹ� �������� �ִ� 256 ������ �����Ѵ�.
//(���̳� ����ġ, ������ 256���� �Ѿ �� ������?)
//////////////////////////////////////////////////////////////////////////////
typedef BYTE ObstacleType_t;
const uint szObstacleType = sizeof(ObstacleType_t);

//////////////////////////////////////////////////////////////////////////////
// class Obstacle;
//
// Ÿ�Ͽ� ���ӵǴ� ��ü�μ�,  ũ��ó�� �̵��� �����ϸ鼭 ���¸� ����
// �ִ� Object�� ���� Ŭ���� ��ü�̴�. ���̳� ����, ����ġ ���� �͵���
// ���⿡ ���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class Obstacle : public Object 
{
public:
	enum ObstacleClass 
	{
		OBSTACLE_CLASS_DOOR ,
		OBSTACLE_CLASS_SWITCH ,
		OBSTACLE_CLASS_TRAP
	};

public:
	Obstacle(ObjectID_t objectID)  : Object(objectID) {}
	virtual ~Obstacle()  {}
	
// methods from Object
public:
	virtual ObjectClass getObjectClass()  { return OBJECT_CLASS_OBSTACLE; }
	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_OBSTACLE; }
	virtual string toString()  = 0;

// own methods
public:
	virtual ObstacleClass getObstacleClass()  = 0;
	virtual ObstacleType_t getObstacleType()  = 0;
};

#endif
