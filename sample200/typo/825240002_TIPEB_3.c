


int
hasilKali(int arrayA[], int arrayB[], int arrayC[], int n)
{
	for (int i = 0; i < n; i++) {
		arrayC[i] = arrayA[i] * arrayB[i];
	}
}

void
cetakArray(int array[], int n)
{
	for (int i = 0; i < n; i++) {
	}
}

void
iptArray(int array[], int n)
{
	for (int i = 0; i < n; i++) {
	}
}

int
main()
{
	int arrayA[100], arrayB[100], arrayC[100];
	int n, hasil;

	iptArray(arrayA, n);

	iptArray(arrayB, n);

	cetakArray(arrayA, n);

	cetakArray(arrayB, n);

	hasil = hasilKali(arrayA, arrayB, arrayC, n);
}
