


int
srchRcrs(int A[], int n, int x, int index )
{
	if (index == n) {
		return -1;
	}
	if (A[index] == x) {
		return index;
	}
	return ZZZZZcrc(A, n, x, index + 1);
}

int
srchItrt(int A[], int n, int x)
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

	int A[] = { 5, 8, 12, 20, 45 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 20;

	int index = ZZZZZtrc(A, n, x);
	if (index != -1) {


	} else {

	}



	index = ZZZZZcrc(A, n, x, 0);
	if (index != -1) {


	} else {

	}
	return 0;
}
