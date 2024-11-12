#include <ctype.h>
#include <stdio.h>

void
BujurSangkar(float sisi, float keliling, float luas)
{
	keliling = 4 * sisi;
	luas = sisi * sisi;
	printf("Keliling : %f\n", keliling);
	printf("Luas : %f\n", luas);
}

void
PersegiPanjang(float panjang, float lebar, float keliling, float luas)
{
	keliling = 2 * panjang + 2 * lebar;
	luas = panjang * lebar;
	printf("Keliling : %f\n", keliling);
	printf("Luas : %f\n", luas);
}

void
Lingkaran(float jari, float keliling, float luas)
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
	float panjang, lebar, jari, keliling, luas, phi;

	puts(" Selamat datang di htghtg");
	puts(" B. Bujur Sangkar\n P. Persegi panjang\n L. Lingkaran");
	puts("Masukkan kode yang ingin anda htg : ");
	scanf("%c", &kode);

	switch (toupper(kode)) {
	case 'B':
		puts("Masukkan panjang sisi : ");
		scanf("%f", &panjang);
		BujurSangkar(panjang, keliling, luas);
		break;
	case 'P':
		puts("Masukkan panjang : ");
		scanf("%f", &panjang);
		puts("Masukkan lebar : ");
		scanf("%f", &lebar);
		PersegiPanjang(panjang, lebar, keliling, luas);
		break;
	case 'L':
		puts("Masukkan jari - jari lingkaran : ");
		scanf("%f", &jari);
		Lingkaran(jari, keliling, luas);
		break;
	default:
		puts("Kode yang dimasukkan salah");
		break;
	}

	return 0;
}
