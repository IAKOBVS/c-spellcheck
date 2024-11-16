#include <stdio.h>

void
totBgPk(float pinjaman, float tenor, float bunga, float pokok, float TotCclPerbulan, float sum)
{
	float akhir, cicilanBunga;
	pokok = pinjaman / tenor;
	akhir = pinjaman;
	sum = 0;
	int n = tenor * 12;

	for (int i = 0; i < n; i++) {
		cicilanBunga = pokok + (akhir * (bunga / 100) * tenor) / 12;
		TotCclPerbulan = pokok + cicilanBunga;
		akhir = akhir - pokok;
		for (int j = 13; i >= j; j += 12) {
			bunga = bunga + 1;
		}
		sum = sum + cicilanBunga;
		if (TotCclPerbulan >= 0) {
			ZZZZZf("Tot cicilan untuk bulan ke- %d : %f\n", i + 1, TotCclPerbulan);
		} else {
			ZZps("Sudah lunas");
			break;
		}
	}
	ZZZZZf("\nBiaya pokok perbulan : %f\n", pokok);
	ZZZZZf("Tot biaya bunga keseluruhan : %f\n", sum);
}

int
main()
{
	float pinjaman, tenor, bunga, Biaya_pokok_perbulan, Tot, Biaya_bunga, sum;

	ZZps("Masukkan besar pinjaman : ");
	ZZZZf("%f", &pinjaman);
	ZZps("\nMasukkan tenor : ");
	ZZZZf("%f", &tenor);
	ZZps("\nMasukkan besar bunga : ");
	ZZZZf("%f", &bunga);

	ZZZZZPt(pinjaman, tenor, bunga, Biaya_pokok_perbulan, Tot, sum);
}
