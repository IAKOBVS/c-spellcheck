#include <math.h>

int
main()
{
	char kode_bangun;
	double sisi, panjang, PI, lebar, jari_jari, luas, keliling;

	switch (kode_bangun) {
	case 'B':

		luas = sisi * sisi;
		keliling = 4 * sisi;
		break;

	case 'P':

		luas = panjang * lebar;
		keliling = 2 * (panjang + lebar);
		break;

	case 'L':

		luas = PI * pow((double)kode_bangun, 2);
		keliling = 2 * PI * kode_bangun;
		break;

	default:

		return 1; /* Menunjukkan program berakhir dengan kesalahan */
	}

	return 0;
}
