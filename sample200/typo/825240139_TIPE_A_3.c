



/* 3a. fungsi untuk menghtg indeks terkecil */
int
indeksTerkecil(int arr[], int size)
{
	/* Indeks dari elemen terkecil */
	int min = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] < arr[min]) {
			min = i;
			/* Update indeks jika ditemukan elemen yang lebih kecil */
		}
	}
	return min;
}

/* 3b. fungsi untuk menghtg indeks terbesar */
int
indeksTerbesar(int arr[], int size)
{
	/* Indeks dari elemen terbesar */
	int max = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] > arr[max]) {
			max = i;
			/* Update indeks jika ditemukan elemen yang lebih besar */
		}
	}
	return max;
}

/* ouput bilangan */
int
main()
{
	int size, array[50];

	for (int i = 0; i < size; i++) {
	}

	int maxIndex = indeksTerbesar(array, size);
	int minIndex = indeksTerkecil(array, size);

	return 0;
}
