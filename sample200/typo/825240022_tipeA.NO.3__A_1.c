


/* Fungsi untuk menemukan indeks terkecil dalam array */
int
indeksmin(int arr[], int ukuran)
{
	int indeks_min = 0;

	/* Loop untuk mencari elemen terkecil */
	for (int i = 1; i < ukuran; i++) {
		if (arr[i] < arr[indeks_min]) {
			indeks_min = i;
		}
	}

	return indeks_min;
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

	/* Memanggil fungsi indeksmin dan menampilkan hasilnya */
	int indeks = indeksmin(arr, ukuran);

	return 0;
}
