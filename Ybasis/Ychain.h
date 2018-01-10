/*
 *  Created on: 2017-12-26
 *      Author: Young.Geo
 *          QQ: 473763733
 *       Email: anxan524@126.com
 */
#ifndef __YCHAIN_H__
#define __YCHAIN_H__

#include "Ybasis.h"
#include "Ylog.h"


typedef struct _buffer_t
{
    struct _buffer_t *next;

    Yint buffer_len;

    Yint misalign;

    Yint off;

    int refcnt;

    unsigned char *buffer;
} buffer_t;

buffer_t*   buffer_new(Yint size);
Yint        buffer_free(buffer_t *buffer);


typedef struct _Ychain_t
{
    buffer_t *first;
    buffer_t *last;

    buffer_t **last_with_datap;//last *
    Yint total_len;

    int refcnt;
} Ychain_t;

Yint        Ychain_buffer_insert(Ychain_t *chain, buffer_t*buffer);

Ychain_t*   Ychain_init();

Yint        Ychain_add(Ychain_t *chain, void *data, Yint datalen);
Yint        Ychain_get(Ychain_t *chain, void *data, Yint datalen);
Yint        Ychain_delete(Ychain_t *chain, void *data, Yint datalen);

#endif // __YCHAIN_H__
