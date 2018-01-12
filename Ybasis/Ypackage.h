/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YPACKAGE_H__
#define __YPACKAGE_H__

#include "Ybasis.h"
#include "Ylog.h"
#include "Yalone.hpp"
#include "Ychain.hpp"
#include "Ymsgtool.h"
#include <msgpack.hpp>

template <typename T>
void    packT(T t, Ychain_t &chain)
{
    Yassert(chain);
    msgpack::sbuffer buffer_;
    msgpack::packer<msgpack::sbuffer>  pack_(&buffer_);
    pack_.pack(t);//序列化对象
    chain.Write((void *)buffer_.data(), buffer_.size());
}

template <typename T>
void    unpackT(T &t, Ychain_t &chain)
{
    unsigned char*data = NULL;
    msgpack::unpacked _msg;
    msgpack::unpack(&_msg, (char*)&chain, (size_t)chain.Size());
    _msg.get().convert(&t);
}

class Ypackage : public alone<Ypackage>
{
public:
    Ypackage();
public:
    msg* ParseBuf(Ychain_t &chain, Yint fd);
};

#define gPACKAGE Ypackage::GetEntity()

#endif // __YPACKAGE_H__
