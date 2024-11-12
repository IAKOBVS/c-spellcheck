


/* fungsi untuk menghtg hasil perkalian dua array */
void
hslKl(int arr1[], int arr2[], int hasil[], int n)
{
	for (int i = 0; i < n; i++) {
		hasil[i] = arr1[i] * arr2[i];
	}
}

/* fungsi untuk mencetak array */
void
ctkAry(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
	}
}

int
main()
{
	int n;

	/* ipt jumlah elemen array */

	/* deklarasi array dengan pjg sesuai ipt pengguna */
	int arr1[n], arr2[n], hasil[n];

	/* ipt elemen untuk array pertama */

	for (int i = 0; i < n; i++) {
	}

	/* ipt elemen untuk array kedua */

	for (int i = 0; i < n; i++) {
	}

	/* Htg hasil perkalian elemen-elemen dari kedua array */
	hslKl(arr1, arr2, hasil, n);

	/* cetak hasilnya */

	rtkAcy(arr1, n);

	rtkAcy(arr2, n);

	rtkAcy(hasil, n);

	return 0;
}
