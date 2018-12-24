//////////////////////////////////////////////////////////////////////
// 
// SocketEncryptOutputStream.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_ENCRYPT_OUTPUT_STREAM_H__
#define __SOCKET_ENCRYPT_OUTPUT_STREAM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketOutputStream.h"
#include "Encrypter.h"

const unsigned int DefaultSocketEncryptOutputBufferSize = 81920;

//////////////////////////////////////////////////////////////////////
//
// class SocketEncryptOutputStream
//
//////////////////////////////////////////////////////////////////////

class SocketEncryptOutputStream : public SocketOutputStream {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketEncryptOutputStream (Socket* sock, uint BufferSize = DefaultSocketEncryptOutputBufferSize) throw (Error);
	~SocketEncryptOutputStream () throw (Error);
	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// write data to stream (output buffer)
	// *CAUTION*
	// string �� ���ۿ� writing �� ��, �ڵ����� size �� �տ� ���� ���� �ִ�.
	// �׷���, string �� ũ�⸦ BYTE/WORD �� ��� ������ �� ������ �ǹ��̴�.
	// ��Ŷ�� ũ��� ���� ���� ���ٴ� ��å�Ͽ��� �ʿ信 ���� string size ����
	// BYTE �Ǵ� WORD �� �������� ����ϵ��� �Ѵ�.
    uint writeEncrypt (bool   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (char   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (uchar  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (short  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (ushort buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (int    buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (uint   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (long   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (ulong  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }

/*    uint writeEncrypt (bool   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szbool  ); }
    uint writeEncrypt (char   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szchar  ); }
    uint writeEncrypt (uchar  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szuchar ); }
    uint writeEncrypt (short  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szshort ); }
    uint writeEncrypt (ushort buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szushort); }
    uint writeEncrypt (int    buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szint   ); }
    uint writeEncrypt (uint   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szuint  ); }
    uint writeEncrypt (long   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szlong  ); }
    uint writeEncrypt (ulong  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szulong ); }
*/
	void	setEncryptCode(uchar code)	{ m_Encrypter.setCode(code); }
	uchar   getEncryptCode() const      { return m_Encrypter.getCode(); }

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	Encrypter m_Encrypter;
	
};

#endif
