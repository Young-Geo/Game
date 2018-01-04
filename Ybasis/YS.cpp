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
    Yassert((entity = Ymalloc(sizeof(entity_t))));
    Yzero(entity, sizeof(entity_t));
    return entity;
}

void master_libevent_work(int fd, short which, void *arg)
{
    int cfd = 0, i = 0, inx = 0;
    struct sockaddr_in caddr;
    socklen_t slen;
    // accept
    assert(arg);
    slen = sizeof(caddr);
    global_t *master = (global_t *)arg;

    cfd = accept(master->conn_receive_fd, (struct sockaddr *)&caddr, &slen);
    if (cfd < 0) {
        fprintf(stderr, "master_libevent_work socket error %d\n", cfd );
        return;
    }

    xmessage("conn num %d, %d, %d, %d,\n", master->thread_entitys[0].conn_num,
                                        master->thread_entitys[1].conn_num,
                                        master->thread_entitys[2].conn_num,
                                        master->thread_entitys[3].conn_num);
    // ���������������߳�

    inx = (master->last_thread + 1) % master->num_threads;
    master->last_thread = inx;

    cq_push(&master->thread_entitys[inx].conn_queue, cfd);

    //write 'c'
    if (strlen("C") != write(master->thread_entitys[inx].notify_send_fd, "C", strlen("C"))) {
        close(cfd);
        return;
    }
    /*
    // ���ļ����������͸���Ӧ���߳�
    if (sizeof(cfd) != write(master->thread_entitys[inx].notify_send_fd, &cfd, sizeof(cfd))) {
        close(cfd);
        return;
    }
    */
}


master_t* Master_Init()
{
    master_t *master = NULL;

    Yassert((master = Ymalloc(sizeof(master_t))));
    Yzero(master, sizeof(master_t));

    master->last_event = -1;
    function<void(master_t *)> func = [=](master_t *master)->void
    {
        /*
        int lfd;
        struct sockaddr_in addr;
        socklen_t slen;

        if((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            fprintf(stderr, "master_work socket error %d\n", lfd);
            exit(1);
        }

        master->conn_receive_fd = lfd;

        xzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(SER_ADDR);
        addr.sin_port = htons(SER_PORT);
        slen = sizeof(addr);
        if (0 != ::bind(lfd, (struct sockaddr *)&addr, slen)) {
            fprintf(stderr, "master_work bind socket error %d\n", lfd);
            exit(1);
        }
        if (0 != listen(lfd, MAX_LISTEN)) {
            fprintf(stderr, "master_work listen  socket  error %d\n", lfd);
            exit(1);
        }
        */
        socket* _socket = socketTool::GetSocket(YSOCKET::SOCKET_SERVER, YSOCKET::SOCKET_STREAM_TCP, Ystring("127.0.0.1"), 9001);


        master->master_base = event_base_new();


         if (!master->master_base) {
            fprintf(stderr, "Can't allocate event base\n");
            exit(1);
        }

        function<void(Yint, Yshort, void *)> MasterWorkFunc = [=] (Yint fd, Yshort which, void *arg)->void
        {
            //an 应该接受链接 分配到不同的event
        };
        master->conn_receive_fd = _socket->GetFd();
        event_set(&master->master_notify_event, master->conn_receive_fd,
                  EV_READ | EV_PERSIST, MasterWorkFunc, master);
        event_base_set(master->master_base, &master->master_notify_event);

        if (event_add(&master->master_notify_event, 0) == -1) {
            fprintf(stderr, "Can'tevent_add\n");
            exit(1);
        }


        event_base_loop(master->master_base, 0);
    };

    return 0;
}
