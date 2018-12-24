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
	Obstacle(ObjectID_t objectID) throw() : Object(objectID) {}
	virtual ~Obstacle() throw() {}
	
// methods from Object
public:
	virtual ObjectClass getObjectClass() const throw() { return OBJECT_CLASS_OBSTACLE; }
	virtual ObjectPriority getObjectPriority() const throw(Error) { return OBJECT_PRIORITY_OBSTACLE; }
	virtual string toString() const throw() = 0;

// own methods
public:
	virtual ObstacleClass getObstacleClass() const throw() = 0;
	virtual ObstacleType_t getObstacleType() const throw() = 0;
};

#endif
