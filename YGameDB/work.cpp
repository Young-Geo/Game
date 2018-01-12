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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //std::thread::detach();
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


void    DBwork::HandleWork(msg *_msg)
{
    Yassert(_msg);

    switch (_msg->m_id) {
    case MSG_C_2_S_LOGIN:
        HandleWorkLogin((msgC2SLogin *)_msg);
        break;
    default:
        break;
    }
}

void    DBwork::HandleWorkLogin(msgC2SLogin *_msg)
{
    Yassert(_msg);
    YLOG_BUG("HandleWorkLogin");
}
