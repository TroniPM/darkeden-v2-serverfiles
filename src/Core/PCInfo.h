//----------------------------------------------------------------------
//
// Filename    : PCInfo.h
// Writen By   : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PC_INFO_H__
#define __PC_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//----------------------------------------------------------------------
//
// class PCInfo;
//
// LCPCList ��Ŷ�� ��ܼ� ���ƿ��� SlayerPCInfo, VampirePCInfo Ŭ������ ���̽�
// Ŭ�����̴�. LCPCList ��Ŷ���� PCInfo* [3] �� ����Ǹ�, DB ���� ĳ������
// ���ڿ� ����, ���⿡ ���� SlayerPCInfo, VampirePCInfo �Ǵ� NULL �� ����
// �ȴ�.
//
//----------------------------------------------------------------------

class PCInfo {

public :

	// destructor
	virtual ~PCInfo () {}	

	// ���� �ν��Ͻ��� �����̾����� �����̾�����..
	virtual PCType getPCType ()  = 0;	

	//----------------------------------------------------------------------
	// ��Ŷ�� embedding �Ƿ��� ��ü�� �Ʒ��� ���� ����Ÿ�� ����ؾ� �Ѵ�.
	//----------------------------------------------------------------------

	// read data from socket input stream
	virtual void read (SocketInputStream & iStream) ;

	// write data to socket output stream
	virtual void write (SocketOutputStream & oStream) ;

	// get size of object
	virtual uint getSize ()  = 0;

	// get debug string
	virtual string toString ()  = 0;

};

#endif
