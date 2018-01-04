/*
 * Ysocket.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#include "Ysocket.h"

socket::socket()
{
    this->_isInit = false;
}

socket::socket(YSOCKET::SOCKET_MODEL mode, YSOCKET::SOCKET_STREAM_MODEL streamMode, Ystring ip, Yint port)
{
    this->_mode = mode;
    this->_streamMode = streamMode;
    this->_ip = ip;
    this->_port = port;
    this->_isInit = false;
}

void    socket::SetSocketModel(YSOCKET::SOCKET_MODEL mode)
{
    this->_mode = mode;
}

void    socket::SetSocketStreamModel(YSOCKET::SOCKET_STREAM_MODEL streamMode)
{
    this->_streamMode = streamMode;
}

void    socket::SetSocketIp(Ystring ip)
{
    this->_ip = ip;
}

void    socket::SetSocketPort(Yint port)
{
    this->_port = port;
}

Yint    socket::GetFd()
{
    return this->_fd;
}

bool    socket::Init()
{
    struct sockaddr_in addr;
    socklen_t slen;

    if((_fd = ::socket(AF_INET, YSOCKET::SOCKET_STREAM_TCP, 0)) < 0) {
        YLOG_ERR("socket::Init socket error %d\n", _fd);
        return false;
    }

    Yzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = htonl(_ip);
    inet_pton(AF_INET, _ip, (void *)(&addr.sin_addr.s_addr));
    addr.sin_port = htons(_port);
    slen = sizeof(addr);
    if (::bind(_fd, (struct sockaddr *)&addr, slen) < 0) {
        YLOG_ERR("socket::bind socket error %d\n", _fd);
        return false;
    }
    _isInit = true;
    return _isInit;
}





///////////////////////////////////////////////////////
socketTool::socketTool(){}
