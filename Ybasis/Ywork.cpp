/*
 * Ywork.cpp
 *
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 */

#include "Ywork.h"

bool		work::Run()
{
	ptr.reset(new std::thread(work::Loop()));
	return true;
}
