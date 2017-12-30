/*
 * Ywork.h
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */

#ifndef __YWORK_H__
#define __YWORK_H__

#include "Ybasis.h"





class work
{
public:
	virtual bool		Init();
	virtual bool		Start();
	virtual void		Loop();
private:
    void		Run();
private:
    std::shared_ptr<std::thread> thread_ptr;
};
#endif /* __YWORK_H__ */
