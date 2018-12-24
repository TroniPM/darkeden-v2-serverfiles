//////////////////////////////////////////////////////////////////////////////
// Filename    : LogClient.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>   /* basic system data types */
#include <sys/socket.h>  /* basic socket definitions */
#include <sys/time.h>    /* timeval{} for select() */
#include <time.h>        /* timespec{} for pselect() */
#include <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>   /* inet(3) functions */
#include <errno.h>
#include <fcntl.h>       /* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>    /* for S_xxx file mode constants */
#include <sys/uio.h>     /* for iovec{} and readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>      /* for Unix domain sockets */
#include "LogClient.h"
#include "LogData.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

LogClient*  g_pLogClient          = NULL;
int         LogClient::m_LogLevel = 0;

void log(short type, const string& source, const string& target)
{
	/*
	// �α� Ÿ���� �˻��ϴ� ���� LogClient::log() �Լ� ������
	// üũ�ؾ� ����� �� ������, �� �� �ִ� �� �Լ� ȣ���� ���̱� ���ؼ�
	// ���� �Լ� ������ �ߴ�.
	if (type < LogClient::getLogLevel())
	{
		g_pLogClient->_log(type, source, target);
	}
	else { }
	*/
}

void log(short type, const string& source, const string& target, const string& content)
{
	/*
	// �α� Ÿ���� �˻��ϴ� ���� LogClient::log() �Լ� ������
	// üũ�ؾ� ����� �� ������, �� �� �ִ� �� �Լ� ȣ���� ���̱� ���ؼ�
	// ���� �Լ� ������ �ߴ�.
	if (type < LogClient::getLogLevel())
	{
		g_pLogClient->_log(type, source, target, content);
	}
	else { }
	*/
}

void log(short type, const string& source, const string& target, const string& content, short zoneid)
{
	/*
	// �α� Ÿ���� �˻��ϴ� ���� LogClient::log() �Լ� ������
	// üũ�ؾ� ����� �� ������, �� �� �ִ� �� �Լ� ȣ���� ���̱� ���ؼ�
	// ���� �Լ� ������ �ߴ�.
	if (type < LogClient::getLogLevel())
	{
		g_pLogClient->_log(type, source, target, content, zoneid);
	}
	else { }
	*/
}


//////////////////////////////////////////////////////////////////////////////
// class LogClient member methods
//////////////////////////////////////////////////////////////////////////////

LogClient::LogClient(string ip, short port)
{
	m_bConnected = false;
	m_Sent = 0;

	connect(ip, port);
}

LogClient::~LogClient()
{
	disconnect();
}

void LogClient::connect(string ip, short port)
{
	/*
	if (m_bConnected)
	{
		cout << "LogClient::connect() : already connected" << endl;
		return;
	}

	sockaddr_in serv_addr;
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	int n = inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
	if (n <= 0)
	{
		cout << "LogClient::connect() : could not complete inet_pton" << endl;
		exit(0);
	}

	::connect(m_Socket, (sockaddr*)&serv_addr, sizeof(serv_addr));

	m_bConnected = true;
	*/
}

void LogClient::disconnect(void)
{
	/*
	if (!m_bConnected)
	{
		cout << "LogClient::disconnect() : not connected yet" << endl;
		return;
	}

	close(m_Socket);
	*/
}

void LogClient::_log(short type, const string& source, const string& target)
{
	/*
	LogData data;

	data.setType(type);
	data.setSource(source);
	data.setTarget(target);

	//m_Sent += data.getSize();

	data.write(m_Socket);
	*/
}

void LogClient::_log(short type, const string& source, const string& target, const string& content)
{
	/*
	LogData data;

	data.setType(type);
	data.setSource(source);
	data.setTarget(target);
	data.setContent(content);

	//m_Sent += data.getSize();

	data.write(m_Socket);
	*/
}

void LogClient::_log(short type, const string& source, const string& target, const string& content, short zoneid)
{
	/*
	LogData data;

	data.setType(type);
	data.setSource(source);
	data.setTarget(target);
	data.setContent(content);
	data.setZoneID(zoneid);

	//m_Sent += data.getSize();

	data.write(m_Socket);
	*/
}

