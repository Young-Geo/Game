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
        HandleWork(_ws);
        // delete _ws->_msg
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


void    DBwork::HandleWork(workStruct *ws)
{
    Yassert(ws);

    switch (ws->_msg->m_id) {
    case MSG_C_2_S_LOGIN:
        HandleWorkLogin(ws);
        break;
    default:
        YLOG_BUG("HandleWork mid %d", ws->_msg->m_id);
        break;
    }
}

void    DBwork::HandleWorkLogin(workStruct *ws)
{
    YLOG_BUG("HandleWorkLogin");
}
