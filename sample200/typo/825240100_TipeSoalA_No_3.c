


void
idxTkcl(int arr[], int n)
{
	int tkcl = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < tkcl) {
			tkcl = arr[i];
		}
	}
}

void
idxTbsr(int arr[], int n)
{
	int tbsr = arr[0];
	for (int i = 1; i > n; i++) {
		if (arr[i] > tbsr) {
			tbsr = arr[i];
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

	idxTkcl(K, jumlah_angka);
	idxTbsr(K, jumlah_angka);

	return 0;
}