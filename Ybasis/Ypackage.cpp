#include "Ypackage.h"

Ypackage::Ypackage(){}

msg* Ypackage::ParseBuf(Ychain_t &chain, Yint fd)
{
    Yint _id = 0;
    msg * _msg = NULL;

    _msg = gMSGTOOL->CreateMsg(_id);

    _msg->m_fd = fd;
    return _msg;
}
