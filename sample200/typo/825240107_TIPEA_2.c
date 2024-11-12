



/* Fungsi untuk menghtg cicilan pokok per bulan */
double
htgCicilanPokok(double pinjaman, int tenor)
{
	return pinjaman / tenor;
}

/* Fungsi untuk menghtg cicilan bunga per bulan */
double
htgCicilanBunga(double saldoPinjaman, double sukuBunga)
{
	return saldoPinjaman * (sukuBunga / 12);
}

/* Fungsi untuk menghtg total cicilan per bulan */
double
htgTotalCicilan(double cicilanPokok, double cicilanBunga)
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
	double cicilanPokok = htgCicilanPokok(pinjaman, tenor);
	double sisaPinjaman = pinjaman;

	/* Loop untuk menampilkan cicilan setiap bulan */
	for (int bulan = 1; bulan <= tenor; bulan++) {
		double cicilanBunga = htgCicilanBunga(sisaPinjaman, sukuBungaTahunan);
		double totalCicilan = htgTotalCicilan(cicilanPokok, cicilanBunga);

		/* Menampilkan hasil */

		/* Mengurangi sisa pinjaman dengan cicilan pokok yang dibayarkan */
		sisaPinjaman -= cicilanPokok;
	}

	return 0;
}
