


void
hasilkali(int submatrix[], int matrixA[], int matrixB[], int row)
{

	for (int i = 0; i < row; i++) {
		submatrix[i] = matrixA[i] * matrixB[i];
	}
}

void
cetakArray(int matrix[], int row)
{
	for (int i = 0; i < row; i++) {
	}
}

int
main()
{
	int row;

	int matrixA[100];
	int matrixB[100];
	int hasilindex[100];

	/* title */

	/* Ipt */

	/* process matrix A */

	for (int i = 0; i < row; i++) {
	}

	/* process matrix B */

	for (int i = 0; i < row; i++) {
	}
	/* fungsi perkalian */

	hasilkali(hasilindex, matrixA, matrixB, row);

	/* tampil hasil semua */

	cetakArray(matrixA, row);

	cetakArray(matrixB, row);

	cetakArray(hasilindex, row);
}
