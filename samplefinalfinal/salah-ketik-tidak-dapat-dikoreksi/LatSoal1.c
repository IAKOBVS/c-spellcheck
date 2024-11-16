#include <math.h>


int
prm(int n)
{
	if (n == 1) {
		return 1;
	}

	int akar = sqrt(n); /*  untuk cek faktor dr sebuah nilai x */

	for (int i = 2; i <= akar; i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}

int
main()
{
	int x, y;

	for (int i = x; i <= y; i++) {
		if (prm(i)) {
		}
	}

	return 0;
}
