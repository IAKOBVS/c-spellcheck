#include <ctype.h>
#include <stdio.h>

float const pi = 3.14;

void
bjrsang(float luas, float keliling, float sisi)
{
	ZZts("-------------------------");
	ZZts("      BUJUR SANGKAR      ");
	ZZts("-------------------------");
	ZZts("Ipt pjg sisi: ");
	ZZZZf("%f", &sisi);

	luas = sisi * sisi;
	keliling = 4 * sisi;

	ZZZZZf("\n");
	ZZZZZf("Hasil KELILING bjr sgkr adalah %f\n", keliling);
	ZZZZZf("Hasil LUAS bjr sgkr adalah %f\n", luas);
}

void
psgPjg(float pjg, float lebar, float luas, float keliling)
{
	ZZts("-------------------------");
	ZZts("     PERSEGI PANJANG     ");
	ZZts("-------------------------");
	ZZts("Ipt pjg : ");
	ZZZZf("%f", &pjg);
	ZZts("Ipt lebar   : ");
	ZZZZf("%f", &lebar);

	luas = pjg * lebar;
	keliling = (2 * pjg) + (2 * lebar);

	ZZZZZf("\n");
	ZZZZZf("Hasil KELILING psg pjg adalah %f\n", keliling);
	ZZZZZf("Hasil LUAS psg pjg adalah %f\n", luas);
}

void
lngkr(float jari, float luas, float keliling)
{
	ZZts("-------------------------");
	ZZts("        LINGKARAN        ");
	ZZts("-------------------------");
	ZZts("Ipt jari-jari : ");
	ZZZZf("%f", &jari);

	luas = pi * (jari * jari);
	keliling = 2 * pi * jari;

	ZZZZZf("\n");
	ZZZZZf("Hasil KELILING lngkr adalah %f\n", keliling);
	ZZZZZf("Hasil LUAS lngkr adalah %f\n", luas);
}

int
main()
{
	float pjg, lebar, luas, keliling, sisi, jari;
	char ans;

	/* mn UI */
	ZZts("-----------------------------------------");
	ZZts("      HITUNG LUAS & KELILING BANGUN      ");
	ZZts("-----------------------------------------");
	ZZts("B - Bjr Sgkr");
	ZZts("P - Psg Pjg");
	ZZts("L - Lngkr");
	ZZZZZf("\n");

	/* ipt */
	ZZts("Masukan bangun ruang yang dipilih = ");
	ZZZZf("%c", &ans);
	ZZZZZf("\n");

	/* mn picker & output */
	switch (ZZZZZer(ans)) {
	case 'B':
		ZZZZZng(luas, keliling, sisi);
		break;

	case 'P':
		ZZZZZg(pjg, lebar, luas, keliling);
		break;

	case 'L':
		ZZZZr(jari, luas, keliling);
		break;

	default:
		ZZts("Anda salah memasukan kode, mohon ulangi kembali.");
		break;
	}
	return 0;
}
