

/* menghtg biaya bunga dan pokok dari pinjaman */
void
kalTotBud(double pokokPinjamanBudi, double bungaTahunanBudi, int tenorBudi, double *totBungaEllen, double *totPembayaranEllen, int bulanBudi)
{
	double sisaPinjamanBudi = pokokPinjamanBudi;
	*totBungaEllen = 0;
	*totPembayaranEllen = 0;

	for (int bulanEllen = 1; bulanEllen <= bulanBudi; bulanEllen++) {
		double cicilanPokokBudi = pokokPinjamanBudi / tenorBudi;
		double cicilanBungaBudi = sisaPinjamanBudi * (bungaTahunanBudi / 12);
		double totCclPerBulanBudi = cicilanPokokBudi + cicilanBungaBudi;

		sisaPinjamanBudi -= cicilanPokokBudi;
		*totBungaEllen += cicilanBungaBudi;
		*totPembayaranEllen += totCclPerBulanBudi;
	}
}

int
main()
{
	double pokokPinjamanBudi, bungaTahunanBudi;
	int tenorBudi;

	/* budi mengipt data */

	/* menghtg dan menmpl tot biaya bunga dan pokok dari pinjaman tiap bulan */
	for (int bulanBudi = 1; bulanBudi <= tenorBudi; bulanBudi++) {
		double totBungaEllen, totPembayaranEllen;
		kalTotBud(pokokPinjamanBudi, bungaTahunanBudi, tenorBudi, &totBungaEllen, &totPembayaranEllen, bulanBudi);

		/* tmplkan dari hasil bulan ke bulan */
	}

	return 0;
}
