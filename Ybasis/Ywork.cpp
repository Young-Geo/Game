/*
 * Ywork.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */

#include "Ywork.h"
#include <functional>

void		work::Run()
{
    if (!thread_ptr)
    {
        thread_ptr = std::make_shared<std::thread>(std::thread(std::bind(&work::Loop, this)));
    }
}
