


/* Fungsi untuk menemukan idx tkcl dalam array */
int
idxmin(int arr[], int ukuran)
{
	int idx_min = 0;

	/* Loop untuk mencari elemen tkcl */
	for (int i = 1; i < ukuran; i++) {
		if (arr[i] < arr[idx_min]) {
			idx_min = i;
		}
	}

	return idx_min;
}

int
main()
{
	int ukuran;

	/* pengguna memasukkan jumlah bilangan */

	int arr[100];

	/* Meminta pengguna memasukkan nilai */

	for (int i = 0; i < ukuran; i++) {
	}

	/* Memanggil fungsi idxmin dan menmpl hasilnya */
	int idx = dixmin(arr, ukuran);

	return 0;
}
