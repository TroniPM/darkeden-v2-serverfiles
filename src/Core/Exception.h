//////////////////////////////////////////////////////////////////////
// 
// Filename    : Exception.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__


// include files
#include "Types.h"
#include "StringStream.h"

#if __WINDOWS__
#pragma warning (disable : 4786)
#endif

#include <list>


//////////////////////////////////////////////////////////////////////
//
// class Throwable
//
// Exception �� Error �� ���̽� Ŭ�����̴�. ���� �޽�� �� ����Ÿ��
// �����س��� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class Throwable : public std::exception
{
public:

	// constructor
	Throwable () throw () {}
	
	// constructor
	Throwable (const string& message) throw () : m_Message(message) {}

	// destructor
	virtual ~Throwable () throw () {}

	// return class's name
	virtual string getName ()  { return what(); }

	// add function name to throwable object's function stack
	void addStack (const string & stackname) throw ()
	{
		m_Stacks.push_front(stackname);
	}

	// return debug string - throwable object's function stack trace
	string getStackTrace () 
	{
		StringStream buf;
		int i = 1;

		for (list<string>::const_iterator itr = m_Stacks.begin() ;
			  itr != m_Stacks.end() ;
			  itr ++, i ++) {
			for (int j = 0 ; j < i ; j ++)
				buf << " ";
			buf << *itr << '\n' ;
		}
		
		return string(buf.toString());
	}

	// get throwable object's message
	const string& getMessage ()  { return m_Message; }
	
	// set throwable object's message
	void setMessage (const string & message) throw () { m_Message = message; }
	
	// return debug string - throwable object's detailed information
	virtual string toString () 
	{
		StringStream buf;
		buf << getName() << " : " << m_Message << '\n'
			<< getStackTrace () ;
		
		return string(buf.toString());
	}

private :
	
	// message string
	string m_Message;
	
	// function stack 
	list<string> m_Stacks;
};

//--------------------------------------------------------------------------------
// macro definition
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//
// Throwable�� �ʿ��ϱ� ������ �Ʒ��� �����ߴ�.
// Exception/Error�� ������ ��� �޽���� ��/�Ʒ��� ��õǾ�� �Ѵ�.
// __END_CATCH�� Throwable�� �޼ҵ� ���ÿ� ����� �� ������ ������
// ������ �Ѵ�.
//
//--------------------------------------------------------------------------------

#if defined(NDEBUG)
	#define __BEGIN_TRY ((void)0);
	#define __END_CATCH ((void)0);
#else
	#define __BEGIN_TRY try {
	#define __END_CATCH } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); }
#endif

// �޼��� ����� END_CATCH
//#define __END_CATCH } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); throw; }

// �޼��� ��� END_CATCH
//#define __END_CATCH } catch (Throwable & t) { cout << "\nCAUGHT Exception IN END_CATCH MACRO...\n[" << __PRETTY_FUNCTION__ << "]\n>>> " << t.toString() << endl; t.addStack(__PRETTY_FUNCTION__); throw; }


/*
//--------------------------------------------------------------------------------
//
//	#define __BEGIN_TRY \
//				try {
//	#define __END_CATCH \
//				} catch (Throwable & t) { \
//					t.addStack((func)); \
//					throw; \
//				}
//
//
// critical section
//
//--------------------------------------------------------------------------------
*/
#define __ENTER_CRITICAL_SECTION(mutex) mutex.lock(); try {
#define __LEAVE_CRITICAL_SECTION(mutex) } catch (Throwable & t) { mutex.unlock(); throw; } mutex.unlock(); 

//--------------------------------------------------------------------------------
//
// cout debugging
//
//--------------------------------------------------------------------------------
#if defined(NDEBUG) || defined(__WIN32__)
	#define __BEGIN_DEBUG ((void)0);
	#define __END_DEBUG ((void)0);
#elif defined(__LINUX__) || defined(__WIN_CONSOLE__)
	#define __BEGIN_DEBUG try {
	#define __END_DEBUG  } catch (Throwable & t) { cout << t.toString() << endl; throw; } catch (exception & e) { cout << e.what() << endl; throw; }
#elif defined(__MFC__)
	#define __BEGIN_DEBUG try {
	#define __END_DEBUG } catch (Throwable & t) { AfxMessageBox(t.toString()); throw; }
