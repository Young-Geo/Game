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

struct msg
{
    msg(Yint _id):m_id(_id), m_fd(0), m_chain(new Ychain_t()){}

    virtual msg* Clone() = 0;

    virtual Ychain_t*   GetSendBuf() = 0;

    Yint m_id;
    Yint m_fd;
    Ychain_t* m_chain;
};

struct msgSS : public msg
{
    msgSS(Yint _id) : msg(_id){}

    virtual msg* Clone()
    {
        return new msgSS(m_id);
    }

    virtual Ychain_t*   GetSendBuf();
};

struct msgSC : public msg
{
    msgSC(Yint _id) : msg(_id){}

    virtual msg* Clone()
    {
        return new msgSC(m_id);
    }

    virtual Ychain_t*   GetSendBuf();
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
