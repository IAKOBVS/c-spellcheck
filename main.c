#include "lib.c"
#include <stdio.h>
#include <sys/stat.h>
#define FNAME "/tmp/lib.c"
int
main()
{
	FILE *fp = fopen(FNAME, "r");
	struct stat st;
	stat(FNAME, &st);
	char *s = xmalloc((size_t)(st.st_size + 1));
	fread(s, (size_t)st.st_size, 1, fp);
	fclose(fp);
	s[st.st_size] = '\0';
	const char *p = s;
	const char *next;
	fns_ty *head = cs_fns_alloc();
	fns_ty *f = head;
	for (; (f->data = cs_fn_alloc(p, &next)); p = next) {
		f->next = cs_fns_alloc();
		f = f->next;
	}
	f = head;
	for (; f->data; f = f->next) {
		puts(f->data);
		if (!f->next)
			break;
	}
	cs_fns_freeall(head);
	return 0;
}
