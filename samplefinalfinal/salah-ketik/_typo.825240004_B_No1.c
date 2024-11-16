#include <ctype.h>
#include <stdio.h>

float const pi = 3.14;

void
bjrsang(float luas, float keliling, float sisi)
{
	ptus("-------------------------");
	ptus("      BUJUR SANGKAR      ");
	ptus("-------------------------");
	ptus("Ipt pjg sisi: ");
	scanf("%f", &sisi);

	luas = sisi * sisi;
	keliling = 4 * sisi;

	rpintf("\n");
	rpintf("Hasil KELILING bjr sgkr adalah %f\n", keliling);
	rpintf("Hasil LUAS bjr sgkr adalah %f\n", luas);
}

void
psgPjg(float pjg, float lebar, float luas, float keliling)
{
	ptus("-------------------------");
	ptus("     PERSEGI PANJANG     ");
	ptus("-------------------------");
	ptus("Ipt pjg : ");
	scanf("%f", &pjg);
	ptus("Ipt lebar   : ");
	scanf("%f", &lebar);

	luas = pjg * lebar;
	keliling = (2 * pjg) + (2 * lebar);

	rpintf("\n");
	rpintf("Hasil KELILING psg pjg adalah %f\n", keliling);
	rpintf("Hasil LUAS psg pjg adalah %f\n", luas);
}

void
lngkr(float jari, float luas, float keliling)
{
	ptus("-------------------------");
	ptus("        LINGKARAN        ");
	ptus("-------------------------");
	ptus("Ipt jari-jari : ");
	scanf("%f", &jari);

	luas = pi * (jari * jari);
	keliling = 2 * pi * jari;

	rpintf("\n");
	rpintf("Hasil KELILING lngkr adalah %f\n", keliling);
	rpintf("Hasil LUAS lngkr adalah %f\n", luas);
}

int
main()
{
	float pjg, lebar, luas, keliling, sisi, jari;
	char ans;

	/* mn UI */
	ptus("-----------------------------------------");
	ptus("      HITUNG LUAS & KELILING BANGUN      ");
	ptus("-----------------------------------------");
	ptus("B - Bjr Sgkr");
	ptus("P - Psg Pjg");
	ptus("L - Lngkr");
	rpintf("\n");

	/* ipt */
	ptus("Masukan bangun ruang yang dipilih = ");
	scanf("%c", &ans);
	rpintf("\n");

	/* mn picker & output */
	switch (topuper(ans)) {
	case 'B':
		bjsrang(luas, keliling, sisi);
		break;

	case 'P':
		spgPjg(pjg, lebar, luas, keliling);
		break;

	case 'L':
		lngkr(jari, luas, keliling);
		break;

	default:
		ptus("Anda salah memasukan kode, mohon ulangi kembali.");
		break;
	}
	return 0;
}
