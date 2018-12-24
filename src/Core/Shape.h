//////////////////////////////////////////////////////////////////////////////
// Filename    : Shape.h
// Written by  : excel96
// Description : 
// �α���ȭ�鿡�� �����̾��� �ܾ��� �����ִ� �� �ʿ��� �Լ���.
// ������ Ÿ�Կ� ���� �Ѹ�� ����� �����ϴ� �Լ����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Types.h"
#include "Exception.h"

BYTE getShoulderType(ItemType_t IType) throw();
PantsType getPantsType(ItemType_t IType) throw();
JacketType getJacketType(ItemType_t IType) throw();
HelmetType getHelmetType(ItemType_t IType) throw();
ShieldType getShieldType(ItemType_t IType) throw();
MotorcycleType getMotorcycleType(ItemType_t IType) throw();

// �����̾�
VampireCoatType getVampireCoatType(ItemType_t IType) throw();

// �ƿ콺�ͽ�
OustersCoatType getOustersCoatType(ItemType_t IType) throw();
OustersArmType getOustersArmType(ItemType_t IType) throw();

#endif
