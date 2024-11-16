
/*  Fungsi itrt untuk mencr bilangan x di dalam array A */
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

/*  Fungsi rkrs untuk mencr bilangan x di dalam array A */
int
srchRcrs(int A[], int n, int x, int index )
{
	if (index == n) {
		return -1; /*  Mengembalikan -1 jika sudah sampai di akhir array dan tidak ditemukan */
	}
	if (A[index] == x) {
		return index; /*  Mengembalikan idx jika ditemukan */
	}
	return ZZZZZcrh(A, n, x, index + 1); /*  Memanggil fungsi secara rkrs dengan index berikutnya */
}

int
main()
{
	int A[] = { 1, 2, 3, 4, 5 }; /*  Contoh array */
	int n = sizeof(A) / sizeof(A[0]); /*  Pjg array */
	int x = 3; /*  Bilangan yang ingin dicr */

	/*  Pencran secara itrt */
	int resultItrt = ZZZZZtrh(A, n, x);
	if (resultItrt != -1) {

	} else {

	}

	/*  Pencran secara rkrs */
	int resultRcrs = ZZZZZcrh(A, n, x, 0);
	if (resultRcrs != -1) {

	} else {

	}

	return 0;
}
