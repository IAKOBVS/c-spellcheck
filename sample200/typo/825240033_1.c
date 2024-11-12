/*
Fungsi crItrt(A, n, x)
 for(i = 0; i < n-1 ; i++)
  if (A[i] == x)
   return i
        else return -1

Fungsi crRkrs(A, n, x, idx)
 if (idx >= n)
  return -1
 if (A[idx] == x)
  return idx
 return crRkrs(A, n, x, idx + 1)

Algoritma ITERATIF_REKURSIF
 arr A[]
 write ("Masukkan Bilangan yang ingin dicr")
 read (x)
 write ("Pilih metode cr")
 write ("1. Itrt")
 write ("2. Rkrs")
 read (pilihan)
 if (pilihan == 1)
  hasil = crItrt(A, n, x)
 if (pilihan == 2)
  hasil = crRkrs(A, n, x, 0)
 if (hasil != -1)
 write ("Ditemukan di idx:", hasil)
 else
  write ("Tidak ditemukan!")
 Halt
*/

/*  Fungsi Itrt */
int
crItrt(int A[], int n, int x)
{
	for (int i = 0; i < n; ++i) {
		if (A[i] == x) {
			return i;
		}
	}
	return -1;
}

/*  Fungsi Rkrs */
int
crRkrs(int A[], int n, int x, int idx)
{
	if (idx >= n) {
		return -1;
	}
	if (A[idx] == x) {
		return idx;
	}
	return crRkrs(A, n, x, idx + 1);
}

int
main()
{
	int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(A) / sizeof(A[0]);
	int x;

	int pilihan;

	int hasil = -1;
	if (pilihan == 1) {
		hasil = crItrt(A, n, x);
	} else if (pilihan == 2) {
		hasil = crRkrs(A, n, x, 0);
	} else {

		return 1;
	}

	if (hasil != -1) {

	} else {
	}

	return 0;
}
