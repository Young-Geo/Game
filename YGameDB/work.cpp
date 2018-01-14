/*
 * work.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#include "work.h"



bool		DBwork::Init()
{
    return true;
}

void		DBwork::Loop()
{
    while (true)
    {
        ///////
        //std::thread::detach();
        workStruct *_ws = (workStruct *)this->Pop();
        if (!_ws || !_ws->_dbEntity || !_ws->_msg) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        HandleWork(_ws->_msg, _ws->_dbEntity);
    }
}


void        DBwork::Exit()
{
    //xiaohui
}

void    DBwork::Join()
{
    work::Join();//master join
    this->Exit();
}

void    DBwork::Start()
{
    //work::Start();//start parent-->Loop
    gDBYS->Start();
}

void    DBwork::Detach()
{
    work::Detach();
}


void    DBwork::HandleWork(msg *_msg, DBEntity_t *_dbEntity)
{
    Yassert(_msg);

    switch (_msg->m_id) {
    case MSG_C_2_S_LOGIN:
        HandleWorkLogin((msgC2SLogin *)_msg, _dbEntity);
        break;
    default:
        break;
    }
}

void    DBwork::HandleWorkLogin(msgC2SLogin *_msg, DBEntity_t *_dbEntity)
{
    Yassert(_msg);
    Yassert(_dbEntity);
    YLOG_BUG("HandleWorkLogin");
}
