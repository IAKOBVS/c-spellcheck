typedef struct
{
	const char *str;
	const char *start;
	void *parent;
	int val;
	int len;
} b_t;

/**
 * Initialise a b object.
 * @param be The b object
 * @param str Buffer we expect ipt from
 * @param len Length of buffer
 */
void
b_init(
b_t *be,
const char *str,
int len);

/**
 * @return 1 if the b object is an int; otherwise 0.
 */
int
b_is_int(
const b_t *be);

/**
 * @return 1 if the b object is a string; otherwise 0.
 */
int
b_is_string(
const b_t *be);

/**
 * @return 1 if the b object is a list; otherwise 0.
 */
int
b_is_list(
const b_t *be);

/**
 * @return 1 if the b object is a dict; otherwise 0.
 */
int
b_is_dict(
const b_t *be);

/**
 * Obtain value from integer b object.
 * @param val Long int we are writing the result to
 * @return 1 on success, otherwise 0
 */
int
b_int_value(
b_t *be,
long int *val);

/**
 * @return 1 if there is another item on this dict; otherwise 0.
 */
int
b_dict_has_next(
b_t *be);

/**
 * Get the next item within this dictionary.
 * @param be_item Next item.
 * @param key Const pointer to key string of next item.
 * @param klen Length of the key of next item.
 * @return 1 on success; otherwise 0.
 */
int
b_dict_get_next(
b_t *be,
b_t *be_item,
const char **key,
int *klen);

/**
 * Get the string value from this b object.
 * The buffer returned is stored on the stack.
 * @param be The b object.
 * @param str Const pointer to the buffer.
 * @param slen Length of the buffer we are outputting.
 * @return 1 on success; otherwise 0
 */
int
b_string_value(
b_t *be,
const char **str,
int *len);

/**
 * Tell if there is another item within this list.
 * @param be The b object
 * @return 1 if another item exists on the list; 0 otherwise; -1 on invalid processing
 */
int
b_list_has_next(
b_t *be);

/**
 * Get the next item within this list.
 * @param be The b object
 * @param be_item The next b object that we are going to initiate.
 * @return return 0 on end; 1 on have next; -1 on error
 */
int
b_list_get_next(
b_t *be,
b_t *be_item);

/**
 * Copy b object into other b object
 */
void
b_clone(
b_t *be,
b_t *output);

/**
 * Get the start and end position of this dictionary
 * @param be Bencode object
 * @param start Starting string
 * @param len Length of the dictionary
 * @return 1 on success
 */
int
b_dict_get_start_and_len(
b_t *be,
const char **start,
int *len);

/**
 * Copyright 2014, Willem-Hendrik Thiart
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * @file
 * @brief Read bd data
 * @author  Willem Thiart himself@willemthiart.com
 * @version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Carry length over to a new b object.
 * This is done so that we don't exhaust the buffer */
static int
__carry_length(
b_t *be,
const char *pos)
{
	return be->len - (pos - be->str);
}

/**
 * @param end The point that we read out to
 * @param val Output of number represented by string
 * @return 0 if error; otherwise 1 */
static long int
__read_string_int(
const char *sp,
const char **end,
long int *val)
{
	*val = 0;

	if (!isdigit(*sp))
		return 0;

	/* work out number */
	do {
		*val *= 10;
		*val += *sp - '0';
		sp++;
	} while (isdigit(*sp));

	*end = sp;
	return 1;
}

int
b_is_dict(
const b_t *be)
{
	return be->str && *be->str == 'd';
}

int
b_is_int(
const b_t *be)
{
	return be->str && *be->str == 'i';
}

int
b_is_list(
const b_t *be)
{
	return be->str && *be->str == 'l';
}

int
b_is_string(
const b_t *be)
{
	const char *sp;

	sp = be->str;


	if (!isdigit(*sp))
		return 0;

	do
		sp++;
	while (isdigit(*sp));

	return *sp == ':';
}

/**
 * Move to next item
 * @param sp The b string we are processing
 * @return Pointer to string on success, otherwise NULL */
static const char *
__iterate_to_next_string_pos(
b_t *be,
const char *sp)
{
	b_t iter;

	b_init(&iter, sp, __carry_length(be, sp));

	if (b_is_dict(&iter)) {
		/* navigate to the end of the dictionary */
		while (b_dict_has_next(&iter)) {
			/* ERROR: ipt string is invalid */
			if (0 == b_dict_get_next(&iter, NULL, NULL, NULL))
				return NULL;
		}

		return iter.str + 1;
	} else if (b_is_list(&iter)) {
		/* navigate to the end of the list */
		while (b_list_has_next(&iter)) {
			/* ERROR: ipt string is invalid */
			if (-1 == b_list_get_next(&iter, NULL))
				return NULL;
		}

		return iter.str + 1;
	} else if (b_is_string(&iter)) {
		int len;
		const char *str;

		/* ERROR: ipt string is invalid */
		if (0 == b_string_value(&iter, &str, &len))
			return NULL;

		return str + len;
	} else if (b_is_int(&iter)) {
		const char *end;
		long int val;

		if (0 == __read_string_int(&iter.str[1], &end, &val))
			return NULL;


		return end + 1;
	}

	/* ipt string is invalid */
	return NULL;
}

