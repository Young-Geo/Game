/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#include "YSocketClient.h"

SocketClient::SocketClient()
{
    m_SockPtr   = NULL;
    m_isbuff    = NULL;
    m_socket    = NULL;
}

SocketClient::SocketClient(bufferevent *ptr)
{
    m_SockPtr   = ptr;
    m_isbuff    = true;
    m_socket    = NULL;
}

SocketClient::SocketClient(struct event_base *base, Yint _fd, Yint opt)
{
    m_isbuff = true;
    m_SockPtr = bufferevent_socket_new(base, _fd, opt);
}

SocketClient::~SocketClient(){}

Yint        SocketClient::GetFd()
{
    return bufferevent_getfd(m_SockPtr);
}

void        SocketClient::Destory()
{
    if (m_SockPtr && m_isbuff) {
        bufferevent_free(m_SockPtr);
    }

    if (m_SockPtr && !m_isbuff) {
        m_socket->Destory();
    }
}
