



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
main()
{
	int A[] = { 2, 4, 6, 8, 10, 12, 14, 16 };
	int n = sizeof(A);
	int x;




	int hasil = crItrt(A, n, x);
	if (hasil != -1) {

	} else {

	}

	return 0;
}
