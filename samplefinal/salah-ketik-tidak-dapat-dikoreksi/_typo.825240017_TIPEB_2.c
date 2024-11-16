
 /* untuk memanipulasi */


/* Fungsi menghtg tot biaya bunga dan pokok */
void
htgBiayaKPR(double pinjaman, double bungaAwal, int tenor)
{
	double cicilanPokok = pinjaman / (tenor * 12); /* cicilan pokok per bulan */
	double totBiayaBunga = 0;
	double totBiaya = 0;
	double saldoPokok = pinjaman;

	for (int tahun = 0; tahun < tenor; ++tahun) {
		for (int bulan = 1; bulan <= 12; ++bulan) {
			double bunga = (saldoPokok * (bungaAwal / 100)) / 12; /* bunga per bulan */
			totBiayaBunga += bunga;
			totBiaya += cicilanPokok + bunga;
			saldoPokok -= cicilanPokok;
		}
		bungaAwal += 1; /* Pertumbuhan bunga  tiap tahun */
	}
}

int
main()
{
	double pinjaman, bungaAwal;
	int tenor;

	/* Ipt pinjaman, bunga, dan tenor */

	/* Memanggil fungsi untuk menghtg biaya KPR */
	ZZZZZayaKPi(pinjaman, bungaAwal, tenor);

	return 0;
}
