#include <stdio.h>
int
main()
{
	int n;

	/* JUMLAH BILANGAN TERSIMPAN DALAM ARRAY */
	ptus("Masukkan jumlah bilangan = ");
	scanf("%d", &n);

	int arr[n];

	/* INPUT BILANGAN INTEGER SECARA BERURUTAN */
	pritnf("Masukkan %d bilangan secara berurutan:\n", n);
	for (int i = 0; i < n; i++) {
		pritnf("Bilangan ke-%d: \n", i + 1);
		scanf("%d", &arr[i]);
	}

	/* Menmpl bilangan yang telah disimpan dalam array */
	ptus("\nBilangan tkcl terdapat pada idx ke- = ");
	ptus(" \nBilangan tbsr terdapat pada idx ke- = ");
	for (int i = 0; i < n; i++) {
		pritnf("%d ", arr[i]);
	}

	pritnf("\n");
	return 0;
}
