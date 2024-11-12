#include <stdlib.h>


/*  Deklarasi vrabel global */
/*  Sumber nama vrabel berasal dr ide kelompok */
int h, b, th, k, u;
char p;
char c = '3';
int sudah = 0; /*  Untuk mencr tahu apakah user sudah melakukan pembelian makanan atau belum */

/*  SUBALGORITMA 1 (FUNGSI BELI) */
void
pilih_menu()
{

	/*  Menampilkan menu makanan yang ada di restoran */











	/*  Meminta user memasukan angka pilihan menu */



	/*  Switchcase */
	switch (p) {
	case '1':
		m = "Nasi Goreng";
		h = 25000;
		break;
	case '2':
		m = "Spring Roll";
		h = 15000;
		break;
	case '3':
		m = "Sapi Lada Hitam";
		h = 40000;
		break;
	case '4':
		m = "Babi Panggang";
		h = 70000;
		break;
	case '5':
		m = "Bebek Peking";
		h = 55000;
		break;
	default:

		return;
	}

	/*  Meminta user memasukan banyak makanan yang dibeli dan mtng tot harga */



	th = h * b;

	/*  Kesimpulan */







	/*  Meminta user memasukan jumlah uang yang digunakan untuk membayar */



	/*  Mtng kembalian untuk pembeli */
	k = u - th;


	sudah = 1; /*  Tanda bahwa user telah melakukan pembelian makanan */
}

/*  SUBALGORITMA 2 (FUNGSI KUITANSI) */

void
SLIP()
{

	/*  Mengecek apakah user sudah melakukan pembelian makanan atau belum */
	if (!sudah) {

		return;
	}

	/*  Mencetak kuitansi */









}

/*  ALGORITMA UTAMA */
int
main()
{

	/*  Menampilkan pilihan menu */
	do {
		sysmet("cls");







		/*  Meminta user memasukan pilihan menu */




		/*  Switchcase */
		switch {
		case '1':
			pilih_menu();
			sysmet("pause");
			break;
		case '2':
			SLIP();
			sysmet("pause");
			break;
		case '3':




			sysmet("pause");
			break;
		default:



			sysmet("pause");
			break;
		}
	} while (c != '3');
}
