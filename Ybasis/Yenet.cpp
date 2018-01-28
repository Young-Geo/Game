/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#include "Yenet.h"

Yenet::Yenet():_handle(NULL){}


bool    Yenet::ManageInit()
{
    return (0 == enet_initialize());
}

void    Yenet::ManageExit()
{
    atexit(enet_deinitialize);
}


bool    Yenet::Init(ENET model, Ystring ip, unsigned short port)
{

    if (model == ENET_SERVER) {
        ENetAddress addr;
        enet_address_set_host(&addr, ip.c_str());
        addr.port = port;
        _model = ENET_SERVER;
        _handle = enet_host_create(&addr, 32, 2, 0, 0);
    } else if (model == ENET_CLIENT) {
        _model = ENET_CLIENT;
        _handle = enet_host_create(NULL, 1, 2, 57600, 14400);
    }

    return (_handle != NULL);
}


void    Yenet::Destory()
{
    if (!_handle)
        return;

    enet_host_destroy(_handle);
}

void    Yenet::Run()
{

}

void    Yenet::Loop(Yint workNum)
{
    ENetEvent event;
    Yint workFlag = -1;

    if (!_handle) {
        return;
    }

    for (Yint i = 0 ; i < workNum; ++i)
    {
        std::shared_ptr<std::thread> ptr;
        ptr = std::make_shared<std::thread>(std::bind(&Yenet::Run, this));
        if (!ptr)
            continue;
        ptr->detach();
        thread_Ptrs.push_back(ptr);
    }
    /* Wait up to 1000 milliseconds for an event. */
    while (true)
    {
        if (enet_host_service(_handle, &event, 1000) <= 0)
            continue;

        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            {
                printf ("A new client connected from %x:%u.\n",
                        event.peer -> address.host,
                        event.peer -> address.port);
                /* Store any relevant client information here. */
                event.peer -> data = (void *)"Client information";

                _work[event.peer] = ++workFlag % workNum;
            }
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
                    event.packet -> dataLength,
                    event.packet -> data,
                    event.peer -> data,
                    event.channelID);
            /* Clean up the packet now that we're done using it. */
            //push work chuli
            enet_packet_destroy(event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            printf ("%s disconnected.\n", event.peer -> data);
            /* Reset the peer's client information. */
            event.peer -> data = NULL;
            if (_work.find(event.peer) == _work.end()) {
                continue;
            }

            _work.erase(event.peer);
        }
    }
}