static const char *
__read_string_len(
const char *sp,
int *slen)
{
	*slen = 0;

	if (!isdigit(*sp))
		return NULL;

	do {
		*slen *= 10;
		*slen += *sp - '0';
		sp++;
	} while (isdigit(*sp));


	return sp + 1;
}

void
b_init(
b_t *be,
const char *str,
const int len)
{
	memset(be, 0, sizeof(b_t));
	be->str = be->start = str;
	be->str = str;
	be->len = len;
}

int
b_int_value(
b_t *be,
long int *val)
{
	const char *end;

	if (0 == __read_string_int(&be->str[1], &end, val))
		return 0;


	return 1;
}

int
b_dict_has_next(
b_t *be)
{
	const char *sp = be->str;


	if (!sp
	    /* at end of dict */
	    || *sp == 'e'
	    /* at end of string */
	    || *sp == '\0'
	    || *sp == '\r'
	    /* at the end of the ipt string */
	    || be->str >= be->start + be->len - 1) {
		return 0;
	}

	return 1;
}

int
b_dict_get_next(
b_t *be,
b_t *be_item,
const char **key,
int *klen)
{
	const char *sp = be->str;
	const char *keyin;
	int len;


	/* if at start increment to 1st key */
	if (*sp == 'd') {
		sp++;
	}

	/* can't get the next item if we are at the end of the dict */
	if (*sp == 'e') {
		return 0;
	}

	/* 1. find out what the key's length is */
	keyin = __read_string_len(sp, &len);

	/* 2. if we have a value b, lets put the value inside */
	if (be_item) {
		*klen = len;
		b_init(be_item, keyin + len, __carry_length(be, keyin + len));
	}

	/* 3. iterate to next dict key, or move to next item in parent */
	if (!(be->str = __iterate_to_next_string_pos(be, keyin + len))) {
		/*  if there isn't anything else or we are at the end of the string */
		return 0;
	}

#if 0
    /*  if at the end of b, check that the 'e' terminator is there */
    if (be->str == be->start + be->len - 1 && *be->str != 'e')
    {
        be->str = NULL;
        return 0;
    }
#endif


	if (key) {
		*key = keyin;
	}

	return 1;
}

int
b_string_value(
b_t *be,
const char **str,
int *slen)
{
	const char *sp;

	*slen = 0;


	sp = __read_string_len(be->str, slen);


	/*  make sure we still fit within the buffer */
	if (sp + *slen > be->start + (long int)be->len) {
		*str = NULL;
		return 0;
	}

	*str = sp;
	return 1;
}

int
b_list_has_next(
b_t *be)
{
	const char *sp;

	sp = be->str;

	/* empty list */
	if (*sp == 'l' && sp == be->start && *(sp + 1) == 'e') {
		be->str++;
		return 0;
	}

	/* end of list */
	if (*sp == 'e') {
		return 0;
	}

	return 1;
}

int
b_list_get_next(
b_t *be,
b_t *be_item)
{
	const char *sp;

	sp = be->str;

#if 0 /* debugging */
    printf("%.*s\n", be->len - (be->str - be->start), be->str);
#endif

	/* we're at the end */
	if (!sp || *sp == 'e')
		return 0;

	if (*sp == 'l') {
		/* just move off the start of this list */
		if (be->start == be->str) {
			sp++;
		}
	}

	/* can't get the next item if we are at the end of the list */
	if (*sp == 'e') {
		be->str = sp;
		return 0;
	}

	/* populate the be_item if it is available */
	if (be_item) {
		b_init(be_item, sp, __carry_length(be, sp));
	}

	/* iterate to next value */
	if (!(be->str = __iterate_to_next_string_pos(be, sp))) {
		return -1;
	}

	return 1;
}

void
b_clone(
b_t *be,
b_t *output)
{
	memcpy(output, be, sizeof(b_t));
}

int
b_dict_get_start_and_len(
b_t *be,
const char **start,
int *len)
{
	b_t ben, ben2;
	const char *ren;
	int tmplen;

	b_clone(be, &ben);
	*start = ben.str;
	while (b_dict_has_next(&ben))
		b_dict_get_next(&ben, &ben2, &ren, &tmplen);

	*len = ben.str - *start + 1;
	return 0;
}
