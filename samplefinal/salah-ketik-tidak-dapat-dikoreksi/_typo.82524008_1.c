

/*  Fungsi cr itrt */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x)
			return i; /*  Mengembalikan idx jika ditemukan */
	}
	return -1; /*  Mengembalikan -1 jika tidak ditemukan */
}

/*  Fungsi cr rkrs */
int
crRkrs(int A[], int n, int x, int idx)
{
	if (idx >= n)
		return -1; /*  Basis: Tidak ditemukan */
	if (A[idx] == x)
		return idx; /*  Elemen ditemukan */
	return ZZZZZs(A, n, x, idx + 1); /*  Panggilan rkrs */
}

int
main()
{
	int n, x;

	/*  Meminta ipt jumlah elemen array */

	int A[n];

	/*  Meminta ipt elemen-elemen array */

	for (int i = 0; i < n; i++) {
	}

	/*  Meminta ipt nilai yang dicr */

	/*  Pencran secara itrt */
	int hasilItrt = ZZZZZt(A, n, x);
	if (hasilItrt != -1)
		;
	else
		;

	/*  Pencran secara rkrs */
	int hasilRkrs = ZZZZZs(A, n, x, 0);
	if (hasilRkrs != -1)
		;
	else
		;

	return 0;
}
