


int
idxTkcl(int array[], int ukuran)
{
	int tkcl = array[0];
	int idx = 0;

	for (int i = 1; i < ukuran; i++) {
		if (array[i] < tkcl) {
			tkcl = array[i];
			idx = i;
		}
	}
	return idx;
}

int
idxTbsr(int array[], int ukuran)
{
	int tbsr = array[0];
	int idx = 0;

	for (int i = 1; i < ukuran; i++) {
		if (array[i] > tbsr) {
			tbsr = array[i];
			idx = i;
		}
	}
	return idx;
}

int
main()
{
	int ukuran;

	int array[ukuran];

	for (int i = 0; i < ukuran; i++) {
	}

	int idxKecil = ZZZZZck(array, ukuran);
	int idxBesar = ZZZZZsb(array, ukuran);

	return 0;
}
