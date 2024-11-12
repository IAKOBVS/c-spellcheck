


/*  Fungsi itrt untuk mencr idx elemen x di array A */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i; /*  Mengembalikan idx jika ditemukan */
		}
	}
	return -1; /*  Mengembalikan -1 jika tidak ditemukan */
}

/*  Fungsi rkrs untuk mencr idx elemen x di array A */
int
crRkrs(int A[], int n, int x, int index )
{
	if (index >= n) {
		return -1; /*  Mengembalikan -1 jika tidak ditemukan */
	}
	if (A[index] == x) {
		return index; /*  Mengembalikan idx jika ditemukan */
	}
	return crRkrs(A, n, x, index + 1); /*  Melanjutkan cr dengan elemen berikutnya */
}

int
main()
{
	int n, x;




	int A[n];

	for (int i = 0; i < n; i++) {


	}




	/*  Pencran secara itrt */
	int hasilItrt = crItrt(A, n, x);
	if (hasilItrt != -1) {

	} else {

	}

	/*  Pencran secara rkrs */
	int hasilRkrs = crRkrs(A, n, x, 0);
	if (hasilRkrs != -1) {

	} else {

	}

	return 0;
}
