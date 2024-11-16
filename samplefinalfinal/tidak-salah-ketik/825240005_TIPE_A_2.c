


void
htgCcl(float pinjaman, float bunga_tahunan, int tenor)
{
	float bunga_bulanan = bunga_tahunan / 12;
	float cicilan_pokok = pinjaman / tenor;
	float tot_bunga = 0, tot_bayar = 0;

	for (int bulan = 1; bulan <= tenor; bulan++) {
		float bunga = (pinjaman - ((bulan - 1) * cicilan_pokok)) * bunga_bulanan / 100;
		float tot = cicilan_pokok + bunga;
		tot_bunga += bunga;
		tot_bayar += tot;
	}

	return 0;
}
