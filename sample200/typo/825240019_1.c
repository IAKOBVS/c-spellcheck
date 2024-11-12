

/* Fungsi Itrt
int crIte(int A[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (A[i] == x) {
            return i
        }
    }
    return -1
}
*/

/*  Fungsi Itrt */
int
crIte(int A[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (A[i] == x) {
			return i;
		}
	}
	return -1;
}

/*  Fungsi Rkrs */
int
crRekur(int A[], int n, int x, int index)
{
	if (index >= n) {
		return -1;
	}
	if (A[index] == x) {
		return index;
	}
	return crRekur(A, n, x, index + 1);
}

int
main()
{
	int A[] = { 1, 2, 3, 4, 5 };
	int n = sizeof(A) / sizeof(A[0]);
	int x;


	int hasilIte = crIte(A, n, x);
	if (hasilIte != -1) {
	} else {
	}

	int hasilRekur = crRekur(A, n, x, 0);
	if (hasilRekur != -1) {
	} else {
	}
}
