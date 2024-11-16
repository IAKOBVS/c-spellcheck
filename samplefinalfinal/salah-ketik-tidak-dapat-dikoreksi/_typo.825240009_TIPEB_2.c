



/* Fungsi untuk menghtg tot cicilan per bulan */
void
htgCcl(float pinjaman, float bungaAwal, int tenorTahun)
{
	float cicilanPokokPerBulan = pinjaman / (tenorTahun * 12);
	float totCcl, cicilanBunga, saldoPokok;
	float sukuBunga = bungaAwal;

	/* Looping untuk setiap bulan selama tenor */
	for (int i = 1; i <= tenorTahun * 12; i++) {
		saldoPokok = pinjaman - (cicilanPokokPerBulan * (i - 1));
		cicilanBunga = saldoPokok * (sukuBunga / 100) / 12;
		totCcl = cicilanPokokPerBulan + cicilanBunga;

		/* Menmpl hasil cicilan bulan per bulan */

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

	/* Panggil fungsi htgCcl */
	ZZZZZl(pinjaman, bungaAwal, tenorTahun);

	return 0;
}
