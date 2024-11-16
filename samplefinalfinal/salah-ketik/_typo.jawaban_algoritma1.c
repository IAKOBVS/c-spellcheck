

/*  Fungsi itrt untuk mencr bilangan x di array A */
int
srchItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i; /*  Mengembalikan idx jika ditemukan */
		}
	}
	return -1; /*  Mengembalikan -1 jika tidak ditemukan */
}

/*  Fungsi rkrs untuk mencr bilangan x di array A */
int
srchRcrs(int A[], int n, int x, int index)
{
	if (index >= n) {
		return -1; /*  Basis: Mengembalikan -1 jika tidak ditemukan */
	}
	if (A[index] == x) {
		return index; /*  Mengembalikan idx jika ditemukan */
	}
	return srchRcrs(A, n, x, index + 1); /*  Rekurens: Lanjut ke idx berikutnya */
}

int
main()
{
	int A[] = { 3, 5, 2, 9, 6 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 9;

	int itrtResult = srchItrt(A, n, x);
	int rcrsResult = srchRcrs(A, n, x, 0);

	if (itrtResult != -1) {

	} else {
	}

	if (rcrsResult != -1) {

	} else {
	}

	return 0;
}
