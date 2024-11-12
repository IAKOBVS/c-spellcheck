



/*  Fungsi untuk mtng PTKP berdasarkan status */
double
htgPTKP(char status)
{
	const double PTKP_SINGLE = 54000000; /*  PTKP untuk status "S" */
	const double PTKP_MENIKAH = 58500000; /*  PTKP untuk status "M" */

	if (status == 'S' || status == 's') {
		return PTKP_SINGLE;
	} else if (status == 'M' || status == 'k') {
		return PTKP_MENIKAH;
	} else {

		return 0;
	}
}

/*  Fungsi untuk mtng pajak terutang berdasarkan PKP */
double
htgPajak(double pkp)
{
	const double PAJAK_5 = 0.05; /*  Trf pajak 5% untuk PKP sampai dengan 50 juta */
	const double PAJAK_15 = 0.15; /*  Trf pajak 15% untuk PKP lebih dr 50 juta sampai dengan 250 juta */
	const double PAJAK_25 = 0.25; /*  Trf pajak 25% untuk PKP lebih dr 250 juta sampai dengan 500 juta */
	const double PAJAK_30 = 0.30; /*  Trf pajak 30% untuk PKP lebih dr 500 juta */

	double pajak = 0.0;

	if (pkp <= 50000000) {
		pajak = pkp * PAJAK_5;
	} else if (pkp <= 250000000) {
		pajak = (50000000 * PAJAK_5) + ((pkp - 50000000) * PAJAK_15);
	} else if (pkp <= 500000000) {
		pajak = (50000000 * PAJAK_5) + (200000000 * PAJAK_15) + ((pkp - 250000000) * PAJAK_25);
	} else {
		pajak = (50000000 * PAJAK_5) + (200000000 * PAJAK_15) + (250000000 * PAJAK_25) + ((pkp - 500000000) * PAJAK_30);
	}

	return pajak;
}

int
main()
{
	double penghasilan;
	char status;
	double ptkp, pkp, pajak;

	while (1) {





		/*  Mtng PTKP dan PKP */
		ptkp = htPgTKP(status);
		pkp = penghasilan - ptkp;

		/*  Menmpl hasil */



	}



	return 0;
}
