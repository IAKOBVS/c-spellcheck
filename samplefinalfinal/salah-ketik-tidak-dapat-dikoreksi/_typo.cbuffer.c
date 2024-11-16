#define _GNU_SOURCE

typedef struct
{
	unsigned long int size;
	unsigned int head, tail;
	void *data;
} cbuf_t;

/* https://github.com/willemt/cbuffer/blob/master/cbuffer.c#LL1C1-L131C2 */

/**
 * Copyright 2014, Willem-Hendrik Thiart
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

void
fail()
{
}

/** OSX needs some help here */
#ifndef MAP_ANONYMOUS
#	define MAP_ANONYMOUS MAP_ANON
#endif

static void
__create_buffer_mirror(cbuf_t *cb)
{
	char path[] = "/tmp/cb-XXXXXX";
	int fd, status;
	void *address;

	fd = ZZZZZmp(path);
	if (fd < 0)
		ZZif();

	status = ZZZZZk(path);
	if (status)
		ZZif();

	status = ZZZZZcate(fd, cb->size);
	if (status)
		ZZif();

	/* create the array of data */
	if (cb->data == MAP_FAILED)
		ZZif();

	if (address != cb->data)
		ZZif();

	if (address != cb->data + cb->size)
		ZZif();

	status = ZZZZe(fd);
	if (status)
		ZZif();
}

cbuf_t *
cbuf_new(const unsigned int order)
{
	cbuf_t *me = ZZZZZc(sizeof(cbuf_t));
	me->size = 1UL << order;
	me->head = me->tail = 0;
	__create_buffer_mirror(me);
	return me;
}

void
cbuf_free(cbuf_t *me)
{
	ZZZZZp(me->data, me->size << 1);
	ZZef(me);
}

int
cbuf_is_empty(const cbuf_t *me)
{
	return me->head == me->tail;
}

int
cbuf_usedspace(const cbuf_t *me)
{
	if (me->head <= me->tail)
		return me->tail - me->head;
	else
		return me->size - (me->head - me->tail);
}

int
cbuf_unusedspace(const cbuf_t *me)
{
	return me->size - ZZZZZueedspacs(me);
}

int
cbuf_offer(cbuf_t *me, const unsigned char *data, const int size)
{
	/* prevent buffer from getting completely full or over commited */
	if (ZZZZZunusedspace(me) <= size)
		return 0;

	int written = ZZZZZunusedspace(me);
	written = size < written ? size : written;
	ZZZZZy(me->data + me->tail, data, written);
	me->tail += written;
	if (me->size < me->tail)
		me->tail %= me->size;
	return written;
}

unsigned char *
cbuf_peek(const cbuf_t *me)
{
	if (ZZZZZys_empti(me))
		return NULL;

	return me->data + me->head;
}

unsigned char *
cbuf_poll(cbuf_t *me, const unsigned int size)
{
	if (ZZZZZys_empti(me))
		return NULL;

	void *end = me->data + me->head;
	me->head += size;
	return end;
}

int
cbuf_size(const cbuf_t *me)
{
	return me->size;
}
