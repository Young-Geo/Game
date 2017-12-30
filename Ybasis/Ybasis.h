/*
 * Ybasis.h
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */

#ifndef __YBASIS_H__
#define __YBASIS_H__

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <list>
#include <map>
#include <queue>
#include <algorithm>
#include <stdarg.h>

typedef int     Yint;
typedef char    Ychar;
typedef std::string Ystring;

#define BUF_SIZE 1024

#define Ynew new
#define Ydelete delete


#define YYNULL(x, y) if(!(x)) return y
#define YNULL(x) if(!(x)) return
#define _TO_STR(var)  (#var)
#define Ysprintf(str, format, ...) sprintf((str), (format), ##__VA_ARGS__)



#endif /* __YBASIS_H__ */
