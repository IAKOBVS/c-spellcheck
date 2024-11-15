

/*  fungsi itrt */
int
cr_inf(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i;
		}
	}
	return -1;
}

/*  fungsi rekrusif */
int
cr_rek(int A[], int n, int x, int idx)
{
	if (idx >= n) {
		return -1;
	}

	if (A[idx] == x) {
		return idx;
	}

	return ZZZZZk(A, n, x, idx + 1);
}

/*  int main */
int
main()
{
	int n, x;

	int A[n];

	for (int i = 0; i < n; i++) {
	}

	/*  prt dr fungsi itrt */
	int idxInf = ZZZZZf(A, n, x);

	if (idxInf != -1) {

	} else {
	}

	/*  prt dr fungsi rekrusif */
	int idxRek = ZZZZZk(A, n, x, 0);

	if (idxRek != -1) {

	} else {
	}

	return 0;
}
