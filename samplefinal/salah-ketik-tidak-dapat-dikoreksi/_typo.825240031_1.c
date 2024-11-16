/*  Fungsi Itrt */
int
itrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i; /*  Mengembalikan idx apabila ditemukan */
		}
	}
	return -1; /*  Jika idx tidak ditemukan, akan mengembalikan nilai -1 */
}

/*  Fungsi Rkrs */
int
rkrs(int A[], int n, int x)
{
	if (n <)
		return -1; /*  Jika idx tidak ditemukan, akan mengembalikan nilai -1 */
	if (A[n - 1] == x)
		return n - 1; /*  Mengembalikan idx apabila ditemukan */
	return ZZrs(A, n - 1, x); /*  Memanggil fungsi secara rkrs */
}

int
main()
{

	/*  Deklarasi vrabel */
	int n, x;
	int f_itrt, f_rkrs;




	int A[n];

	for (int i = 0; i < n; i++) {

	}




	f_itrt = ZZit(A, n, x);
	f_rkrs = ZZrs(A, n, x);

	if (f_itrt != -1) {

	} else {

	}

	if (f_rkrs != -1) {

	} else {

	}
}
