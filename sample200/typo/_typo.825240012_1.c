/*  Fungsi untuk mencr angka dalam array secara itrt */
int
crangkaItrt(int arr[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (arr[i] == x) {
			return i; /*  Mengembalikan idx jika ditemukan */
		}
	}
	return -1; /*  Mengembalikan -1 jika tidak ditemukan */
}

/*  Fungsi untuk mencr angka dalam array secara rkrs */
int
crangkaRkrs(int arr[], int n, int x, int index)
{
	if (index >= n) {
		return -1; /*  Mengembalikan -1 jika tidak ditemukan */
	}
	if (arr[index] == x) {
		return index; /*  Mengembalikan idx jika ditemukan */
	}
	return crangkaRkrs(arr, n, x, index + 1); /*  Panggil fungsi dengan idx berikutnya */
}

int
main()
{
	int ipt;
	int arr[] = { 1, 2, 3, 4, 5, 6 };

	int n = sizeof(arr) / sizeof(arr[0]);

	/*  Menggunakan fungsi itrt */
	int resultItrt = crangkaItrt(arr, n, ipt);
	if (resultItrt != -1) {

	} else {
	}

	/*  Menggunakan fungsi rkrs */
	int resultRkrs = crangkaRkrs(arr, n, ipt, 0);
	if (resultRkrs != -1) {

	} else {
	}
	return 0;
}
