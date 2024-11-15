

int
isPrm(int x)
{
	int p = 0;
	if (x == 1)
		return 1;
	for (int i = x; i >= 1; i--) {
		if (x % i == 0 && x % 1 == 0) {
			p++;
		}
	}
	if (p == 2) {
		return 1;
	} else {
		return 0;
	}
}

int
main()
{

	int hasil;
	int x, y;

	for (int i = x; x <= y; x++) {
		if (ZZZZr(x) == 1) {
		}
	}

	return 0;
}
