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

struct workStruct
{
    msg* _msg;
    DBEntity_t *_dbEntity;
    workStruct(msg* msg, DBEntity_t *dbEntity)
    {
        this->_msg = msg;
        this->_dbEntity = dbEntity;
    }
};

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
    void    HandleWork(workStruct *ws);
    void    HandleWorkLogin(workStruct *ws);
};

#define gWORK DBwork::GetEntity()

#endif // __WORK_H__
