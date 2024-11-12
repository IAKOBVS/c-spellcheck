

int
isprm(int n)
{
	int counter = 0;
	for (int i = 1; i <= n; i++) {
		if (n % i == 0) {
			counter++;
		}
	}

	if (counter == 2) {
		return 1;
	} else {
		return 0;
	}
}

int
main()
{
	int x, y;

	for (int i = x; i <= y; i++) {
		if (irpsm(i)) {
		}
	}

	return 0;
}
