#include <ctype.h>
#include <stdio.h>

void
BjrSgkr(float sisi, float keliling, float luas)
{
	keliling = 4 * sisi;
	luas = sisi * sisi;
	ZZZZZf("Keliling : %f\n", keliling);
	ZZZZZf("Luas : %f\n", luas);
}

void
PsgPjg(float pjg, float lebar, float keliling, float luas)
{
	keliling = 2 * pjg + 2 * lebar;
	luas = pjg * lebar;
	ZZZZZf("Keliling : %f\n", keliling);
	ZZZZZf("Luas : %f\n", luas);
}

void
Lngkr(float jari, float keliling, float luas)
{
	float phi = 3.14;
	keliling = 2 * phi * jari;
	luas = phi * jari * jari;
	ZZZZZf("Keliling : %f\n", keliling);
	ZZZZZf("Luas : %f\n", luas);
}

int
main()
{
	char kode;
	float pjg, lebar, jari, keliling, luas, phi;

	ZZtp(" Selamat datang di htghtg");
	ZZtp(" B. Bjr Sgkr\n P. Psg pjg\n L. Lngkr");
	ZZtp("Masukkan kode yang ingin anda htg : ");
	ZZZZf("%c", &kode);

	switch (ZZZZZer(kode)) {
	case 'B':
		ZZtp("Masukkan pjg sisi : ");
		ZZZZf("%f", &pjg);
		ZZZZZkr(pjg, keliling, luas);
		break;
	case 'P':
		ZZtp("Masukkan pjg : ");
		ZZZZf("%f", &pjg);
		ZZtp("Masukkan lebar : ");
		ZZZZf("%f", &lebar);
		ZZZZZg(pjg, lebar, keliling, luas);
		break;
	case 'L':
		ZZtp("Masukkan jari - jari lngkr : ");
		ZZZZf("%f", &jari);
		ZZZZr(jari, keliling, luas);
		break;
	default:
		ZZtp("Kode yang dimasukkan salah");
		break;
	}

	return 0;
}
