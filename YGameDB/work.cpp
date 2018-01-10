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
