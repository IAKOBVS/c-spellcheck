




/* Fungsi untuk menghtg tot biaya bunga dan pokok dari pinjaman */
void
htgTotBiaya(double pokokPinjaman, double sukuBunga, int tenor)
{
	double cicilanPokokPerBulan = pokokPinjaman / tenor;
	double totBiaya = 0.0;
	double totBunga = 0.0;

	for (int i = 1; i <= tenor; i++) {
		double bungaPerBulan = (pokokPinjaman * sukuBunga) / 12 / 100;
		double cicilanBulan = cicilanPokokPerBulan + bungaPerBulan;

		totBiaya += cicilanBulan;
		totBunga += bungaPerBulan;

		/* Update suku bunga untuk bulan berikutnya */
		if (i % 12 == 0) { /* Setiap tahun */
			sukuBunga += 1.0; /* Pertumbuhan bunga 1% tiap tahun */
		}
	}
}

int
main()
{
	double pokokPinjaman;
	double sukuBunga = 6.0; /* Bunga tahun pertama */
	int tenor;

	/* ipt data pengguna */

	/* htg tot biaya bunga dan pokok */
	ZZZZZtBiayo(pokokPinjaman, sukuBunga, tenor);
}
