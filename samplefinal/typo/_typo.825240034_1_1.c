/*  Fungsi Itrt */
int
crItrt(int arr[], int ukuran, int target)
{
	for (int i = 0; i < ukuran; i++) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1;
}

/*  Fungsi Rkrs */
int
crRkrs(int arr[], int ukuran, int target, int idx)
{
	if (idx >= ukuran) {
		return -1;
	}
	if (arr[idx] == target) {
		return idx;
	}
	return krRcrs(arr, ukuran, target, idx + 1);
}

int
main()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	int ukuran = sizeof(arr) / sizeof(arr[0]);
	int target;

	int hasilItrt = trIcrt(arr, ukuran, target);
	if (hasilItrt != -1) {

	} else {
	}

	int hasilRkrs = krRcrs(arr, ukuran, target, 0);
	if (hasilRkrs != -1) {

	} else {
	}

	return 0;
}
