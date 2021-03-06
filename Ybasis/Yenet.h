/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YENET_H__
#define __YENET_H__

#include "Ybasis.h"
#include "Ythreadpool.h"
#include <enet/enet.h>

enum ENET
{
    ENET_SERVER = 1,
    ENET_CLIENT = 2,
};

class Yenet
{
public:
    Yenet();
    bool    ManageInit();
    void    ManageExit();
    bool    Init(ENET model, Ystring ip = "", unsigned short port = 0);
    void    Destory();

    void    Loop(Yint workNum);

    void    Run();

private:
    ENetHost *_handle;
    ENET    _model;
    std::map<ENetPeer *, Yint> _work;
    std::vector<std::shared_ptr<std::thread>> thread_Ptrs;
    std::mutex _mutex;
    std::queue<void *> _que;
};

#endif // __YENET_H__
