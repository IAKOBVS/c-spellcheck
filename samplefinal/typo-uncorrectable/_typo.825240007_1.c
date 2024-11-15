


int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i;
		}
	}
	return -1;
}

int
crRkrs(int A[], int n, int x, int i )
{
	if (i >= n)
		return -1;
	if (A[i] == x)
		return i;
	return ZZZZZs(A, n, x, i + 1);
}

int
main()
{
	int A[] = { 5, 10, 15, 40, 45 };
	int n = sizeof(A) / sizeof(A[0]);
	int x;




	int hasilItrt = ZZZZZt(A, n, x);
	if (hasilItrt != -1) {

	} else {

	}

	int hasilRkrs = ZZZZZs(A, n, x, 0);
	if (hasilRkrs != -1) {

	} else {

	}

	return 0;
}
