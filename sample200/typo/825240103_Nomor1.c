

/*  fungsi itrt untuk mencr x di array A mulai dr idx tertentu */
int
crItrt(int A[], int n, int x, int start)
{
	for (int i = start; i < n; ++i) {
		if (A[i] == x) {
			return i; /*  kembalikan idx jika ditemukan */
		}
	}
	return -1; /*  kembalikan -1 kalau nggak ketemu */
}

/*  fungsi rkrs untuk mencr x di array A */
int
crRkrs(int A[], int n, int x, int start)
{
	/*  kalau sudah habis idxnya (basis kasus) */
	if (start >= n) {
		return -1; /*  nggak ketemu, kembalikan -1 */
	}

	/*  coba cr menggunakan metode itrt mulai dr idx 'start' */
	int result = crItrt(A, n, x, start);

	/*  kalau ketemu, langsung kembalikan hasilnya */
	if (result != -1) {
		return result;
	}

	/*  kalau belum ketemu, lanjutkan pencran di idx berikutnya */
	return crRkrs(A, n, x, start + 1);
}

int
main()
{
	/*  inisialisasi array dan vrabel pencran */
	int A[] = { 3, 8, 1, 7, 9, 2 }; /*  array contoh */
	int n = sizeof(A) / sizeof(A[0]); /*  ukuran array */
	int x;

	/*  minta ipt angka yang mau dicr */

	/*  cr angka tersebut dengan gabungan rkrs dan itrt */
	int idx = crRkrs(A, n, x, 0);

	/*  tampilkan hasil pencran */
	if (idx != -1) {

	} else {
	}

	return 0;
}
