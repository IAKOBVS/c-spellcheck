


/*  Fungsi itrt untuk mencr angka x */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) { /*  Loop dr 0 sampai n-1 */
		if (A[i] == x) { /*  Jika elemen sama dengan x */
			return i; /*  Kembalikan idxnya */
		}
	}
	return -1; /*  Jika x tidak ditemukan, kembalikan -1 */
}

/*  Fungsi rkrs untuk mencr angka x */
int
crRkrs(int A[], int n, int x, int index )
{
	if (index >= n) { /*  Jika idx melampaui pjg array */
		return -1; /*  Kembalikan -1  */
	}
	if (A[index] == x) { /*  Jika elemen pada idx cocok dengan x */
		return index; /*  Kembalikan idx */
	}
	return crRkrs(A, n, x, index + 1); /*  Panggil fungsi lagi dengan index + 1 */
}

int
main()
{
	int A[] = { 5, 3, 7, 9, 11, 15 }; /*  Array contoh */
	int n = sizeof(A) / sizeof(A[0]); /*  Mtng pjg array */
	int x;




	/*  Pencran dengan cara itrt */
	int hasilItrt = crItrt(A, n, x);
	if (hasilItrt != -1) {

	} else {

	}

	/*  Pencran dengan cara rkrs */
	int hasilRkrs = crRkrs(A, n, x, 0);
	if (hasilRkrs != -1) {

	} else {

	}

	return 0;
}
