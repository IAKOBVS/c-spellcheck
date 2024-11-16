

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

		if (i % 12 == 0) {
			sukuBunga += 1.0;
		}
	}
}

int
main()
{
	return 0;
}
