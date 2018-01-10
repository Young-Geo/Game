/*
 * DBYS.h
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */
#ifndef __DBYS_H__
#define __DBYS_H__

#include "YS.h"
#include "Yalone.hpp"
#include "ocicursor.h"

struct DBEntity_t
{
public:
    COCIDatabase _dataEntity;
    COCICursor _coc;
    std::queue<void *> _que;
    DBEntity_t(Ystring dataBaseSid, Ystring dataBaseUsr, Ystring dataBasePwd)
    {
        _dataEntity.COCIDatabase_init();
        _dataEntity.Open(dataBaseSid.c_str(), dataBaseUsr.c_str(), dataBasePwd.c_str());
        _coc.COCICursor_init(&_dataEntity);
    }
};

class DBYS : public YS, public alone<DBYS>
{
public:
    DBYS();
    void Start();
private:
    std::vector<DBEntity_t *> _dbEntitys;
};

#define gDBYS DBYS::GetEntity()

#endif // DBYS_H
