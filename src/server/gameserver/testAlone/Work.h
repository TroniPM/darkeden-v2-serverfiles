///////////////////////////////////////////////////////////////////
// �����ٸ��� �۾��� ���� Work �߻� Ŭ����.
///////////////////////////////////////////////////////////////////

#ifndef __WORK_H__
#define __WORK_H__

#include <iostream>
#include "Exception.h"

class Work 
{
public:
	Work() {}
	virtual ~Work() {}

public:
	virtual void execute() throw (Error) = 0;
	virtual string toString() const throw(Error) = 0;
};

#endif // __WORK_H__
