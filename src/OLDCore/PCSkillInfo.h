//////////////////////////////////////////////////////////////////////
// 
// Filename    : PCSkillInfo.h 
// Written By  : elca@ewestsoft.com
// Description :  ��ų�� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __PC_SKILL_INFO_H__
#define __PC_SKILL_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class PCSkillInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class PCSkillInfo {

public :
	
	// destructor
	virtual ~PCSkillInfo () throw () {}

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    virtual void read (SocketInputStream & iStream) throw (ProtocolException, Error) = 0;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    virtual void write (SocketOutputStream & oStream) const throw (ProtocolException, Error) = 0;

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	virtual PacketSize_t getSize () throw () = 0;

	// get packet's debug string
	virtual string toString () const throw () = 0;

};

#endif
