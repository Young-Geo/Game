/*
 * YS.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#include "YS.h"

entity_t* Entity_Init()
{
    entity_t *entity = NULL;
    Yint    pfd[2] = { 0 };

    Yassert((entity = (entity_t *)Ymalloc(sizeof(entity_t))));
    Yzero(entity, sizeof(entity_t));

    if (pipe(pfd)) {
        YLOG_ERR("Can't create notify pipe");
        return NULL;
    }

    entity->notify_receive_fd = pfd[0];
    entity->notify_send_fd = pfd[1];

    if (!(entity->base = event_base_new())) {
        YLOG_ERR("Entity_Init base new error");
        return NULL;
    }

    event_call_t EntityWorkFunc = [=] (Yint fd, Yshort which, void *arg)->void
    {
        //master send fd .. this rec
        Yint cfd = 0, count = 0;
        entity_t *entity = NULL;
        struct bufferevent *bev = NULL;

        Yassert(arg);
        entity = (entity_t *)arg;

        if (sizeof(cfd) != (count = read(fd, &cfd, sizeof(cfd)))) {
            //error
            return;
        }
        //cfd par
        bev = bufferevent_socket_new(entity->base, cfd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, NULL, NULL, NULL, entity);//r w error
        bufferevent_enable(bev, EV_READ|EV_WRITE);

        ++entity->conn_num;
    };

    event_set(&entity->notify_event, entity->notify_receive_fd, (EV_READ | EV_PERSIST), EntityWorkFunc, entity);
    event_base_set(entity->base, &entity->notify_event);
    if (event_add(&entity->notify_event, 0) < 0) {
        //
        YLOG_ERR("Entity_Init event_add eror");
        return NULL;
    }
    std::function<void(entity_t *)> entity_Func = [=](entity_t *entity)->void
    {
        event_base_loop(entity->base, 0);//thread--
    };

    //entity->thread_handle = new std::thread(std::bind(entity_Func, entity));
    entity->thread_ptr = std::make_shared<std::thread>(std::thread(std::bind(entity_Func, entity)));
    return entity;
}

master_t* Master_Init()
{
    master_t *master = NULL;

    Yassert((master = (master_t *)Ymalloc(sizeof(master_t))));
    Yzero(master, sizeof(master_t));

    master->last_event = -1;
    std::function<void(master_t *)> master_Func = [=](master_t *master)->void
    {

        Socket* _socket = socketTool::GetSocket(YSOCKET::SOCKET_SERVER, YSOCKET::SOCKET_STREAM_TCP, Ystring("127.0.0.1"), 9001);

        master->master_base = event_base_new();
        if (!master->master_base) {
            fprintf(stderr, "Can't allocate event base\n");
            exit(1);
        }

        //std::function<void(Yint, Yshort, void *)> MasterWorkFunc = [=] (Yint fd, Yshort which, void *arg)->void
        event_call_t MasterWorkFunc = [=] (Yint fd, Yshort which, void *arg)->void
        {
            //an 应该接受链接 分配到不同的event

            int cfd = 0;
            struct sockaddr_in caddr;
            socklen_t slen;
            // accept
            Yassert(arg);
            master_t *master = (master_t *)arg;

            slen = sizeof(caddr);
            cfd = accept(master->conn_receive_fd, (struct sockaddr *)&caddr, &slen);
            if (cfd < 0) {
                YLOG_ERR("accept socket error %d\n", cfd);
                return;
            }

            master->last_event = (master->last_event + 1) % master->_entitys.size();

            if (sizeof(cfd) != write(master->_entitys[master->last_event]->notify_send_fd, &cfd, sizeof(cfd))) {
                YLOG_ERR("sendto %d socket fd error %d\n", master->last_event, cfd);
                close(cfd);
                return;
            }

        };

        master->conn_receive_fd = _socket->GetFd();
        event_set(&master->master_event, master->conn_receive_fd,
                  EV_READ | EV_PERSIST, MasterWorkFunc, master);
        event_base_set(master->master_base, &master->master_event);

        if (event_add(&master->master_event, 0) == -1) {
            YLOG_ERR("Can'tevent_add\n");
            exit(1);
        }

        event_base_loop(master->master_base, 0);
    };

    //
    if (!master->thread_ptr) {
        master->thread_ptr = std::make_shared<std::thread>(std::thread(std::bind(master_Func, master)));
    }
    return 0;
}




//////////////////////////////////////////////////////
void    YS::Init()
{
    Yassert(_master = ::Master_Init());
}

void    YS::AddEvent()
{
    entity_t *entity = NULL;
    Yassert(entity = ::Entity_Init());
    _master->_entitys.push_back(entity);
}
