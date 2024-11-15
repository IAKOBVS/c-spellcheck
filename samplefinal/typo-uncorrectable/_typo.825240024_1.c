


/*  ini fungsi cr secara itrt */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x)
			return i;
	}
	return -1;
}

/*  kalo ini fungsi cr secara rkrs */
int
crRkrs(int A[], int n, int x, int index )
{
	if (index >= n)
		return -1;
	if (A[index] == x)
		return index;
	return ZZZZZs(A, n, x, index + 1);
}

int
main()
{
	int A[] = { 1, 3, 5, 7, 9 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 7;

	/*  cr secara itrt */
	int hasilItrt = ZZZZZt(A, n, x);
	if (hasilItrt != -1)
		;
	else
		;

	/*  cr secara rkrs */
	int hasilRkrs = ZZZZZs(A, n, x, 0);
	if (hasilRkrs != -1)
		;
	else
		;

	return 0;
}
