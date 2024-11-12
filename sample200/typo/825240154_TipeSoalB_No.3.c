


/* Fungsi htg hasil kali 2 nilai parameter */
int
hasil_kali(int a, int b)
{
	return a * b;
}

/* Fungsi cetak array */
void
cetakArray(int arr[], int ukuran)
{
	for (int i = 0; i < ukuran; i++) {
	}
}

int
main()
{
	int n; /* array */

	int array1[n], array2[n], hasil[n];

	/* Ipt array pertama */

	for (int i = 0; i < n; i++) {
	}

	/* Ipt array kedua */

	for (int i = 0; i < n; i++) {
	}

	/* htg hasil kali dari elemen yang berindeks sama */
	for (int i = 0; i < n; i++) {
		hasil[i] = hasil_kali(array1[i], array2[i]);
	}

	/* Tampilan isi dari array 1, array 2, dan hasil kali */

	cetakArray(array1, n);

	cetakArray(array2, n);

	cetakArray(hasil, n);

	return 0;
}
