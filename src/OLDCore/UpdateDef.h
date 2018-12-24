//--------------------------------------------------------------------------------
//
// Filename   : UpdateDef.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __UPDATE_DEF_H__
#define __UPDATE_DEF_H__

#include "Types.h"

//--------------------------------------------------------------------------------
//
// Smart Update ���� Ŭ�������� ����ϴ� ���� ������ Ÿ�԰� �� ũ��, limit ����
//
//--------------------------------------------------------------------------------

typedef DWORD FileSize_t;
const uint szFileSize = sizeof(FileSize_t);

typedef BYTE FilenameLen_t;
const uint szFilenameLen = sizeof(FilenameLen_t);
const uint maxFilename = 256;

// version
typedef WORD Version_t;
const uint szVersion = sizeof(Version_t);

// �Ķ���� ���� Ÿ��
typedef WORD ParameterLen_t;
const uint szParameterLen = sizeof(ParameterLen_t);

// �Ķ������ �ִ� ����
const uint maxParams = 6;

// max parameter length
// �ִ� ���̴� �����̸��� ����(256) + ���ϻ�����(15�ڸ�����)�̴�.
const uint maxParameterLen = 256 + 15;

#endif