#endif


//////////////////////////////////////////////////////////////////////
//
// Exception
//
//////////////////////////////////////////////////////////////////////
class Exception : public Throwable {
public :
	Exception () throw () : Throwable() {}
	Exception (const string& msg) throw () : Throwable(msg) {}
	string getName ()  { return "Exception"; }
};

	//////////////////////////////////////////////////////////////////////
	//
	// I/O Exception
	//
	// ����, ����, IPC ����½� �߻��� �� �ִ� ����
	//
	//////////////////////////////////////////////////////////////////////
	// ����, ����, IPC ����½� �߻��� �� �ִ� ����
	class IOException : public Exception {
	public :
		IOException () throw () : Exception () {}
		IOException (const string& msg) throw () : Exception (msg) {}
		string getName ()  { return "IOException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Non Blocking I/O Exception
		//
		// I/O �� nonblocking �� �߻��� ���
		//
		//////////////////////////////////////////////////////////////////////
		class NonBlockingIOException : public IOException {
		public :
			NonBlockingIOException () throw () : IOException () {}
			NonBlockingIOException (const string& msg) throw () : IOException (msg) {}
			string getName ()  { return "NonBlockingIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted I/O Exception
		//
		// I/O �� ���ͷ�Ʈ�� �ɸ� ���
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedIOException : public IOException {
		public :
			InterruptedIOException () throw () : IOException () {}
			InterruptedIOException (const string& msg) throw () : IOException (msg) {}
			string getName ()  { return "InterruptedIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// EOF Exception
		//
		// I/O �� EOF �� ���� ���
		//
		//////////////////////////////////////////////////////////////////////
		class EOFException : public IOException {
		public :
			EOFException () throw () : IOException () {}
			EOFException (const string& msg) throw () : IOException (msg) {}
			string getName ()  { return "EOFException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// File Not Opened Exception 
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotOpenedException : public IOException {
		public :
			FileNotOpenedException () throw () : IOException() {}
			FileNotOpenedException (const string& msg) throw () : IOException(msg) {}
			string getName ()  { return "FileNotOpenedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Already Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileAlreadyExistException : public IOException {
		public :
			FileAlreadyExistException () throw () : IOException() {}
			FileAlreadyExistException (const string& msg) throw () : IOException(msg) {}
			string getName ()  { return "FileAlreadyExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Not Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotExistException : public IOException {
		public :
			FileNotExistException () throw () : IOException() {}
			FileNotExistException (const string& msg) throw () : IOException(msg) {}
			string getName ()  { return "FileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Time out Exception
		//
		// ���� �ð��� ������ ���
		//
		//////////////////////////////////////////////////////////////////////
		class TimeoutException : public IOException {
		public :
			TimeoutException () throw () : IOException () {}
			TimeoutException (const string& msg) throw () : IOException (msg) {}
			string getName ()  { return "TimeoutException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Socket Exception
		//
		// Ư�� ���Ͽ��� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class SocketException : public IOException {
		public :
			SocketException () throw () : IOException () {}
			SocketException (const string& msg) throw () : IOException (msg) {}
			string getName ()  { return "SocketException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Bind Exception
			//
			// bind()�� �߻��ϴ� ����
			//
			//////////////////////////////////////////////////////////////////////
			class BindException : public SocketException {
			public :
				BindException () throw () : SocketException () {}
				BindException (const string& msg) throw () : SocketException (msg) {}
				string getName ()  { return "BindException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Connect Exception
			//
			// ���� ������ ���� ��� (���� ���� �߻��Ѵٰ� ���� �ȴ�.)
			//
			//////////////////////////////////////////////////////////////////////
			class ConnectException : public SocketException {
			public :
				ConnectException () throw () : SocketException () {}
				ConnectException (const string& msg) throw () : SocketException (msg) {}
				string getName ()  { return "ConnectException"; }
			};
			
		//////////////////////////////////////////////////////////////////////
		//
		// Protocol Exception
		//
		// ��Ŷ �Ľ��Ҷ� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class ProtocolException : public IOException {
		public :
			ProtocolException () throw () : IOException () {}
			ProtocolException (const string& msg) throw () : IOException (msg) {}
			string getName ()  { return "ProtocolException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Idle Exception
			//
			// ���� �ð����� peer �κ��� �Է��� ���� ���
			//
			//////////////////////////////////////////////////////////////////////
			class IdleException : public ProtocolException {
			public :
				IdleException () throw () : ProtocolException () {}
				IdleException (const string& msg) throw () : ProtocolException (msg) {}
				string getName ()  { return "IdleException"; }
			};
	

			//////////////////////////////////////////////////////////////////////
			//
			// Invalid Protocol Exception
			//
			// �߸��� ��������
			//
			//////////////////////////////////////////////////////////////////////
			class InvalidProtocolException : public ProtocolException {
			public :
				InvalidProtocolException () throw () : ProtocolException () {}
				InvalidProtocolException (const string& msg) throw () : ProtocolException (msg) {}
				string getName ()  { return "InvalidProtocolException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Insufficient Data Exception
			//
			// ���� ��Ŷ ����Ÿ�� �����ϰ� �������� �ʾ��� ���
			//
			//////////////////////////////////////////////////////////////////////
			class InsufficientDataException : public ProtocolException {
			public :
				InsufficientDataException (uint size = 0) throw () : ProtocolException (), m_Size(size) {}
				InsufficientDataException (const string& msg, uint size = 0) throw () : ProtocolException (msg), m_Size(size) {}
				string getName ()  { return "InsufficientDataException"; }
				uint getSize ()  { return m_Size; }
				string toString () 
				{
					StringStream buf;
					buf << getName() << " : " << getMessage();
					if (m_Size > 0) {
						buf << " (lack of " << m_Size << " bytes)\n";
					}
					buf << getStackTrace ();
			
					return buf.toString();
				}
	
			private :
				uint m_Size;
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// �������� ����, �ý��� ���� ���������ؼ� ������ ©��� �� ���
			// �� ���ܸ� ����Ѵ�.
			// 
			//////////////////////////////////////////////////////////////////////
			class DisconnectException : public ProtocolException {
			public :
				DisconnectException () throw () : ProtocolException () {}
				DisconnectException (const string& msg) throw () : ProtocolException (msg) {}
				string getName ()  { return "DisconnectException"; }
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// Ư�� ��Ȳ�� �����ؾ� �Ǵ� ��Ŷ�� ������ ���
			// 
			//////////////////////////////////////////////////////////////////////
			class IgnorePacketException : public ProtocolException {
			public :
				IgnorePacketException () throw () : ProtocolException () {}
				IgnorePacketException (const string& msg) throw () : ProtocolException (msg) {}
				string getName ()  { return "IgnorePacketException"; }
			};


	//////////////////////////////////////////////////////////////////////
	//
	// Thread Exception
	//
	// ������ �� ����ȭ �����鿡�� �߻��ϴ� ���ܵ�
	//
	//////////////////////////////////////////////////////////////////////
	class ThreadException : public Exception {
	public :
		ThreadException () throw () : Exception () {}
		ThreadException (const string& msg) throw () : Exception (msg) {}
		string getName ()  { return "ThreadException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Mutex Exception
		//
		// ���ؽ����� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class MutexException : public ThreadException {
		public :
			MutexException () throw () : ThreadException () {}
			MutexException (const string& msg) throw () : ThreadException (msg) {}
			string getName ()  { return "MutexException"; }
		};

			//////////////////////////////////////////////////////////////////////
			//
			// Mutex Attribute Exception
			//
			// ���ؽ� �Ӽ����� �߻��ϴ� ���ܵ�
			//
			//////////////////////////////////////////////////////////////////////
			class MutexAttrException : public MutexException {
			public :
				MutexAttrException () throw () : MutexException () {}
				MutexAttrException (const string& msg) throw () : MutexException (msg) {}
				string getName ()  { return "MutexAttrException"; }
			};


		//////////////////////////////////////////////////////////////////////
		//
		// Conditional Variable Exception
		//
		// Conditional Variable ���� �߻��ϴ� ���� (�̸��� �ʹ� ���.. - -)
		//
		//////////////////////////////////////////////////////////////////////
		class CondVarException : public ThreadException {
		public :
			CondVarException () throw () : ThreadException () {}
			CondVarException (const string& msg) throw () : ThreadException (msg) {}
			string getName ()  { return "CondVarException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Semaphore Exception
		//
		// Semaphore ���� �߻��ϴ� ����
		//
		//////////////////////////////////////////////////////////////////////
		class SemaphoreException : public ThreadException {
		public :
			SemaphoreException () throw () : ThreadException () {}
			SemaphoreException (const string& msg) throw () : ThreadException (msg) {}
			string getName ()  { return "SemaphoreException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// SQL Exception 
	//
	// SQL ���� ����
	//
	//////////////////////////////////////////////////////////////////////
	class SQLException : public Exception {
	public :
		SQLException () throw () : Exception() {}
		SQLException (const string& msg) throw () : Exception(msg) {}
		string getName ()  { return "SQLException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// SQL Warning
		//
		// SQL ����� ��Ÿ���� ����~~
		//
		//////////////////////////////////////////////////////////////////////
		class SQLWarning : public SQLException {
		public :
			SQLWarning () throw () : SQLException() {}
			SQLWarning (const string& msg) throw () : SQLException(msg) {}
			string getName ()  { return "SQLWarning"; }
		};


		//////////////////////////////////////////////////////////////////////
		//
		// SQL Connect Exception
		//
		// SQL�� ���� ���� �õ��� ������ ���, ������ �������� ��� ��
		//
		//////////////////////////////////////////////////////////////////////
		class SQLConnectException : public SQLException {
		public :
			SQLConnectException () throw () : SQLException() {}
			SQLConnectException (const string& msg) throw () : SQLException(msg) {}
			string getName ()  { return "SQLConnectException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Query Exception
		//
		//////////////////////////////////////////////////////////////////////
		class SQLQueryException : public SQLException {
		public :
			SQLQueryException () throw () : SQLException() {}
			SQLQueryException (const string& msg) throw () : SQLException(msg) {}
			string getName ()  { return "SQLQueryException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// Runtime Exception
	//
	// ��Ÿ�ӿ� �߻������� generic �� �뵵�� ���� �� �ִ� ���ܵ�
	//
	//////////////////////////////////////////////////////////////////////
	class RuntimeException : public Exception {
	public :
		RuntimeException () throw () : Exception () {}
		RuntimeException (const string& msg) throw () : Exception (msg) {}
		string getName ()  { return "RuntimeException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Invalid Arguemnt Exception
		//
		// �Լ�, ����Լ��� �Ķ���Ͱ� �߸��� ��� 
		//
		//////////////////////////////////////////////////////////////////////
		class InvalidArgumentException : public RuntimeException {
		public :
			InvalidArgumentException () throw () : RuntimeException () {}
			InvalidArgumentException (const string& msg) throw () : RuntimeException (msg) {}
			string getName ()  { return "InvalidArgumentException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Out Of Bound Exception
		//
		// ���״��. Out Of Bound!
		//
		//////////////////////////////////////////////////////////////////////
		class OutOfBoundException : public RuntimeException {
		public :
			OutOfBoundException () throw () : RuntimeException () {}
			OutOfBoundException (const string& msg) throw () : RuntimeException (msg) {}
			string getName ()  { return "OutOfBoundException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted Exception
		//
		// System Call ���� ���ͷ�Ʈ ������ ���
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedException : public RuntimeException {
		public :
			InterruptedException () throw () : RuntimeException () {}
			InterruptedException (const string& msg) throw () : RuntimeException (msg) {}
			string getName ()  { return "InterruptedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// No Such Element Exception
		//
		// �÷��ǿ��� Ư�� Ű���� �˻������� �׷� ������Ʈ�� ���� ���
		//
		//////////////////////////////////////////////////////////////////////
		class NoSuchElementException : public RuntimeException {
		public :
			NoSuchElementException () throw () : RuntimeException () {}
			NoSuchElementException (const string& msg) throw () : RuntimeException (msg) {}
			string getName ()  { return "NoSuchElementException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Duplicated Exception
		//
		// �÷����� Ư�� Ű�� �ߺ��Ǿ��� �� 
		//
		//////////////////////////////////////////////////////////////////////
		class DuplicatedException : public RuntimeException {
		public :
			DuplicatedException () throw () : RuntimeException () {}
			DuplicatedException (const string& msg) throw () : RuntimeException (msg) {}
			string getName ()  { return "DuplicatedException"; }
		};

	//////////////////////////////////////////////////////////////////////
	//
	// Game Exception
	//
	// ���ӿ��� goto �뵵�� ����ϴ� ���ܵ�.. -_-;
	//
	//////////////////////////////////////////////////////////////////////
	class GameException : public Exception {
	public :
		GameException () throw () : Exception () {}
		GameException (const string& msg) throw () : Exception (msg) {}
		string getName ()  { return "GameException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Portal Exception
		//
		// PC �� ��Ż�� �������...�
		//
		//////////////////////////////////////////////////////////////////////
		class PortalException : public GameException {
		public :
			PortalException () throw () : GameException () {}
			PortalException (const string& msg) throw () : GameException (msg) {}
			string getName ()  { return "PortalException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Ư�� ��ǥ ������ ������ ũ��ó�� ���� ������� �� ���� ��
		//
		//////////////////////////////////////////////////////////////////////
		class EmptyTileNotExistException : public GameException {
		public :
			EmptyTileNotExistException () throw () : GameException () {}
			EmptyTileNotExistException (const string& msg) throw () : GameException (msg) {}
			string getName ()  { return "EmptyTileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		//
		//
		//////////////////////////////////////////////////////////////////////
		class InventoryFullException : public GameException {
		public :
			InventoryFullException () throw () : GameException () {}
			InventoryFullException (const string& msg) throw () : GameException (msg) {}
			string getName ()  { return "InventoryFullException"; }
		};


//////////////////////////////////////////////////////////////////////
//
// Error
//
//////////////////////////////////////////////////////////////////////
class Error : public Throwable {
public :
	Error () throw () : Throwable() {}
	Error (const string & msg) throw () : Throwable(msg) {}
	string getName ()  { return "Error"; }
};	
	//////////////////////////////////////////////////////////////////////
	//
	// Game Error
	//
	//////////////////////////////////////////////////////////////////////
	class GameError : public Error {
	public :
		GameError () throw () : Error () {}
		GameError (const string& msg) throw () : Error(msg) {}
		string getName ()  { return "GameError"; }
	};


	//////////////////////////////////////////////////////////////////////
	//
	// Assertion Error
	//
	//////////////////////////////////////////////////////////////////////
	class AssertionError : public Error {
	public :
		AssertionError () throw () : Error () {}
		AssertionError (const string& msg) throw () : Error(msg) {}
		string getName ()  { return "AssertionError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unsupported Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnsupportedError : public Error {
	public :
		UnsupportedError () throw () : Error () {}
		UnsupportedError (const string& msg) throw () : Error(msg) {}
		string getName ()  { return "UnsupportedError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Log Error
	//
	// �Ϲ����� �����ʹ� �޸� LogError�� ����Ʈ �α����Ͽ� �α׵� �� ����.
	// (�����غ���. �α׸Ŵ��� ��ü�� ������ ��� �α��Ѵٴ� ���ΰ�?)
	//
	//////////////////////////////////////////////////////////////////////
	class LogError : public Error {
	public :
		LogError () throw () : Error () {}
		LogError (const string& msg) throw () : Error(msg) {}
		string getName ()  { return "LogError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unknown Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnknownError : public Error {
	public :
		UnknownError () throw () : Error() {}
		UnknownError (const string & msg) throw () : Error(msg) {}
		UnknownError (const string & msg, uint ErrorCode) throw () : Error(msg), m_ErrorCode(ErrorCode) {}
		string getName ()  { return "UnknownError"; }
		uint getErrorCode ()  { return m_ErrorCode; }
		string toString () 
		{
			StringStream buf;
			buf << getName() << " : " << getMessage() << " (" << getErrorCode() << ") \n"
				<< getStackTrace () ;
			
			return buf.toString();
		}
	private :
		uint m_ErrorCode;
	};

#define __BEGIN_DEBUG_EX try {
#define __END_DEBUG_EX  } catch (ProtocolException&) { throw; } catch (Error&) { throw; } catch (Exception & e) { ofstream file("packet_exception.txt", ios::out | ios::app); file << e.toString() << endl; file.close(); cout << e.toString() << endl; } 

#endif
