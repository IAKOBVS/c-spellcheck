


/*  Mencr Itrt */
int
itrt(int A[], int n, int x)
{
	for (int i = 0; i < n; i++)
		if (A[i] == x)
			return i;
	return -1;
}

/*  Mencr Rkrs */
int
rkrs(int A[], int n, int x, int index )
{
	if (index >= n)
		return -1;
	if (A[index] == x)
		return index;
	return rksr(A, n, x, index + 1);
}

int
main()
{
	int A[] = { 5, 3, 8, 2, 9 }, n = sizeof(A) / sizeof(A[0]), x = 8;


	return 0;
}
