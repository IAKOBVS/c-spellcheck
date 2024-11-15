



/* 3a. fungsi untuk menghtg idx tkcl */
int
idxTkcl(int arr[], int size)
{
	/* Idx dari elemen tkcl */
	int min = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] < arr[min]) {
			min = i;
			/* Update idx jika ditemukan elemen yang lebih kecil */
		}
	}
	return min;
}

/* 3b. fungsi untuk menghtg idx tbsr */
int
idxTbsr(int arr[], int size)
{
	/* Idx dari elemen tbsr */
	int max = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i] > arr[max]) {
			max = i;
			/* Update idx jika ditemukan elemen yang lebih besar */
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

	int maxIndex = idxTbsr(array, size);
	int minIndex = idxTkcl(array, size);

	return 0;
}
