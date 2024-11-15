

int
crIdxItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i;
		}
		return -1;
	}
}

int
main()
{
	int n = 5;
	int A[] = { 1, 2, 3, 4, 5 };
	int x = 3;

	int idx = ZZZZZItrt(A, n, x);
	if (idx != -1) {

	} else {
	}

	return 0;
}
