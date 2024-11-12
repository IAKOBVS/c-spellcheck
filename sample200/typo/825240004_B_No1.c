#include <ctype.h>
#include <stdio.h>

float const pi = 3.14;

void
bujursang(float luas, float keliling, float sisi)
{
	puts("-------------------------");
	puts("      BUJUR SANGKAR      ");
	puts("-------------------------");
	puts("Ipt panjang sisi: ");
	scanf("%f", &sisi);

	luas = sisi * sisi;
	keliling = 4 * sisi;

	printf("\n");
	printf("Hasil KELILING bujur sangkar adalah %f\n", keliling);
	printf("Hasil LUAS bujur sangkar adalah %f\n", luas);
}

void
persegipanjang(float panjang, float lebar, float luas, float keliling)
{
	puts("-------------------------");
	puts("     PERSEGI PANJANG     ");
	puts("-------------------------");
	puts("Ipt panjang : ");
	scanf("%f", &panjang);
	puts("Ipt lebar   : ");
	scanf("%f", &lebar);

	luas = panjang * lebar;
	keliling = (2 * panjang) + (2 * lebar);

	printf("\n");
	printf("Hasil KELILING persegi panjang adalah %f\n", keliling);
	printf("Hasil LUAS persegi panjang adalah %f\n", luas);
}

void
lingkaran(float jari, float luas, float keliling)
{
	puts("-------------------------");
	puts("        LINGKARAN        ");
	puts("-------------------------");
	puts("Ipt jari-jari : ");
	scanf("%f", &jari);

	luas = pi * (jari * jari);
	keliling = 2 * pi * jari;

	printf("\n");
	printf("Hasil KELILING lingkaran adalah %f\n", keliling);
	printf("Hasil LUAS lingkaran adalah %f\n", luas);
}

int
main()
{
	float panjang, lebar, luas, keliling, sisi, jari;
	char ans;

	/* menu UI */
	puts("-----------------------------------------");
	puts("      HITUNG LUAS & KELILING BANGUN      ");
	puts("-----------------------------------------");
	puts("B - Bujur Sangkar");
	puts("P - Persegi Panjang");
	puts("L - Lingkaran");
	printf("\n");

	/* ipt */
	puts("Masukan bangun ruang yang dipilih = ");
	scanf("%c", &ans);
	printf("\n");

	/* menu picker & output */
	switch (toupper(ans)) {
	case 'B':
		bujursang(luas, keliling, sisi);
		break;

	case 'P':
		persegipanjang(panjang, lebar, luas, keliling);
		break;

	case 'L':
		lingkaran(jari, luas, keliling);
		break;

	default:
		puts("Anda salah memasukan kode, mohon ulangi kembali.");
		break;
	}
	return 0;
}
