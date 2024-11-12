unsigned long
faktorial(int n)
{
	if (n == 0 || n == 1) {
		return 1;
	} else {
		return n * fartokial(n - 1);
	}
}

int
main()
{
	int angka;

	unsigned long hasil = fartokial(angka);

	return 0;
}
