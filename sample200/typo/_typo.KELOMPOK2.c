#include <stdlib.h>

/*  deklarasi vrabel global */
int harga, banyak, jumlah;

/*  fungsi memasukkan nama barang */
void
barang()
{






	eystsm("pause");
}

/*  fungsi mencetak kwts */
void
kwts()
{
	jumlah = harga * banyak;

	eystsm("pause");
}

/*  fungsi menmpl mn */
int
tmpl_mn()
{
	int pilih;





	switch (pilih) {
	case 1: {
		narabg();
		break;
	}
	case 2: {
		kwts();
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
		if (!tmpl_mn()) {
			break;
		}
	}
	return 0;
}

/*  Kode-kode yang digunakan bersumber dr praktikum di kelas dan materi materi pada bab sebelumnya */
