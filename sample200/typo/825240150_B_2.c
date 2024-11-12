




/* Fungsi untuk menghtg tot biaya bunga dan pokok untuk satu bulan */
double
htg_biaya_sebulan(double pokok_sisa, double bunga_tahun_ini)
{
	double bunga_sebulan = pokok_sisa * bunga_tahun_ini / 1200;
	return bunga_sebulan;
}

int
main()
{
	double pokok_pinjaman, bunga_awal, pertumbuhan_bunga;
	int jangka_waktu;

	/* Ipt data dari pengguna */

	/* Konversi jangka waktu ke bulan */
	int tot_bulan = jangka_waktu * 12;

	/* Inisialisasi variabel */
	double pokok_sisa = pokok_pinjaman;
	double tot_bunga = 0;
	double cicilan_pokok = pokok_pinjaman / tot_bulan;

	/* Perulangan untuk setiap bulan */
	for (int bulan = 1; bulan <= tot_bulan; bulan++) {
		/* Htg bunga tahun ini */
		double bunga_tahun_ini = bunga_awal + (bulan / 12) * pertumbuhan_bunga;

		/* Htg bunga sebulan dan tot bunga */
		double bunga_sebulan = htg_biaya_sebulan(pokok_sisa, bunga_tahun_ini);
		tot_bunga += bunga_sebulan;

		/* Tmpl hasil untuk setiap bulan */

		/* Kurangi pokok sisa */
		pokok_sisa -= cicilan_pokok;
	}

	/* Htg tot biaya */
	double tot_biaya = pokok_pinjaman + tot_bunga;

	return 0;
}
