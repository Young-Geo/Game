/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YMSGTOOL_H__
#define __YMSGTOOL_H__

#include "Yalone.hpp"
#include "Ybasis.h"
#include "Ychain.hpp"
#include <msgpack.hpp>

template <typename T>
void    packT(T &t, Ychain_t &chain)
{
    msgpack::sbuffer buffer_;
    msgpack::packer<msgpack::sbuffer>  pack_(&buffer_);
    pack_.pack(t);//序列化对象//T need MSGPACK_DEFINE
    chain.Write((void *)buffer_.data(), buffer_.size());
}

template <typename T>
void    unpackT(T &t, Ychain_t &chain)
{
    msgpack::unpacked _msg;
    msgpack::unpack(&_msg, (char*)&chain, (size_t)chain.Size());
    _msg.get().convert(&t);//T need MSGPACK_DEFINE
}

struct msg
{
    MSGPACK_DEFINE(m_id);
    msg(Yint _id):m_id(_id), m_fd(0), m_chain(new Ychain_t()){}

    virtual msg* Clone() = 0;

    virtual bool    Read(Ychain_t &chain)
    {
        unpackT<msg>(*this, chain);
        return true;
    }

    virtual bool    Write(Ychain_t &chain)
    {
        packT<msg>(*this, chain);
        return true;
    }

    Yint m_id;
    Yint m_fd;
    bool m_isSC;
    Ychain_t* m_chain;
};

struct msgSS : public msg
{
    msgSS(Yint _id) : msg(_id)
    {
        m_isSC = false;
    }

    virtual msg* Clone()
    {
        return new msgSS(m_id);
    }
};

struct msgSC : public msg
{
    msgSC(Yint _id) : msg(_id)
    {
        m_isSC = true;
    }

    virtual msg* Clone()
    {
        return new msgSC(m_id);
    }
};

class msgTool : public alone<msgTool>
{
public:
    msgTool();
public:
    bool    Register(msg *);
    msg*    CreateMsg(Yint id);
private:
    std::map<Yint, msg*> _msgMap;
};

#define gMSGTOOL msgTool::GetEntity()


enum msgID
{
    MSG_C_2_S_LOGIN = 1,
};


struct msgC2SLogin : public msgSC
{
    msgC2SLogin() : msgSC(MSG_C_2_S_LOGIN){}

    virtual msg* Clone(){return new msgC2SLogin();}
};

#endif // __YMSGTOOL_H__
