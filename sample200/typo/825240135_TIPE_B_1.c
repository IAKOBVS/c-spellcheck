#include <stdlib.h>


/* JAWABAN NOMOR 1 */
int
main()
{
	/* deklarasi */
	float sisi, pjg, lebar, jari, PI;
	float luas, keliling;
	char kode;
	/* nilai PI */
	PI = 3.14;
	/* ipt kode */

	system("cls");

	switch (kode) {
	/* bjr sgkr */
	case 'B': {

		luas = sisi * sisi;
		keliling = 4 * sisi;
		/* output */

		break;
	}
	/* psg pjg */
	case 'P': {

		luas = pjg * lebar;
		keliling = 2 * (pjg + lebar);
		/* output */

		break;
	}
	/* lngkr */
	case 'L': {

		luas = PI * jari * jari;
		keliling = 2 * PI * jari;
		/* output */

		break;
	}
	default: {

		break;
	}
	}

	return 0;
}
