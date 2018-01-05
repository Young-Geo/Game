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
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/event_compat.h>

#define WORK_THREAD 4

typedef event_callback_fn event_call_t;

typedef struct _entity_t
{
    int inx;
    //pthread_t thread_id;
    std::thread *thread_handle;
    std::shared_ptr<std::thread> thread_ptr;
    struct event_base *base;
    struct event notify_event;
    int notify_receive_fd;
    int notify_send_fd;
    int conn_num;
} entity_t;


typedef struct _master_t
{
    struct event_base *master_base;
    struct event master_event;
    int conn_receive_fd;
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
    void    Init();
    void    AddEvent();
private:
    master_t *_master;
};

#endif // __YS_H__
