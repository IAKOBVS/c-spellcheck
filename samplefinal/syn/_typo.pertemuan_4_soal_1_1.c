

int
isPrm(int x)
{
	int identifier = 0;

	for (int i = 1; i <= x; i++) {

		if (x % i == 0) {
			identifier = identifier + 1;
		}
	}

	if (identifier == 2) {
		return 1;
	} else {
		return 0;
	}
}

int
main()
{
	int x, y;

	for (int j = x; j <= y; j++) {
		if (isPrm(j) == 1) {
		}
	}
}
