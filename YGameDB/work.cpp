#include "work.h"



bool		DBwork::Init()
{
    return true;
}

void		DBwork::Loop()
{
    event_rwe_t r = { 0 };
    auto func_r = [=](struct bufferevent *bev, void *arg)->void
    {
        //
        entity_t *entity = NULL;
        Yassert(arg);
        entity = (entity_t *)arg;
        entity->call.arg;
        //
    };
    r.call_r = func_r;
    for (Yint i = 0; i < 4; ++i)
        this->AddEvent(r);
    //

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
    YS::Start();//YS start
    work::Start();//start parent-->Loop
}

void    DBwork::Detach()
{
    work::Detach();
}
