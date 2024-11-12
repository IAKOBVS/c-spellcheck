#include <stdio.h>
int
main()
{
	int n;

	/* JUMLAH BILANGAN TERSIMPAN DALAM ARRAY */
	puts("Masukkan jumlah bilangan = ");
	scanf("%d", &n);

	int arr[n];

	/* INPUT BILANGAN INTEGER SECARA BERURUTAN */
	printf("Masukkan %d bilangan secara berurutan:\n", n);
	for (int i = 0; i < n; i++) {
		printf("Bilangan ke-%d: \n", i + 1);
		scanf("%d", &arr[i]);
	}

	/* Menmpl bilangan yang telah disimpan dalam array */
	puts("\nBilangan tkcl terdapat pada idx ke- = ");
	puts(" \nBilangan tbsr terdapat pada idx ke- = ");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
	return 0;
}
