


int
iterSrch(int a[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (a[i] == x) {
			return i;
		}
	}
	return -1;
}

int
recSrch(int a[], int n, int x, int index )
{
	if (index == n) {
		return -1;
	}
	if (a[index] == x) {
		return index;
	}
	return ZZZZZcr(a, n, x, index + 1);
}

int
main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(a) / sizeof(a[0]);
	int x;




	int hasilIter = ZZZZZrch(a, n, x);
	if (hasilIter != -1) {

	} else {

	}

	int hasilRec = ZZZZZcr(a, n, x, 0);
	if (hasilRec != -1) {

	} else {

	}

	return 0;
}
