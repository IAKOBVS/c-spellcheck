


/* proses perhtgan */
double
htg_tot_biaya_bunga_dan_pokok(double pinjaman, double bunga, int tenor)
{
	double tot_bunga = 0;
	double saldo_pinjaman = pinjaman;
	double cicilan_pokok = pinjaman / (tenor * 12);
	double bunga_tahun_ini = bunga;

	for (int tahun = 1; tahun <= tenor; ++tahun) {
		for (int bulan = 1; bulan <= 12; ++bulan) {
			double bunga_bulan_ini = saldo_pinjaman * (bunga_tahun_ini / 100) / 12;
			tot_bunga += bunga_bulan_ini;
			saldo_pinjaman -= cicilan_pokok;
		}
		bunga_tahun_ini += 1;
	}

	return tot_bunga + pinjaman;
}
/* program utama */
int
main()
{
	double pinjaman;
	double bunga;
	int tenor;

	double tot_biaya = htg_tot_biaya_bunga_dan_pokok(pinjaman, bunga, tenor);

	return 0;
}