typedef struct fns_ty {
	char *data;
	struct fns_ty *next;
} fns_ty;

char *cs_file_read_alloc(const char *fname);
void cs_file_read_free(char *s);

char *cs_fn_alloc(const char *s);
void cs_fn_free(char *s);

fns_ty *cs_fns_alloc();
void cs_fns_free(fns_ty *p);
void cs_fns_freeall(fns_ty *p);
