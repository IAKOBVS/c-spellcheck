/*  Fungsi pencran itrt */
int
pencranItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x)
			return i;
	}
	return -1;
}

/*  Fungsi pencran rkrs */
int
pencranRkrs(int A[], int n, int x, int idx)
{
	if (idx >= n)
		return -1;
	if (A[idx] == x)
		return idx;
	return pencranRkrs(A, n, x, idx + 1);
}

int
main()
{
	int n, x;

	/*  Ipt jumlah elemen array dr pengguna */

	int A[n];

	/*  Ipt elemen array dr pengguna */

	for (int i = 0; i < n; i++) {
	}

	/*  Ipt angka yang dicr dr pengguna */

	/*  Pencran itrt */
	int hasilItrt = pencranItrt(A, n, x);
	if (hasilItrt != -1)
		;
	else
		;

	/*  Pencran rkrs */
	int hasilRkrs = pencranRkrs(A, n, x, 0);
	if (hasilRkrs != -1)
		;
	else
		;

	return 0;
}
