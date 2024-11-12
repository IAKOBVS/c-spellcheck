


/*
Algoritma:
1. Fungsi itrt:
   -Loop seluruh elemen array A.
   -Jika ditemukan elemen yang sama dengan x, kembalikan idx elemen tersebut
   -Jika tidak ditemukan, kembalikan -1

2. Fungsi rkrs:
   -Mulai dengan idx 0
   -Periksa apakah elemen array pada idx tersebut sama dengan x
   -Jika ya, kembalikan idx
   -Jika tidak, lanjutkan cr dengan memanggil fungsi rkrs pada idx berikutnya
   -Jika idx lebih besar atau sama dengan pjg array, kembalikan -1
*/

/*  Fungsi itrt untuk mencr bilangan x dalam array A */
int
crItrt(int A[], int n, int x)
{

	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i;
		}
	}
	return -1;
}

/*  Fungsi rkrs untuk mencr bilangan x dalam array A */
int
crRkrs(int A[], int n, int x, int idx )
{

	if (idx >= n) {
		return -1;
	}

	if (A[idx] == x) {
		return idx;
	}

	return crRkrs(A, n, x, idx + 1);
}

int
main()
{
	/*  Array A yang berisi deret bilangan */
	int A[] = { 10, 20, 30, 40, 50 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 30;

	/*  Menggunakan fungsi itrt */
	int idxItrt = crItrt(A, n, x);
	if (idxItrt != -1) {

	} else {

	}

	/*  Menggunakan fungsi rkrs */
	int idxRkrs = crRkrs(A, n, x, 0);
	if (idxRkrs != -1) {

	} else {

	}

	return 0;
}
