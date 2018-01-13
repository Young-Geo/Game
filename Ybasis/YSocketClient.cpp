/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#include "YSocketClient.h"

SocketClient::SocketClient(){}

SocketClient::SocketClient(bufferevent *ptr, Yint flag)
{
    m_SockPtr = ptr;
    m_flag    = flag;
    m_isbuff = true;
}

SocketClient::SocketClient(struct event_base *base, Yint _fd, Yint opt)
{
    m_flag = 1;
    m_isbuff = true;
    m_SockPtr = bufferevent_socket_new(base, _fd, opt);
}

SocketClient::~SocketClient()
{
    if (m_SockPtr && m_flag && m_isbuff) {
        bufferevent_free(m_SockPtr);
    }
}

Yint        SocketClient::GetFd()
{
    return bufferevent_getfd(m_SockPtr);
}
