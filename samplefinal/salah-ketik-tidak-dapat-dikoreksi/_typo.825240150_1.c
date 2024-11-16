



int
crItrt(int arr[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (arr[i] == x) {
			return i; /*  Jika ditemukan, kembalikan idx */
		}
	}
	return -1; /*  Jika tidak ditemukan, kembalikan -1 */
}
int
crRkrs(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == x)
			return mid;

		if (arr[mid] > x)
			return ZZZZZr(arr, l, mid - 1, x);

		return ZZZZZr(arr, mid + 1, r, x);
	}

	return -1;
}
int
main()
{
	int arr[] = { 2, 3, 4, 10, 40 };
	int x = 10;
	int n = sizeof(arr) / sizeof(arr[0]);

	int result = ZZZZZr(arr, n, x);
	if (result == -1)

	else


	result = ZZZZZr(arr, 0, n - 1, x);
	if (result == -1)

	else


	return 0;
}
