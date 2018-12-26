//--------------------------------------------------------------------------------
//
// Filename   : Assert.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __ASSERT_H__
#define __ASSERT_H__

// include files
#include "Types.h"
#include "Exception.h"

//--------------------------------------------------------------------------------
//
// Config.h �� NDEBUG �� ���ǵǸ�, ��� Assert�� �����Ѵ�.
// �׷��� ���� ��� Assert�� �����ϸ� ���Ͽ� �α׸� ����, AssertError�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
void __assert__ (const char* file, uint line, const char* func, const char* expr) ;

//--------------------------------------------------------------------------------
//
// ProtocolAssert �� Ŭ���̾�Ʈ ��ŷ��, �߸��� �����Ͱ� �Ѿ�� ��, ������ ��ó�� �� ��, 
// �� ������ �����Ű�� ������ �Ѵ�.
//
//--------------------------------------------------------------------------------
void __protocol_assert__ (const char* file, uint line, const char* func, const char* expr) ;

#if defined(NDEBUG)
	#define Assert(expr) ((void)0)
#elif __LINUX__
	#define Assert(expr) ((void)((expr)?0:(__assert__(__FILE__,__LINE__,__PRETTY_FUNCTION__,#expr),0)))
	#define ProtocolAssert(expr) ((void)((expr)?0:(__protocol_assert__(__FILE__,__LINE__,__PRETTY_FUNCTION__,#expr),0)))
#elif __WIN_CONSOLE__ || __WIN32__
	#define Assert(expr) ((void)((expr)?0:(__assert__(__FILE__,__LINE__,"",#expr),0)))
#elif __MFC__
	#define Assert(expr) ASSERT(expr)
#endif

#endif
