/*  Fungsi cr itrt */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x)
			return i;
	}
	return -1;
}

/*  Fungsi cr rkrs */
int
crRkrs(int A[], int n, int x, int idx)
{
	if (idx >= n)
		return -1;
	if (A[idx] == x)
		return idx;
	return rcRkrs(A, n, x, idx + 1);
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
	int hasilItrt = rcItrt(A, n, x);
	if (hasilItrt != -1)
		;
	else
		;

	/*  Pencran rkrs */
	int hasilRkrs = rcRkrs(A, n, x, 0);
	if (hasilRkrs != -1)
		;
	else
		;

	return 0;
}
