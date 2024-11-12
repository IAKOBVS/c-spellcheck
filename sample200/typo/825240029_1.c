


/*  Fungsi itrt untuk mencr bilangan x di array A */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i; /*  Mengembalikan idx jika x ditemukan */
		}
	}
	return -1; /*  Mengembalikan -1 jika x tidak ditemukan */
}

/*  Fungsi rkrs untuk mencr bilangan x di array A */
int
crRkrs(int A[], int n, int x)
{
	if (n == 0) {
		return -1; /*  Mengembalikan -1 jika x tidak ditemukan (base case) */
	}
	if (A[n - 1] == x) {
		return n - 1; /*  Mengembalikan idx jika x ditemukan */
	}
	return crRkrs(A, n - 1, x); /*  Memanggil fungsi rkrs untuk elemen selanjutnya */
}

int
main()
{
	int A[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(A) / sizeof(A[0]);
	int x;
	int counter = 0; /*  Mtng jumlah masukan */

	while (counter < 3) { /*  Loop akan berhenti setelah 3 masukan */



		/*  Mencr x secara itrt */
		int idxItrt = crItrt(A, n, x);
		if (idxItrt != -1) {

		} else {

		}

		/*  Mencr x secara rkrs */
		int idxRkrs = crRkrs(A, n, x);
		if (idxRkrs != -1) {

		} else {

		}

		counter++; /*  Increment counter setiap kali pengguna memasukkan bilangan */
	}


	return 0;
}
