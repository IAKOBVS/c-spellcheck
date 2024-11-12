




/* Fungsi untuk menghtg total biaya bunga dan pokok untuk satu bulan */
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
	int total_bulan = jangka_waktu * 12;

	/* Inisialisasi variabel */
	double pokok_sisa = pokok_pinjaman;
	double total_bunga = 0;
	double cicilan_pokok = pokok_pinjaman / total_bulan;

	/* Perulangan untuk setiap bulan */
	for (int bulan = 1; bulan <= total_bulan; bulan++) {
		/* Htg bunga tahun ini */
		double bunga_tahun_ini = bunga_awal + (bulan / 12) * pertumbuhan_bunga;

		/* Htg bunga sebulan dan total bunga */
		double bunga_sebulan = htg_biaya_sebulan(pokok_sisa, bunga_tahun_ini);
		total_bunga += bunga_sebulan;

		/* Tampilkan hasil untuk setiap bulan */

		<< ", Pokok Sisa = Rp " << pokok_sisa << endl;

		/* Kurangi pokok sisa */
		pokok_sisa -= cicilan_pokok;
	}

	/* Htg total biaya */
	double total_biaya = pokok_pinjaman + total_bunga;

	return 0;
}
