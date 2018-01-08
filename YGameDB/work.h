#ifndef __WORK_H__
#define __WORK_H__

#include "Ywork.h"
#include "Yalone.hpp"
#include "YS.h"

class DBwork : public work, public YS, public alone<DBwork>
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
