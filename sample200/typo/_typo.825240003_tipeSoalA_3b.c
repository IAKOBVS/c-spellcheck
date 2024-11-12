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

	/* Menampilkan bilangan yang telah disimpan dalam array */
	puts("\nBilangan terkecil terdapat pada indeks ke- = ");
	puts(" \nBilangan terbesar terdapat pada indeks ke- = ");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
	return 0;
}
