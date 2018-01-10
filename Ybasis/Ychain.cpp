#include "Ychain.h"

buffer_t*   buffer_new(Yint size)
{
    buffer_t *buffer = NULL;
    Yint needSize = 0;
    if (size <= 0) {
        YLOG_LOG("buffer_new size %d", size);
        return NULL;
    }

    needSize += size;
    needSize += sizeof(buffer_t);
    needSize = BUF_SIZE * ((needSize / BUF_SIZE) + 1);

    Yassert(buffer = (buffer_t *)Ycalloc(1, needSize));

    buffer->buffer_len = needSize - sizeof(buffer_t);
    buffer->buffer = (unsigned char *)((buffer_t *)(buffer+1));
    buffer->refcnt = 1;

    return buffer;
}

Yint        buffer_free(buffer_t *buffer)
{
    Yassert(buffer);

    return 0;
}

Yint        Ychain_buffer_insert(Ychain_t *chain, buffer_t*buffer)
{
    Yassert(chain);
    Yassert(buffer);

    if (NULL == *chain->last_with_datap) {
        chain->first = buffer;
        chain->last = buffer;
    } else {
        chain->last->next = buffer;
        chain->last = buffer;
    }

    if (buffer->off)
        chain->last_with_datap = &chain->last;

    return 0;
}

Ychain_t*   Ychain_init()
{
    Ychain_t *chain = NULL;

    Yassert(chain = (Ychain_t *)Ycalloc(1, sizeof(Ychain_t)));

    chain->refcnt = 1;
    chain->last_with_datap = &chain->first;
    return chain;
}

Yint        Ychain_add(Ychain_t *chain, void *data_in, Yint datalen)
{
    buffer_t *cur_buf = NULL;
    unsigned char *data = (unsigned char *)data_in;
    Yint needMoveLen = datalen;

    Yassert(chain);
    Yassert(data_in);

    if (chain->total_len + needMoveLen >= YINTMAX) {
        YLOG_BUG("Ychain_add chain too long");
        return -1;
    }

    if (NULL == *chain->last_with_datap) {
        //first
        cur_buf = buffer_new(needMoveLen);
    } else {
        cur_buf = *chain->last_with_datap;
    }

    if (!cur_buf) {
        YLOG_ERR("Ychain_add error");
        return -2;
    }

    if (needMoveLen > 0 && (cur_buf->off < cur_buf->buffer_len)) {
        Ymemcpy(cur_buf->buffer+cur_buf->off, data, cur_buf->buffer_len - cur_buf->off);
        cur_buf->off += (cur_buf->buffer_len - cur_buf->off);
        needMoveLen -= (cur_buf->buffer_len - cur_buf->off);
        data += (cur_buf->buffer_len - cur_buf->off);
    }
    if (NULL == *chain->last_with_datap) {
        Ychain_buffer_insert(chain, cur_buf);
    }

    if (needMoveLen > 0) {
        buffer_t *cur_buf = NULL;
        Yassert(cur_buf = buffer_new(needMoveLen));
        Ymemcpy(cur_buf->buffer+cur_buf->off, data, needMoveLen);
        cur_buf->off += needMoveLen;
        Ychain_buffer_insert(chain, cur_buf);
    }

    chain->total_len += datalen;

    return 0;
}

Yint        Ychain_get(Ychain_t *chain, void *data, Yint datalen)
{
    Yint needGet = datalen, pos = 0, curNeedCopy = 0;
    buffer_t *curBuf = NULL;

    Yassert(chain);
    Yassert(data);

    if (needGet <= 0 || chain->total_len <= 0) {
        YLOG_LOG("total_len %d   Ychain_get needGet %d", chain->total_len, needGet);
        return -1;
    }

    if (needGet > chain->total_len)
        needGet = chain->total_len;

    curBuf = chain->first;
    if (NULL == curBuf) {
        YLOG_ERR("chain first = NULL");
        return -1;
    }
    
    for ( ; (needGet > 0) && (curBuf); )
    {
        curNeedCopy = needGet < (curBuf->off - curBuf->misalign) ? needGet : (curBuf->off - curBuf->misalign);
        Ymemcpy(data+pos, curBuf->buffer+curBuf->misalign, curNeedCopy);
        pos += curNeedCopy;
        needGet -= curNeedCopy;
        curBuf = curBuf->next;
    }

    return 0;
}

static
Yint        chain_cur_move(Ychain_t *chain, Yint len)
{
    Yint needMove = len;
    buffer_t *curBuf = NULL, *tempBuf = NULL;

    Yassert(chain);

    if (needMove <= 0) {
        YLOG_LOG("chain_move needMove %d", needMove);
        return -1;
    }

    curBuf = chain->first;
    if(NULL == curBuf) {
        YLOG_ERR("chain_move chain first = NULL");
        return -1;
    }

    for ( ; needMove > 0; )
    {

        if (needMove >= (curBuf->off-curBuf->misalign)) {
            needMove -= (curBuf->off-curBuf->misalign);
            tempBuf = curBuf;
            curBuf = curBuf->next;
            chain->first = curBuf;
            if (tempBuf == *chain->last_with_datap) {
                chain->last_with_datap = NULL;
                buffer_free(tempBuf);
                break;
            }
            buffer_free(tempBuf);
        } else {
            curBuf->misalign += needMove;
            needMove = 0;
        }
    }

    return 0;
}

Yint        Ychain_delete(Ychain_t *chain, void *data, Yint datalen)
{
    Yint needDelete = datalen;
    Yassert(chain);
    Yassert(data);

    if (needDelete <= 0) {
        YLOG_LOG("Ychain_delete needDelete %d", needDelete);
        return -1;
    }

    if (needDelete > chain->total_len)//
        needDelete = chain->total_len;

    if (Ychain_get(chain, data, needDelete)) {
        YLOG_ERR("Ychain_delete get data");
        return -1;
    }

    return chain_cur_move(chain, needDelete);
}
