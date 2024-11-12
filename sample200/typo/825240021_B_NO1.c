


int pilihan;
int sisi, panjang, lebar, jari_jari;
const double PI = 3.14159; /* Mendefinisikan nilai pi tanpa cmath */

/* Rumus persegi */
int
htg_luas_persegi(int sisi)
{
	return sisi * sisi;
}

int
htg_kll_persegi(int sisi)
{
	return 4 * sisi;
}

/* Rumus persegi panjang */
int
htg_luas_persegi_panjang(int panjang, int lebar)
{
	return panjang * lebar;
}

int
htg_kll_persegi_panjang(int panjang, int lebar)
{
	return 2 * (panjang + lebar);
}

/* Rumus lingkaran */
double
htg_luas_lingkaran(int jari_jari)
{
	return PI * jari_jari * jari_jari;
}

double
htg_kll_lingkaran(int jari_jari)
{
	return 2 * PI * jari_jari;
}

int
main()
{
	do {
		/* Menampilkan menu */

		switch (pilihan) {
		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		case 4:

			break;

		case 5:

			break;

		case 6:

			break;

		case 7:

			break;

		default:
		}

	} while (pilihan != 7);

	return 0;
}
