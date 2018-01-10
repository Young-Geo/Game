/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#include "DBconfig.h"

DBconfig::DBconfig(){}

void       DBconfig::Init()
{
    this->ini.LoadFile("YGameDB.ini");
}

Yint    DBconfig::GetNumDB()
{
    return this->ini.GetInt("DBnum", 4);
}

Ystring DBconfig::GetDBServerIp()
{
    return this->ini.GetString("DBServerIp", "127.0.0.1");
}

Yint    DBconfig::GetDBServerPort()
{
    return this->ini.GetInt("DBServerPort", 9001);
}

Ystring     DBconfig::GetDBSID()
{
    return this->ini.GetString("DBSID", "//127.0.0.1/landlord_game");
}

Ystring     DBconfig::GetDBUSR()
{
    return this->ini.GetString("DBUSR", "root");
}

Ystring     DBconfig::GetDBPWD()
{
    return this->ini.GetString("DBPWD", "anxan4444anxan");
}
