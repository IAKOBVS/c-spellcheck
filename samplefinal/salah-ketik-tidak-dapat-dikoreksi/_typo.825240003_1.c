/*  825240003 - Jennifer lolong */

int
rkrsSrch(int A[], int n, int x, int index)
{
	if (index >= n) { /*  BASE CASE */
		return -1;
	}
	/*  Jika elemen pada idx sekarang sama dengan x, kembalikan index */
	if (A[index] == x) {
		return index;
	}
	/*  Panggil fungsi secara rkrs dengan idx yang ditambah */
	return ZZZZZrcs(A, n, x, index + 1);
}

/*  HASIL */
int
main()
{
	int A[] = { 3, 5, 2, 8, 6 };
	int n = sizeof(A) / sizeof(A[0]);
	int x = 8;
	int hasil = ZZZZZrcs(A, n, x, 0);

	return 0;
}
