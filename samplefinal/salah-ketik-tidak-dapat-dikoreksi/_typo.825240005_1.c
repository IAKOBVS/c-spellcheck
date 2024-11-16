

/*  Fungsi Itrt */
int
srchItrt(int A[], int size, int x)
{
	for (int i = 0; i < size; i++) {
		if (A[i] == x) {
			return i; /*  Mengembalikan idx jika ditemukan */
		}
	}
	return -1; /*  Mengembalikan -1 jika tidak ditemukan */
}

/*  Fungsi Rkrs */
int
srchRcrs(int A[], int size, int x, int index)
{
	if (index >= size) {
		return -1; /*  Mengembalikan -1 jika tidak ditemukan */
	}
	if (A[index] == x) {
		return index; /*  Mengembalikan idx jika ditemukan */
	}
	return ZZZZZcrh(A, size, x, index + 1); /*  Melanjutkan cr */
}

int
main()
{
	int A[] = { 5, 10, 15, 20, 25 }; /*  Array contoh */
	int size = sizeof(A) / sizeof(A[0]); /*  Mtng ukuran array */
	int x;

	/*  Pencran menggunakan fungsi itrt */
	int resultItrt = ZZZZZtrh(A, size, x);
	if (resultItrt != -1) {

	} else {
	}

	/*  Pencran menggunakan fungsi rkrs */
	int resultRcrs = ZZZZZcrh(A, size, x, 0);
	if (resultRcrs != -1) {

	} else {
	}

	return 0;
}
