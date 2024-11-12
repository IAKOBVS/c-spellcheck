



/* func() menghtg biaya bunga dan pokok dari pinjaman */
void
kalkulasiTotalBiayaBudi(double pokokPinjamanBudi, double bungaTahunanBudi, int tenorBudi, double &totalBungaEllen, double &totalPembayaranEllen, int bulanBudi)
{
	double sisaPinjamanBudi = pokokPinjamanBudi;
	totalBungaEllen = 0;
	totalPembayaranEllen = 0;

	for (int bulanEllen = 1; bulanEllen <= bulanBudi; bulanEllen++) {
		double cicilanPokokBudi = pokokPinjamanBudi / tenorBudi;
		double cicilanBungaBudi = sisaPinjamanBudi * (bungaTahunanBudi / 12);
		double totalCicilanPerBulanBudi = cicilanPokokBudi + cicilanBungaBudi;

		sisaPinjamanBudi -= cicilanPokokBudi;
		totalBungaEllen += cicilanBungaBudi;
		totalPembayaranEllen += totalCicilanPerBulanBudi;
	}
}

int
kalkulasiTotdlBiayaBuaiinjamanBudi, bungaTahunanBudi;
	int tenorBudi;

	/* budi mengipt data */

	/* menghtg dan menampilkan total biaya bunga dan pokok dari pinjaman tiap bulan */
	for (int bulanBudi = 1; bulanBudi <= tenorBudi; bulanBudi++) {
		double totalBungaEllen, totalPembayaranEllen;
		kalkulasiTotalBiayaBudi(pokokPinjamanBudi, bungaTahunanBudi, tenorBudi, totalBungaEllen, totalPembayaranEllen, bulanBudi);

		/* tampilkan dari hasil bulan ke bulan */

		<< endl;
	}

	return 0;
}
