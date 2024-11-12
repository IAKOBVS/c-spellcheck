




void
htgTotalBiaya(double pokokPinjaman, double sukuBunga, int tenor)
{
	double cicilanPokokPerBulan = pokokPinjaman / tenor;
	double totalBiaya = 0.0;
	double totalBunga = 0.0;

	for (int i = 1; i <= tenor; i++) {
		double bungaPerBulan = (pokokPinjaman * sukuBunga) / 12 / 100;
		double cicilanBulan = cicilanPokokPerBulan + bungaPerBulan;

		totalBiaya += cicilanBulan;
		totalBunga += bungaPerBulan;

		<< bungaPerBulan << "\t\t"
		<< cicilanBulan << "\n";

		if (i % 12 == 0) {
			sukuBunga += 1.0;
		}
	}
}
}
return 0;
}
