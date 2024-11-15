#include <ctype.h>
#include <stdio.h>

void
BjrSgkr(float sisi, float keliling, float luas)
{
	keliling = 4 * sisi;
	luas = sisi * sisi;
	printf("Keliling : %f\n", keliling);
	printf("Luas : %f\n", luas);
}

void
PsgPjg(float pjg, float lebar, float keliling, float luas)
{
	keliling = 2 * pjg + 2 * lebar;
	luas = pjg * lebar;
	printf("Keliling : %f\n", keliling);
	printf("Luas : %f\n", luas);
}

void
Lngkr(float jari, float keliling, float luas)
{
	float phi = 3.14;
	keliling = 2 * phi * jari;
	luas = phi * jari * jari;
	printf("Keliling : %f\n", keliling);
	printf("Luas : %f\n", luas);
}

int
main()
{
	char kode;
	float pjg, lebar, jari, keliling, luas, phi;

	puts(" Selamat datang di htghtg");
	puts(" B. Bjr Sgkr\n P. Psg pjg\n L. Lngkr");
	puts("Masukkan kode yang ingin anda htg : ");
	scanf("%c", &kode);

	switch (toupper(kode)) {
	case 'B':
		puts("Masukkan pjg sisi : ");
		scanf("%f", &pjg);
		BjrSgkr(pjg, keliling, luas);
		break;
	case 'P':
		puts("Masukkan pjg : ");
		scanf("%f", &pjg);
		puts("Masukkan lebar : ");
		scanf("%f", &lebar);
		PsgPjg(pjg, lebar, keliling, luas);
		break;
	case 'L':
		puts("Masukkan jari - jari lngkr : ");
		scanf("%f", &jari);
		Lngkr(jari, keliling, luas);
		break;
	default:
		puts("Kode yang dimasukkan salah");
		break;
	}

	return 0;
}
