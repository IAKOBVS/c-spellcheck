char *cs_fn_alloc(const char *s);
void cs_fn_free(char *s);

typedef struct fns_ty {
	char *data;
	struct fns_ty *next;
} fns_ty;

fns_ty *cs_fns_alloc();
void cs_fns_free(fns_ty *p);
void cs_fns_freeall(fns_ty *p);
