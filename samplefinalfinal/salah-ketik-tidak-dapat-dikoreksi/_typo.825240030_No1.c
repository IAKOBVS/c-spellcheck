

/*  Fungsi untuk mencr bilangan x secara itrt */
int
srchItrt(int A[], int size, int x)
{
	/*  Melakukan iterasi melalui array */
	for (int i = 0; i < size; i++) {
		/*  Jika elemen saat ini sama dengan x */
		if (A[i] == x) {
			return i; /*  Kembalikan idx */
		}
	}
	return -1; /*  Kembalikan -1 jika tidak ditemukan */
}

/*  Fungsi untuk mencr bilangan x secara rkrs */
int
srchRcrs(int A[], int size, int x, int index)
{
	/*  Basis: jika index sudah mencapai ukuran array */
	if (index >= size) {
		return -1; /*  Kembalikan -1 jika tidak ditemukan */
	}
	/*  Jika elemen pada index saat ini sama dengan x */
	if (A[index] == x) {
		return index; /*  Kembalikan idx */
	}
	/*  Rekursi untuk memeriksa elemen berikutnya */
	return ZZZZZcrs(A, size, x, index + 1);
}

/*  Fungsi utama */
int
main()
{
	/*  Inisialisasi array A */
	int A[] = { 10, 20, 30, 40, 50 };
	int size = sizeof(A) / sizeof(A[0]); /*  Mtng ukuran array */
	int x; /*  Vrabel untuk menyimpan ipt dr pengguna */

	/*  Meminta pengguna untuk memasukkan bilangan yang dicr */

	/*  Validasi ipt */

	return 1; /*  Keluar dr program dengan kode kesalahan */
	/*  Pencran menggunakan fungsi itrt */
	int resultItrt = ZZZZZtrt(A, size, x);
	if (resultItrt != -1) {

	} else {
	}

	/*  Pencran menggunakan fungsi rkrs */
	int resultRcrs = ZZZZZcrs(A, size, x, 0);
	if (resultRcrs != -1) {

	} else {
	}

	return 0; /*  Mengindikasikan bahwa program selesai dengan sukses */
}
