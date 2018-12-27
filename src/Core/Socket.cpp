//////////////////////////////////////////////////////////////////////
//
// Socket.cpp
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#include "Socket.h"
#include "Assert.h"

Socket::Socket ()

    : m_pSocketImpl(NULL)
{
    __BEGIN_TRY

    m_pSocketImpl = new SocketImpl();
    m_pSocketImpl->create();

    __END_CATCH
}

Socket::Socket ( const string &host, uint port )

    : m_pSocketImpl(NULL)
{
    __BEGIN_TRY

    m_pSocketImpl = new SocketImpl(host, port);
    m_pSocketImpl->create();

    __END_CATCH
}

Socket::Socket ( SocketImpl *impl )

    : m_pSocketImpl(NULL)
{
    __BEGIN_TRY

    Assert( impl != NULL );

    m_pSocketImpl = impl;

    __END_CATCH
}

Socket::~Socket ()

{
    __BEGIN_TRY

    if ( m_pSocketImpl != NULL )
    {
        delete m_pSocketImpl;
        m_pSocketImpl = NULL;
    }

    __END_CATCH
}

// close previous connection and connect to another server socket
void Socket::reconnect ( const string &host, uint port )

{
    __BEGIN_TRY

    // delete old socket impl object
    m_pSocketImpl->close();
    delete m_pSocketImpl;

    // create new socket impl object
    m_pSocketImpl = new SocketImpl( host, port );
    m_pSocketImpl->create();

    // try to connect
    m_pSocketImpl->connect();

    __END_CATCH
}

void Socket::close ()

{
    __BEGIN_TRY

    m_pSocketImpl->close();

    __END_CATCH
}

void Socket::connect ()

{
    __BEGIN_TRY

    m_pSocketImpl->connect();

    __END_CATCH
}

void Socket::connect (const string &host, uint port)

{
    __BEGIN_TRY

    m_pSocketImpl->connect(host, port);

    __END_CATCH
}

uint Socket::send (const void *buf, uint len, uint flags)

{
    __BEGIN_TRY

    return m_pSocketImpl->send(buf, len, flags);

    __END_CATCH
    return 0;
}

uint Socket::receive (void *buf, uint len, uint flags)

{
    __BEGIN_TRY

    return m_pSocketImpl->receive(buf, len, flags);

    __END_CATCH
    return 0;
}

uint Socket::available ()

{
    __BEGIN_TRY

    return m_pSocketImpl->available();

    __END_CATCH
    return 0;
}

uint Socket::getLinger ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getLinger();

    __END_CATCH
    return 0;
}

void Socket::setLinger (uint lingertime)

{
    __BEGIN_TRY

    m_pSocketImpl->setLinger(lingertime);

    __END_CATCH
}

uint Socket::getSockError()

{
    __BEGIN_TRY

    return m_pSocketImpl->isSockError();

    __END_CATCH
    return 0;
}

bool Socket::isNonBlocking ()

{
    __BEGIN_TRY

    return m_pSocketImpl->isNonBlocking();

    __END_CATCH
    return false;
}

void Socket::setNonBlocking (bool on = true)

{
    __BEGIN_TRY

    m_pSocketImpl->setNonBlocking(on);

    __END_CATCH
}

uint Socket::getReceiveBufferSize ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getReceiveBufferSize();

    __END_CATCH
    return 0;
}

void Socket::setReceiveBufferSize (uint size)

{
    __BEGIN_TRY

    m_pSocketImpl->setReceiveBufferSize(size);

    __END_CATCH
}

uint Socket::getSendBufferSize ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getSendBufferSize();

    __END_CATCH
    return 0;
}

void Socket::setSendBufferSize (uint size)

{
    __BEGIN_TRY

    m_pSocketImpl->setSendBufferSize(size);

    __END_CATCH
}

string Socket::getHost ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getHost();

    __END_CATCH
    return NULL;
}

uint Socket::getPort ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getPort();

    __END_CATCH
    return 0;
}

IP_t Socket::getHostIP ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getHostIP();

    __END_CATCH
}

bool Socket::isValid ()

{
    __BEGIN_TRY

    return m_pSocketImpl->isValid();

    __END_CATCH
}

SOCKET Socket::getSOCKET ()

{
    __BEGIN_TRY

    return m_pSocketImpl->getSOCKET();

    __END_CATCH
}

// return debug string
string Socket::toString ()

{
    __BEGIN_TRY

    StringStream msg;
    msg << "Socket(FD:" << getSOCKET() << ",HOST:" << getHost() << ",PORT:" << getPort() << ")" ;
    return msg.toString();

    __END_CATCH
    return NULL;
}
