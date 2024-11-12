


void
indeksTerkecil(int arr[], int n)
{
	int terkecil = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < terkecil) {
			terkecil = arr[i];
		}
	}
}

void
indeksTerbesar(int arr[], int n)
{
	int terbesar = arr[0];
	for (int i = 1; i > n; i++) {
		if (arr[i] > terbesar) {
			terbesar = arr[i];
		}
	}
}

int
main()
{
	int n, jumlah_angka;

	int K[1000];

	for (int j = 0; j < jumlah_angka; j++) {
	}

	indeksTerkecil(K, jumlah_angka);
	indeksTerbesar(K, jumlah_angka);

	return 0;
}