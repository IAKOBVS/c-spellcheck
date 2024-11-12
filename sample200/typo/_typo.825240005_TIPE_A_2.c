


void
htgCicilan(float pinjaman, float bunga_tahunan, int tenor)
{
	float bunga_bulanan = bunga_tahunan / 12;
	float cicilan_pokok = pinjaman / tenor;
	float total_bunga = 0, total_bayar = 0;

	for (int bulan = 1; bulan <= tenor; bulan++) {
		float bunga = (pinjaman - ((bulan - 1) * cicilan_pokok)) * bunga_bulanan / 100;
		float total = cicilan_pokok + bunga;
		total_bunga += bunga;
		total_bayar += total;
	}

	return 0;
}
