

int
main()
{
	int n;

	if (n % 2 == 0) {

	} else {

		for (int i = 1; i <= n; i += 2) {
			for (int j = 1; j <= ((n - i) / 2); j++) {
			}
			for (int j = 0; j < i; j++) {
			}
		}

		for (int i = n - 2; i >= 1; i -= 2) {
			for (int j = 1; j <= ((n - i) / 2); j++) {
			}
			for (int j = 0; j < i; j++) {
			}
		}
	}
}
