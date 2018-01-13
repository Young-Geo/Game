/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YUSER_H__
#define __YUSER_H__

#include "Ybasis.h"
#include "YSocketClient.h"

class Yuser
{
public:
    Yuser();
private:
    SocketClient _sock;
};

#endif // __YUSER_H__
