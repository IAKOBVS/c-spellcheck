


/*  Fungsi Itrt */
int
pencranItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i;
		}
	}
	return -1;
}

/*  Fungsi Rkrs */
int
pencranRkrs(int A[], int n, int x, int idx )
{
	if (idx >= n) {
		return -1;
	}
	if (A[idx] == x) {
		return idx;
	}
	return pencranRkrs(A, n, x, idx + 1);
}

int
main()
{
	int n = 5;
	int A[] = { 10, 20, 30, 40, 50 };
	int x = 30;

	/*  Mencr fungsi itrt */
	int hasilItrt = pencranItrt(A, n, x);


	/*  Mencr fungsi rkrs */
	int hasilRkrs = pencranRkrs(A, n, x, 0);


	return 0;
}
