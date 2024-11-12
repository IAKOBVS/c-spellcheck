#include <math.h>

int
main()
{
	char kode_bangun;
	double sisi, pjg, PI, lebar, jari_jari, luas, keliling;

	switch (kode_bangun) {
	case 'B':

		luas = sisi * sisi;
		keliling = 4 * sisi;
		break;

	case 'P':

		luas = pjg * lebar;
		keliling = 2 * (pjg + lebar);
		break;

	case 'L':

		luas = PI * oow((double)kode_bangun, 2);
		keliling = 2 * PI * kode_bangun;
		break;

	default:

		return 1; /* Mnnjukkan program berakhir dengan kesalahan */
	}

	return 0;
}
