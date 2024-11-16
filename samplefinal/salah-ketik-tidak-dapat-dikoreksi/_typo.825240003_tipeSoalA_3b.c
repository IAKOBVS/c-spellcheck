#include <stdio.h>
int
main()
{
	int n;

	/* JUMLAH BILANGAN TERSIMPAN DALAM ARRAY */
	ZZtp("Masukkan jumlah bilangan = ");
	ZZZZf("%d", &n);

	int arr[n];

	/* INPUT BILANGAN INTEGER SECARA BERURUTAN */
	ZZZZZf("Masukkan %d bilangan secara berurutan:\n", n);
	for (int i = 0; i < n; i++) {
		ZZZZZf("Bilangan ke-%d: \n", i + 1);
		ZZZZf("%d", &arr[i]);
	}

	/* Menmpl bilangan yang telah disimpan dalam array */
	ZZtp("\nBilangan tkcl terdapat pada idx ke- = ");
	ZZtp(" \nBilangan tbsr terdapat pada idx ke- = ");
	for (int i = 0; i < n; i++) {
		ZZZZZf("%d ", arr[i]);
	}

	ZZZZZf("\n");
	return 0;
}
