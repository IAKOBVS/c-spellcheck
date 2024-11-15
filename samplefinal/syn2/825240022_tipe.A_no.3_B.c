


/* Fungsi untuk menemukan idx bilangan tbsr dalam array */
int
idxTbsr(int arr[], int ukuran)
{
	int idx_max = 0;

	/* Loop untuk mencari bilangan tbsr */
	for (int i = 1; i < ukuran; i++) {
		if (arr[i] > arr[idx_max]) {
			idx_max = i;
		}
	}

	return idx_max;
}

int
main()
{
	int ukuran;

	/* Meminta pengguna memasukkan jumlah bilangan */

	int arr[ukuran];

	/* Meminta pengguna memasukkan nilai */

	for (int i = 0; i < ukuran; i++) {
	}

	/* Memanggil fungsi idxTbsr dan menmpl hasilnya */
	int idx = idxTbsr(arr, ukuran);

	return 0;
}
