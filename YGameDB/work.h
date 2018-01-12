/*
 * work.h
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#ifndef __WORK_H__
#define __WORK_H__

#include "Ywork.h"
#include "Yalone.hpp"
#include "DBYS.h"
#include "Ymsgtool.h"

class DBwork : public work, public alone<DBwork>
{
public:
    virtual bool		Init();
    virtual void		Loop();
    virtual void        Exit();
public:
    void    Start();
    void    Join();
    void    Detach();
public:
    void    HandleWork(msg *_msg);
    void    HandleWorkLogin(msgC2SLogin *_msg);
};

#define gWORK DBwork::GetEntity()

#endif // __WORK_H__
