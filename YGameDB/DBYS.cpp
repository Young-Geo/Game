/*
 * DBYS.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#include "DBYS.h"
#include "DBconfig.h"
#include "Ypackage.h"
#include "work.h"
#include "YSocketClient.h"

DBYS::DBYS(){}


void    DBYS::Start()
{
    YSOCKET::sock_addr_t addr;
    addr._ip    = gDBconfig->GetDBServerIp();
    addr._port  = gDBconfig->GetDBServerPort();
    YS::Start(addr);//start

    auto func_r = [=] (SocketClient sockClient, Ychain_t &chain, void *arg) ->void
    {
        DBEntity_t *_dbEntity = NULL;
        msg *_msg = NULL;

        Yassert(_dbEntity = (DBEntity_t *)arg);

        _msg = gPACKAGE->ParseBuf(chain, sockClient);
        if (!_msg) {
            return;
        }
        gWORK->Push(new workStruct(_msg, _dbEntity));
    };

    for (Yint i = 0; i < gDBconfig->GetNumDB(); ++i)
    {
        DBEntity_t * dbEntity = nullptr;
        Yassert(dbEntity = new DBEntity_t(gDBconfig->GetDBSID(), gDBconfig->GetDBUSR(), gDBconfig->GetDBPWD()));
        _dbEntitys.push_back(dbEntity);

        this->AddWorkEvent(func_r, NULL, NULL, dbEntity);
    }
    //
}
