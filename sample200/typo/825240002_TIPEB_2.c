#include <stdio.h>

void
totalBungaPokok(float pinjaman, float tenor, float bunga, float pokok, float TotalCicilanPerbulan, float sum)
{
	float akhir, cicilanBunga;
	pokok = pinjaman / tenor;
	akhir = pinjaman;
	sum = 0;
	int n = tenor * 12;

	for (int i = 0; i < n; i++) {
		cicilanBunga = pokok + (akhir * (bunga / 100) * tenor) / 12;
		TotalCicilanPerbulan = pokok + cicilanBunga;
		akhir = akhir - pokok;
		for (int j = 13; i >= j; j += 12) {
			bunga = bunga + 1;
		}
		sum = sum + cicilanBunga;
		if (TotalCicilanPerbulan >= 0) {
			printf("Total cicilan untuk bulan ke- %d : %f\n", i + 1, TotalCicilanPerbulan);
		} else {
			puts("Sudah lunas");
			break;
		}
	}
	printf("\nBiaya pokok perbulan : %f\n", pokok);
	printf("Total biaya bunga keseluruhan : %f\n", sum);
}

int
main()
{
	float pinjaman, tenor, bunga, Biaya_pokok_perbulan, Total, Biaya_bunga, sum;

	puts("Masukkan besar pinjaman : ");
	scanf("%f", &pinjaman);
	puts("\nMasukkan tenor : ");
	scanf("%f", &tenor);
	puts("\nMasukkan besar bunga : ");
	scanf("%f", &bunga);

	totalBungaPokok(pinjaman, tenor, bunga, Biaya_pokok_perbulan, Total, sum);
}
