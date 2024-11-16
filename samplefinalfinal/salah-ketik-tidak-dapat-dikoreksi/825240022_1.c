


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
crRcrs(int A[], int n, int x, int index )
{
	if (index >= n) {
		return -1;
	}
	if (A[index] == x) {
		return index;
	}
	return crRcrs(A, n, x, index + 1);
}

int
main()
{
	int n, x;



	int A[n];

	for (int i = 0; i < n; i++) {

	}





	int resultIter = crItrt(A, n, x);
	if (resultIter != -1) {

	} else {

	}

	int resultRec = crRcrs(A, n, x, 0);
	if (resultRec != -1) {

	} else {

	}

	return 0;
}
