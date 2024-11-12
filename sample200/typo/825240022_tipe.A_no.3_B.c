


/* Fungsi untuk menemukan indeks bilangan terbesar dalam array */
int
indeksTerbesar(int arr[], int ukuran)
{
	int indeks_max = 0;

	/* Loop untuk mencari bilangan terbesar */
	for (int i = 1; i < ukuran; i++) {
		if (arr[i] > arr[indeks_max]) {
			indeks_max = i;
		}
	}

	return indeks_max;
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

	/* Memanggil fungsi indeksTerbesar dan menampilkan hasilnya */
	int indeks = indeksTerbesar(arr, ukuran);

	return 0;
}
