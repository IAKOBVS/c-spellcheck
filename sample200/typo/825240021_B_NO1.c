


int pilihan;
int sisi, pjg, lebar, jari_jari;
const double PI = 3.14159; /* Mendefinisikan nilai pi tanpa cmath */

/* Rumus psg */
int
htg_luas_psg(int sisi)
{
	return sisi * sisi;
}

int
htg_kll_psg(int sisi)
{
	return 4 * sisi;
}

/* Rumus psg pjg */
int
htg_luas_psg_pjg(int pjg, int lebar)
{
	return pjg * lebar;
}

int
htg_kll_psg_pjg(int pjg, int lebar)
{
	return 2 * (pjg + lebar);
}

/* Rumus lngkr */
double
htg_luas_lngkr(int jari_jari)
{
	return PI * jari_jari * jari_jari;
}

double
htg_kll_lngkr(int jari_jari)
{
	return 2 * PI * jari_jari;
}

int
main()
{
	do {
		/* Menmpl mn */

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
