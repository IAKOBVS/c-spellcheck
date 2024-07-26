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

typedef struct jtrie_node_ty {
	struct jtrie_node_ty *child[JTRIE_ASCII_SIZE];
	int EOW;
} jtrie_node_ty;

static jtrie_node_ty *
jtrie_alloc(void)
{
	return (jtrie_node_ty *)calloc(1, sizeof(jtrie_node_ty));
}

static void
jtrie__free(jtrie_node_ty *node)
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
jtrie_free(jtrie_node_ty **node)
{
	jtrie__free(*node);
}

static jtrie_ret_ty
jtrie_insert(jtrie_node_ty *root,
          const char *word)
{
	if (*word == '\0')
		return JTRIE_RET_SUCC;
	const unsigned char *w = (unsigned char *)word;
	jtrie_node_ty *curr = root;
	for (; *w; ++w) {
		if (curr->child[JTRIE_ASCII_IDX_GET(*w)] == NULL)
			curr->child[JTRIE_ASCII_IDX_GET(*w)] = jtrie_alloc();
		curr = curr->child[JTRIE_ASCII_IDX_GET(*w)];
		if (curr == NULL)
			return JTRIE_RET_ERR;
	}
	curr->EOW = 1;
	return JTRIE_RET_SUCC;
}

typedef enum {
	PJTRIE_FLAG_REMOVE_NOT_PREFIXES = 0,
	PJTRIE_FLAG_REMOVE_PREFIXES
} jtrie__flag_delete_prefixes_ty;

static void
jtrie__delete(jtrie__flag_delete_prefixes_ty flag,
              jtrie_node_ty *root,
              const char *word)
{
	if (*word == '\0')
		return;
	const unsigned char *w = (unsigned char *)word;
	jtrie_node_ty *curr = root->child[JTRIE_ASCII_IDX_GET(*w)];
	if (curr == NULL)
		return;
	while (*++w && curr->child[JTRIE_ASCII_IDX_GET(*w)]) {
		if (flag == PJTRIE_FLAG_REMOVE_PREFIXES)
			curr->EOW = 0;
		curr = curr->child[JTRIE_ASCII_IDX_GET(*w)];
	}
	curr->EOW = 0;
}

static void
jtrie_delete(jtrie_node_ty *root,
             const char *word)
{
	jtrie__delete(PJTRIE_FLAG_REMOVE_NOT_PREFIXES, root, word);
}

static void
jtrie_deleteprefixes(jtrie_node_ty *root,
                     const char *word)
{
	jtrie__delete(PJTRIE_FLAG_REMOVE_PREFIXES, root, word);
}

/*
   Return value:
   Pointer to node with last letter of WORD.
   NULL if not found.
*/
static jtrie_node_ty *
jtrie_starts(const jtrie_node_ty *root,
             const char *word)
{
	if (*word == '\0')
		return NULL;
	const unsigned char *w = (unsigned char *)word;
	const jtrie_node_ty *curr = root->child[JTRIE_ASCII_IDX_GET(*w)];
	if (curr == NULL)
		return NULL;
	for (; *++w && curr->child[JTRIE_ASCII_IDX_GET(*w)]; curr = curr->child[JTRIE_ASCII_IDX_GET(*w)]) {}
	return (jtrie_node_ty *)curr;
}

/*
   Return value:
   1 if matches;
   0 otherwise.
*/
static int
jtrie_match(const jtrie_node_ty *root,
            const char *word)
{
	const jtrie_node_ty *node = jtrie_starts(root, word);
	return node ? node->EOW : 0;
}


#undef R

#endif /* JTRIE_H */
