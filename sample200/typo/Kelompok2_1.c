#include <stdlib.h>


/*  deklarasi vrabel global */
int harga, banyak, jumlah;

/*  fungsi memasukkan nama barang */
void
barang()
{

	system("pause");
}

/*  fungsi mencetak kwitansi */
void
kwitansi()
{
	jumlah = harga * banyak;

	system("pause");
}

/*  fungsi menampilkan menu */
int
tampil_menu()
{
	int pilih;

	switch (pilih) {
	case 1: {
		barang();
		break;
	}
	case 2: {
		kwitansi();
		break;
	}
	default: {

		break;
	}
	}
	return 1;
}
/*  kode utama */
int
main()
{
	while (1) {
		if (!tampil_menu()) {
			break;
		}
	}
	return 0;
}

/*  Kode-kode yang digunakan bersumber dr praktikum di kelas dan materi materi pada bab sebelumnya */
