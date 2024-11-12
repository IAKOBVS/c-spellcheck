


/* fungsi untuk menghtg hasil perkalian dua array */
void
hasilKali(int arr1[], int arr2[], int hasil[], int n)
{
	for (int i = 0; i < n; i++) {
		hasil[i] = arr1[i] * arr2[i];
	}
}

/* fungsi untuk mencetak array */
void
cetakArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
	}
}

int
main()
{
	int n;

	/* ipt jumlah elemen array */

	/* deklarasi array dengan panjang sesuai ipt pengguna */
	int arr1[n], arr2[n], hasil[n];

	/* ipt elemen untuk array pertama */

	for (int i = 0; i < n; i++) {
	}

	/* ipt elemen untuk array kedua */

	for (int i = 0; i < n; i++) {
	}

	/* Htg hasil perkalian elemen-elemen dari kedua array */
	hasilKali(arr1, arr2, hasil, n);

	/* cetak hasilnya */

	cetakArray(arr1, n);

	cetakArray(arr2, n);

	cetakArray(hasil, n);

	return 0;
}
