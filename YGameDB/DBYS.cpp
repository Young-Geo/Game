/*
 * DBYS.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#include "DBYS.h"
#include "DBconfig.h"

DBYS::DBYS(){}


void    DBYS::Start()
{
    YSOCKET::sock_addr_t addr;
    addr._ip    = gDBconfig->GetDBServerIp();
    addr._port  = gDBconfig->GetDBServerPort();
    YS::Start(addr);//start

    auto func_r = [=](struct bufferevent *bev, void *arg)->void
    {
        //
        entity_t *entity = NULL;
        DBEntity_t *dbEntity = NULL;

        Yassert(arg);
        entity = (entity_t *)arg;
        Yassert(entity->call.arg);
        dbEntity = (DBEntity_t *)entity->call.arg;
        //
    };

    for (Yint i = 0; i < gDBconfig->GetNumDB(); ++i)
    {
        DBEntity_t * dbEntity = nullptr;
        Yassert(dbEntity = new DBEntity_t(gDBconfig->GetDBSID(), gDBconfig->GetDBUSR(), gDBconfig->GetDBPWD()));
        _dbEntitys.push_back(dbEntity);

        event_rwe_t r = { 0 };
        r.call_r = func_r;
        r.arg = dbEntity;
        this->AddEvent(r);
    }
    //
}
