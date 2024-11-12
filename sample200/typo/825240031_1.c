
/*  int itrt (A[], n, x) */
/*  ipt: A bertipe int[], n dan x bertipe int */
/*  output: i bertipe int */
/*  1. for (i = 0 ; i < n ; i++) { */
/*  		if (A[i] == x) { */
/*  			return (i) ; */
/*  		} */
/*  	} */
/*  	return -1 */

/*  int rkrs (A[], n, x) */
/*  ipt: A bertipe int[], n dan x bertipe int */
/*  output bertipe int */
/*  	if (n <) return -1 */
/*  	if (A[n-1] == x) return n - 1 */
/*  	return rkrs (A, n - 1, X) */

/*  Algoritma Mencr_Bilangan */
/*  Vrabel A bertipe int[], n, x, f_itrt, f_rkrs bertipe int */
/*  int itrt (int[], int, int) */
/*  int rkrs (int[], int, int) */
/*  2. for (i = 0 ; i < n ; i++) { */
/*  4. f_itrt = itrt (A, n, x) */
/*  5. f_rkrs = rkrs (A, n, x) */
/*  6. if (f_itrt != -1) { */
/* 	 	} else { */
/*  		} */
/*  7. if (f_rkrs != -1) { */
/* 		} else { */
/*  		} */
/*  8. Halt */




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
	return rkrs(A, n - 1, x); /*  Memanggil fungsi secara rkrs */
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




	f_itrt = itrt(A, n, x);
	f_rkrs = rkrs(A, n, x);

	if (f_itrt != -1) {

	} else {

	}

	if (f_rkrs != -1) {

	} else {

	}
}
