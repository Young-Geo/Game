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
};

#define gWORK DBwork::GetEntity()

#endif // __WORK_H__
