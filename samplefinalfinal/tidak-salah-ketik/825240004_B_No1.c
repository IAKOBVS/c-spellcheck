#include <ctype.h>
#include <stdio.h>

float const pi = 3.14;

void
bjrsang(float luas, float keliling, float sisi)
{
	puts("-------------------------");
	puts("      BUJUR SANGKAR      ");
	puts("-------------------------");
	puts("Ipt pjg sisi: ");
	scanf("%f", &sisi);

	luas = sisi * sisi;
	keliling = 4 * sisi;

	printf("\n");
	printf("Hasil KELILING bjr sgkr adalah %f\n", keliling);
	printf("Hasil LUAS bjr sgkr adalah %f\n", luas);
}

void
psgPjg(float pjg, float lebar, float luas, float keliling)
{
	puts("-------------------------");
	puts("     PERSEGI PANJANG     ");
	puts("-------------------------");
	puts("Ipt pjg : ");
	scanf("%f", &pjg);
	puts("Ipt lebar   : ");
	scanf("%f", &lebar);

	luas = pjg * lebar;
	keliling = (2 * pjg) + (2 * lebar);

	printf("\n");
	printf("Hasil KELILING psg pjg adalah %f\n", keliling);
	printf("Hasil LUAS psg pjg adalah %f\n", luas);
}

void
lngkr(float jari, float luas, float keliling)
{
	puts("-------------------------");
	puts("        LINGKARAN        ");
	puts("-------------------------");
	puts("Ipt jari-jari : ");
	scanf("%f", &jari);

	luas = pi * (jari * jari);
	keliling = 2 * pi * jari;

	printf("\n");
	printf("Hasil KELILING lngkr adalah %f\n", keliling);
	printf("Hasil LUAS lngkr adalah %f\n", luas);
}

int
main()
{
	float pjg, lebar, luas, keliling, sisi, jari;
	char ans;

	/* mn UI */
	puts("-----------------------------------------");
	puts("      HITUNG LUAS & KELILING BANGUN      ");
	puts("-----------------------------------------");
	puts("B - Bjr Sgkr");
	puts("P - Psg Pjg");
	puts("L - Lngkr");
	printf("\n");

	/* ipt */
	puts("Masukan bangun ruang yang dipilih = ");
	scanf("%c", &ans);
	printf("\n");

	/* mn picker & output */
	switch (toupper(ans)) {
	case 'B':
		bjrsang(luas, keliling, sisi);
		break;

	case 'P':
		psgPjg(pjg, lebar, luas, keliling);
		break;

	case 'L':
		lngkr(jari, luas, keliling);
		break;

	default:
		puts("Anda salah memasukan kode, mohon ulangi kembali.");
		break;
	}
	return 0;
}
