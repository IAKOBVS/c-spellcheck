#include <stdlib.h>

/*  function for PTKP */
long
htgPTKP(char menikah, int tanggungan)
{
	long ptkp = 54000000; /*  PTKP standar untuk lajang */
	if (menikah == 'y' || menikah == 'Y') {
		ptkp += 4500000; /*  Tambahan PTKP untuk yang sudah menikah */
	}
	if (tanggungan > 0) {
		if (tanggungan > 3)
			tanggungan = 3; /*  Maksimal 3 tanggungan */
		ptkp += tanggungan * 4500000; /*  Tambahan PTKP per tanggungan */
	}
	return ptkp;
}

/*  function for PKP */
long
htgPKP(long gaji_tahunan, char menikah, int tanggungan)
{
	long ptkp = htgPTKP(menikah, tanggungan);
	if (gaji_tahunan <= ptkp) {
		return 0; /*  Gaji di bawah atau sama dengan PTKP, tidak ada PKP */
	}
	return gaji_tahunan - ptkp; /*  PKP adalah selisih antara gaji tahunan dan PTKP */
}

int
main()
{
	long ptkp = 0, pkp = 0, gaji_tahunan, pph21;
	int pilihan, tanggungan = 0;
	char menikah;

	do {

		/*  Tampilkan Menu */

		switch (pilihan) {
		case 1: {

			if (gaji_tahunan < 54000000) {

				system("pause");
				break;
			}

			/*  Meminta ipt status pernikahan */

			/*  Ipt jumlah tanggungan hanya jika menikah */
			if (menikah == 'y' || menikah == 'Y') {

			} else if (menikah != 'y' || menikah != 'Y') {

			} else {
			}

			ptkp = htgPTKP(menikah, tanggungan);

			if (gaji_tahunan <= ptkp) {
			}
			system("pause");
			break;
		}
		case 2: {

			if (gaji_tahunan < 54000000) {

				system("pause");
				break;
			}

			/*  Meminta ipt status pernikahan */

			/*  Ipt jumlah tanggungan hanya jika menikah */
			if (menikah == 'y' || menikah == 'Y') {

			} else {
				tanggungan = 0; /*  Set tanggungan ke 0 jika belum menikah */
			}

			ptkp = htgPTKP(menikah, tanggungan);

			if (gaji_tahunan < ptkp) {

				system("pause");
				break;
			}

			pkp = htgPKP(gaji_tahunan, menikah, tanggungan);

			/*  Htg PPh 21 berdasarkan PKP */
			if (pkp <= 50000000) {
				pph21 = pkp * 0.05; /*  Trf pajak 5% untuk PKP sampai Rp 50.000.000 */
			} else if (pkp <= 250000000) {
				pph21 = 50000000 * 0.05; /*  Trf 5% untuk lapisan pertama */
				pph21 += (pkp - 50000000) * 0.15; /*  Trf 15% untuk PKP lebih dr Rp 50.000.000 */
			} else if (pkp <= 500000000) {
				pph21 = 50000000 * 0.05; /*  Trf 5% untuk lapisan pertama */
				pph21 += 200000000 * 0.15; /*  Trf 15% untuk lapisan kedua */
				pph21 += (pkp - 250000000) * 0.25; /*  Trf 25% untuk PKP lebih dr Rp 250.000.000 */
			} else {
				pph21 = 50000000 * 0.05; /*  Trf 5% untuk lapisan pertama */
				pph21 += 200000000 * 0.15; /*  Trf 15% untuk lapisan kedua */
				pph21 += 250000000 * 0.25; /*  Trf 25% untuk lapisan ketiga */
				pph21 += (pkp - 500000000) * 0.30; /*  Trf 30% untuk PKP lebih dr Rp 500.000.000 */
			}

			system("pause");
			break;
		}

		case 0: {
			/*  Keluar dr program */

			break;
		}

		default: {
			/*  Jika ipt pilihan salah */

			break;
		}
		}

	} while (pilihan != 0);

	return 0;
}
