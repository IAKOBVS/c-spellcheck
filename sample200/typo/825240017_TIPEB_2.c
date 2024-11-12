
 /* untuk memanipulasi */


/* Fungsi menghtg total biaya bunga dan pokok */
void
htgBiayaKPR(double pinjaman, double bungaAwal, int tenor)
{
	double cicilanPokok = pinjaman / (tenor * 12); /* cicilan pokok per bulan */
	double totalBiayaBunga = 0;
	double totalBiaya = 0;
	double saldoPokok = pinjaman;

	for (int tahun = 0; tahun < tenor; ++tahun) {
		for (int bulan = 1; bulan <= 12; ++bulan) {
			double bunga = (saldoPokok * (bungaAwal / 100)) / 12; /* bunga per bulan */
			totalBiayaBunga += bunga;
			totalBiaya += cicilanPokok + bunga;
			saldoPokok -= cicilanPokok;

			<< cicilanPokok << "\t\t"
			<< bunga << "\t\t"
			<< (cicilanPokok + bunga) << "\t\t"
			<< saldoPokok << endl;
		}
		bungaAwal += 1; /* Pertumbuhan bunga (1%) tiap tahun */
	}
}

int
main()
{
	double pinjaman, bungaAwal;
	int tenor;

	/* Ipt pinjaman, bunga, dan tenor */

	/* Memanggil fungsi untuk menghtg biaya KPR */
	htgBiayaKPR(pinjaman, bungaAwal, tenor);

	return 0;
}
