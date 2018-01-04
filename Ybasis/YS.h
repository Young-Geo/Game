/*
 * YS.h
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#ifndef __YS_H__
#define __YS_H__

#include "Ybasis.h"
#include "Yalone.hpp"
#include "Ysocket.h"

#define WORK_THREAD 4


typedef struct _entity_t
{
    int inx;
    //pthread_t thread_id;
    //std::thread *thread_handle;
    struct event_base *base;
    struct event notify_event;
    int notify_receive_fd;
    int notify_send_fd;
    int conn_num;
    //conn_queue_t conn_queue;
    master_t *master;
} entity_t;


typedef struct _master_t
{
    struct event_base *master_base;
    struct event master_notify_event;
    int conn_receive_fd;
    int num_event;
    int last_event;
    std::vector<entity_t *> _entitys;
    std::shared_ptr<std::thread> thread_ptr;
} master_t;

entity_t* Entity_Init();

master_t* Master_Init();


//封装libevent
class YS : public alone<YS>
{
public:
private:
    master_t *_master;
};

#endif // __YS_H__
