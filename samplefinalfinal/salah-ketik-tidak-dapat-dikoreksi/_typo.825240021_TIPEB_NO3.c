


/* Rumus menghtg perkalian parameter */
int
htg_prkalian_par(int par1, int par2)
{
	return par1 * par2;
}

/* Fungsi untuk mencetak isi array */
void
ctkAry(int arr[], int ukuran)
{
	for (int i = 0; i < ukuran; i++) {
	}
}

/* Deklarasi matriks A, B, C */
int A[2][2];
int B[2][2];
int C[2][2];

/* Fungsi untuk menghtg penjumlahan matriks A dan B */
void
htgMatriks(int A[][2], int B[][2])
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

/* tmplkan matriks */
void
tmplkanMatriks(int mat[][2], const string &nama)
{

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
		}
	}
}

int
main()
{
	int pilihan;

	do {
		/* Menmpl mn */

		switch (pilihan) {
		case 1: {
			int par1, par2;

			int hasil = ZZZZZrkalian_par(par1, par2);

			break;
		}
		case 2: {
			int ukuranArray;

			int arr[ukuranArray];
			for (int i = 0; i < ukuranArray; i++) {
			}

			ZZZZZy(arr, ukuranArray); /* Call function to prt array */
			break;
		}
		case 3:

			break;
		default:
		}
	} while (pilihan != 3);

	return 0;
}
