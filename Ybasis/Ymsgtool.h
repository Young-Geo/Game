/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YMSGTOOL_H__
#define __YMSGTOOL_H__

#include "Yalone.hpp"

struct msg
{
    msg() {}
    virtual msg* Clone()
    {
        return new msg;
    }
    Yint m_id;
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

#endif // __YMSGTOOL_H__
