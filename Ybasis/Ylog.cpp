/*
 * Ylog.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */

#include "Ylog.h"

void        Log::ConsoleLog(YLOG_LEVEL level, const Ychar *file, const Ychar *func, const Yint line, const Ychar *format, ...)
{
    LogData *logdata = new LogData;
    YNULL(logdata);
    logdata->_level = level;
    logdata->_file  = Ystring(file);
    logdata->_func  = Ystring(func);
    logdata->_line  = line;
    va_list va;
    Ychar logBuf[BUF_SIZE] = { 0 };
    va_start(va, format);
    if (vsnprintf(logBuf, (BUFSIZ - 1), format, va) > 0) {
        logdata->_log   = Ystring(logBuf);
    }
    va_end(va);
}

void        Log::SetFileName(Ystring fileName)
{
    this->_fileName = fileName;
}

bool		Log::Init()
{
    return true;
}

Ystring        Log::FormatLogData(LogData *logdata)
{
    //初始化好数据格式放到队列中
    Ystring msg;

    YYNULL(logdata, msg);

    msg += "[";
    msg += _LOGSTRING(logdata->_level);
    msg += "]\t[";
    msg += logdata->_file;
    msg += "]\t[";
    msg += logdata->_func;
    msg += ":";
    Ychar strNumber[20] = { 0 };
    Ysprintf(strNumber, "%d", logdata->_line);
    msg += Ystring(strNumber);
    msg += "]\t";
    msg += logdata->_log;

    return msg;
}

void        Log::WriteFileLog(const Ychar *data)
{
    YNULL(data);
    //write file
}
void		Log::Loop()
{
    while (IsStop())
    {
        //应该读出数据写到日志中
        LogData *logdata = nullptr;
        logdata = (LogData *)this->Pop();
        if (!logdata) {
            //usleep(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        Ystring msg = FormatLogData(logdata);
        //write
        WriteFileLog(msg.c_str());
        delete logdata;
    }
}
