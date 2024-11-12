#include <math.h>

/* Fungsi untuk menghtg angsuran per bulan */
double
htg_angsuran(double pokok_pinjaman, double suku_bunga, int tahun)
{
	double bunga_bulanan = suku_bunga / 12 / 100;
	int bulan = tahun * 12;
	double angsuran = (pokok_pinjaman * bunga_bulanan) / (1 - pow(1 + bunga_bulanan, -bulan));
	return angsuran;
}

/* Program utama */
int
main()
{
	double jumlah_pinjaman, suku_bunga;
	int tahun;

	/* Ipt data pinjaman */

	/* Htg angsuran per bulan */
	double angsuran_bulanan = htg_angsuran(jumlah_pinjaman, suku_bunga, tahun);
	double tot_pembayaran = angsuran_bulanan * tahun * 12;

	/* tmpl hasil */

	return 0;
}
