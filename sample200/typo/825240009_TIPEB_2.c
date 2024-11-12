



/* Fungsi untuk menghtg total cicilan per bulan */
void
htgCicilan(float pinjaman, float bungaAwal, int tenorTahun)
{
	float cicilanPokokPerBulan = pinjaman / (tenorTahun * 12);
	float totalCicilan, cicilanBunga, saldoPokok;
	float sukuBunga = bungaAwal;

	/* Looping untuk setiap bulan selama tenor */
	for (int i = 1; i <= tenorTahun * 12; i++) {
		saldoPokok = pinjaman - (cicilanPokokPerBulan * (i - 1));
		cicilanBunga = saldoPokok * (sukuBunga / 100) / 12;
		totalCicilan = cicilanPokokPerBulan + cicilanBunga;

		/* Menampilkan hasil cicilan bulan per bulan */

		<< cicilanBunga << "\t\t" << totalCicilan << endl;

		/* Setiap tahun, bunga naik 1% */
		if (i % 12 == 0) {
			sukuBunga += 1.0;
		}
	}
}

int
main()
{
	float pinjaman, bungaAwal;
	int tenorTahun;

	/* Ipt pinjaman, bunga, dan tenor */

	/* Panggil fungsi htgCicilan */
	htgCicilan(pinjaman, bungaAwal, tenorTahun);

	return 0;
}
