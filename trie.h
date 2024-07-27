/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 James Tirta Halim <tirtajames45 at gmail dot com>
 * This file is part of c-spellcheck.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#ifndef JTRIE_H
#define JTRIE_H 1

#include <stdlib.h>

#ifndef JTRIE_ASCII_SIZE
#  define JTRIE_ASCII_SIZE 256
#endif

#ifndef JTRIE_ASCII_IDX_GET
#  define JTRIE_ASCII_IDX_GET(c) c
#endif

typedef enum {
	JTRIE_RET_SUCC = 0,
	JTRIE_RET_ERR = 1
} jtrie_ret_ty;

typedef struct jtrie_ty {
	struct jtrie_ty *child[JTRIE_ASCII_SIZE];
	int EOW;
} jtrie_ty;

static jtrie_ty *
jtrie_alloc(void)
{
	return (jtrie_ty *)calloc(1, sizeof(jtrie_ty));
}

static void
jtrie__free(jtrie_ty *node)
{
	if (node == NULL)
		return;
	int i;
	for (i = 0; i < JTRIE_ASCII_SIZE; ++i)
		jtrie__free(node->child[i]);
	free(node);
	node = NULL;
}

static void
jtrie_free(jtrie_ty **node)
{
	jtrie__free(*node);
}

static jtrie_ret_ty
jtrie_insert(jtrie_ty *root,
          const char *word)
{
	if (*word == '\0')
		return JTRIE_RET_SUCC;
	const unsigned char *w = (unsigned char *)word;
	jtrie_ty *node = root;
	for (; *w; ++w) {
		if (node->child[JTRIE_ASCII_IDX_GET(*w)] == NULL)
			node->child[JTRIE_ASCII_IDX_GET(*w)] = jtrie_alloc();
		node = node->child[JTRIE_ASCII_IDX_GET(*w)];
		if (node == NULL)
			return JTRIE_RET_ERR;
	}
	node->EOW = 1;
	return JTRIE_RET_SUCC;
}

typedef enum {
	PJTRIE_FLAG_REMOVE_NOT_PREFIXES = 0,
	PJTRIE_FLAG_REMOVE_PREFIXES
} jtrie__flag_delete_prefixes_ty;

static void
jtrie__delete(jtrie__flag_delete_prefixes_ty flag,
              jtrie_ty *root,
              const char *word)
{
	if (*word == '\0')
		return;
	const unsigned char *w = (unsigned char *)word;
	jtrie_ty *node = root->child[JTRIE_ASCII_IDX_GET(*w)];
	if (node == NULL)
		return;
	while (*++w && node->child[JTRIE_ASCII_IDX_GET(*w)]) {
		if (flag == PJTRIE_FLAG_REMOVE_PREFIXES)
			node->EOW = 0;
		node = node->child[JTRIE_ASCII_IDX_GET(*w)];
	}
	node->EOW = 0;
}

static void
jtrie_delete(jtrie_ty *root,
             const char *word)
{
	jtrie__delete(PJTRIE_FLAG_REMOVE_NOT_PREFIXES, root, word);
}

static void
jtrie_deleteprefixes(jtrie_ty *root,
                     const char *word)
{
	jtrie__delete(PJTRIE_FLAG_REMOVE_PREFIXES, root, word);
}

/*
   Return value:
   Pointer to node with last letter of WORD.
   NULL if not found.
*/
static jtrie_ty *
jtrie_starts(const jtrie_ty *root,
             const char *word)
{
	if (*word == '\0')
		return NULL;
	const unsigned char *w = (unsigned char *)word;
	const jtrie_ty *node = root->child[JTRIE_ASCII_IDX_GET(*w)];
	if (node == NULL)
		return NULL;
	for (; *++w && node->child[JTRIE_ASCII_IDX_GET(*w)]; node = node->child[JTRIE_ASCII_IDX_GET(*w)]) {}
	return (jtrie_ty *)node;
}

/*
   Return value:
   1 if matches;
   0 otherwise.
*/
static int
jtrie_match(const jtrie_ty *root,
            const char *word)
{
	const jtrie_ty *node = jtrie_starts(root, word);
	return node ? node->EOW : 0;
}


#undef R

#endif /* JTRIE_H */
