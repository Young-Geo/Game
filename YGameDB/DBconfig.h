/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __DBCONFIG_H__
#define __DBCONFIG_H__

#include "Yalone.hpp"
#include "Yconfig.h"

class DBconfig : public alone<DBconfig>
{
public:
    DBconfig();
public:
    void        Init();
    Yint        GetNumDB();
    Ystring     GetDBServerIp();
    Yint        GetDBServerPort();
    Ystring     GetDBSID();
    Ystring     GetDBUSR();
    Ystring     GetDBPWD();
private:
    config ini;
};

#define gDBconfig DBconfig::GetEntity()

#endif // DBCONFIG_H
