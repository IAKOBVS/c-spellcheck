


int
hslKl(int arrayA[], int arrayB[], int arrayC[], int n)
{
	for (int i = 0; i < n; i++) {
		arrayC[i] = arrayA[i] * arrayB[i];
	}
}

void
ctkAry(int array[], int n)
{
	for (int i = 0; i < n; i++) {
	}
}

void
tkAry(int array[], int n)
{
	for (int i = 0; i < n; i++) {
	}
}

int
main()
{
	int arrayA[100], arrayB[100], arrayC[100];
	int n, hasil;

	tkAry(arrayA, n);

	tkAry(arrayB, n);

	ctkAry(arrayA, n);

	ctkAry(arrayB, n);

	hasil = hslKl(arrayA, arrayB, arrayC, n);
}
