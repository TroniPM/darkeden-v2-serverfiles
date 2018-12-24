//////////////////////////////////////////////////////////////////////////////
// Filename    : Shape.cpp
// Written by  : excel96
// Description : 
// 로그인 화면에서 슬레이어의 외양을 보여주는 데 필요한 함수들.
// 아이템 타입에 따른 겉모습 상수를 리턴하는 함수들이다.
//////////////////////////////////////////////////////////////////////////////

#include "Shape.h"

BYTE getShoulderType(ItemType_t IType)
	throw()
{
	return 1;
}

PantsType getPantsType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return PANTS1;
		case 4:
		case 5:
		case 6:
		case 7:
			return PANTS2;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		default:
//			throw ("getPantsType() : unknown pants type");
			return PANTS3;
			break;
	}

	return PANTS_BASIC;
}

JacketType getJacketType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
			return JACKET_BASIC;
		case 28:
		case 29:
			return JACKET1;
		case 30:
		case 31:
			return JACKET2;
		case 32:
		case 33:
			return JACKET3;
		case 34:	
		case 35:
			return JACKET4;
		case 36:
		case 37:
			return JACKET5;
		case 38:
		case 39:
			return JACKET6;
		default:
			return JACKET_BASIC;
			break;
	}

	return JACKET_BASIC;
}

HelmetType getHelmetType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
			return HELMET1;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		default:
			return HELMET2;
			break;
	}

	return HELMET_NONE;
}

ShieldType getShieldType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			return SHIELD1;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		default:
//			throw ("getShieldType() : unknown shield type");
			return SHIELD2;
			break;
	}

	return SHIELD_NONE;
}

VampireCoatType getVampireCoatType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			return VAMPIRE_COAT_BASIC;
			break;
		case 24:
		case 25:
			return VAMPIRE_COAT1;
			break;
		case 26:
		case 27:
			return VAMPIRE_COAT2;
			break;
		case 28:
		case 29:
			return VAMPIRE_COAT3;
			break;
		case 30:
		case 31:
			return VAMPIRE_COAT4;
			break;
		case 32:
		case 33:
			return VAMPIRE_COAT5;
			break;
		case 34:
		case 35:
			return VAMPIRE_COAT6;
			break;
		default:
			return VAMPIRE_COAT3;
			break;
	}

	return VAMPIRE_COAT_BASIC;
}

MotorcycleType getMotorcycleType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 6:
			return MOTORCYCLE2;
			break;
		case 7:
			return MOTORCYCLE3;
			break;
		case 8:
			return MOTORCYCLE4;
			break;
		case 9:
			return MOTORCYCLE5;
			break;
		case 0:
		case 5:
		default:
			return MOTORCYCLE1;
			break;
	}

	return MOTORCYCLE_NONE;
}

OustersCoatType getOustersCoatType(ItemType_t IType)
	throw()
{
	switch ( IType )
	{
		case 0:
		case 1:
		case 2:
			return OUSTERS_COAT1;
		case 3:
		case 4:
		case 5:
			return OUSTERS_COAT2;
		case 6:
		case 7:
		case 8:
		case 9:
			return OUSTERS_COAT_BASIC;
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			return OUSTERS_COAT4;
		case 18:
			return OUSTERS_COAT5;
		case 19:
			return OUSTERS_COAT6;
		default:
			return OUSTERS_COAT3;
	}

	return OUSTERS_COAT_BASIC;
}

OustersArmType getOustersArmType(ItemType_t IType)
	throw()
{
	switch ( IType )
	{
		case 0:
			return OUSTERS_ARM_GAUNTLET;
	}

	return OUSTERS_ARM_GAUNTLET;
}

