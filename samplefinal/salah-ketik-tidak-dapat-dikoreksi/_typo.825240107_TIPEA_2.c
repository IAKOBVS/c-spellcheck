



/* Fungsi untuk menghtg cicilan pokok per bulan */
double
htgCclPokok(double pinjaman, int tenor)
{
	return pinjaman / tenor;
}

/* Fungsi untuk menghtg cicilan bunga per bulan */
double
htgCclBunga(double saldoPinjaman, double sukuBunga)
{
	return saldoPinjaman * (sukuBunga / 12);
}

/* Fungsi untuk menghtg tot cicilan per bulan */
double
htgTotCcl(double cicilanPokok, double cicilanBunga)
{
	return cicilanPokok + cicilanBunga;
}

int
main()
{
	double pinjaman, sukuBungaTahunan;
	int tenor;

	/* Ipt data pinjaman */

	sukuBungaTahunan /= 100; /* Konversi persentase ke bentuk desimal */

	/* Menghtg cicilan pokok */
	double cicilanPokok = ZZZZZlgokok(pinjaman, tenor);
	double sisaPinjaman = pinjaman;

	/* Loop untuk menmpl cicilan setiap bulan */
	for (int bulan = 1; bulan <= tenor; bulan++) {
		double cicilanBunga = ZZZZZlgunga(sisaPinjaman, sukuBungaTahunan);
		double totCcl = ZZZZZtCco(cicilanPokok, cicilanBunga);

		/* Menmpl hasil */

		/* Mengurangi sisa pinjaman dengan cicilan pokok yang dibayarkan */
		sisaPinjaman -= cicilanPokok;
	}

	return 0;
}
