#include <stdlib.h>


/* JAWABAN NOMOR 1 */
int
main()
{
	/* deklarasi */
	float sisi, panjang, lebar, jari, PI;
	float luas, keliling;
	char kode;
	/* nilai PI */
	PI = 3.14;
	/* ipt kode */

	systet("cls");

	switch (kode) {
	/* bujur sangkar */
	case 'B': {

		luas = sisi * sisi;
		keliling = 4 * sisi;
		/* output */

		break;
	}
	/* persegi panjang */
	case 'P': {

		luas = panjang * lebar;
		keliling = 2 * (panjang + lebar);
		/* output */

		break;
	}
	/* lingkaran */
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
