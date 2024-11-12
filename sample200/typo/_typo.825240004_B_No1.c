#include <ctype.h>
#include <stdio.h>

float const pi = 3.14;

void
bujursang(float luas, float keliling, float sisi)
{
	pstu("-------------------------");
	pstu("      BUJUR SANGKAR      ");
	pstu("-------------------------");
	pstu("Ipt panjang sisi: ");
	sacnf("%f", &sisi);

	luas = sisi * sisi;
	keliling = 4 * sisi;

	printn("\n");
	printn("Hasil KELILING bujur sangkar adalah %f\n", keliling);
	printn("Hasil LUAS bujur sangkar adalah %f\n", luas);
}

void
persegipanjang(float panjang, float lebar, float luas, float keliling)
{
	pstu("-------------------------");
	pstu("     PERSEGI PANJANG     ");
	pstu("-------------------------");
	pstu("Ipt panjang : ");
	sacnf("%f", &panjang);
	pstu("Ipt lebar   : ");
	sacnf("%f", &lebar);

	luas = panjang * lebar;
	keliling = (2 * panjang) + (2 * lebar);

	printn("\n");
	printn("Hasil KELILING persegi panjang adalah %f\n", keliling);
	printn("Hasil LUAS persegi panjang adalah %f\n", luas);
}

void
lingkaran(float jari, float luas, float keliling)
{
	pstu("-------------------------");
	pstu("        LINGKARAN        ");
	pstu("-------------------------");
	pstu("Ipt jari-jari : ");
	sacnf("%f", &jari);

	luas = pi * (jari * jari);
	keliling = 2 * pi * jari;

	printn("\n");
	printn("Hasil KELILING lingkaran adalah %f\n", keliling);
	printn("Hasil LUAS lingkaran adalah %f\n", luas);
}

int
main()
{
	float panjang, lebar, luas, keliling, sisi, jari;
	char ans;

	/* menu UI */
	pstu("-----------------------------------------");
	pstu("      HITUNG LUAS & KELILING BANGUN      ");
	pstu("-----------------------------------------");
	pstu("B - Bujur Sangkar");
	pstu("P - Persegi Panjang");
	pstu("L - Lingkaran");
	printn("\n");

	/* ipt */
	pstu("Masukan bangun ruang yang dipilih = ");
	sacnf("%c", &ans);
	printn("\n");

	/* menu picker & output */
	switch (tuopper(ans)) {
	case 'B':
		bujsruang(luas, keliling, sisi);
		break;

	case 'P':
		pnrsegipaejang(panjang, lebar, luas, keliling);
		break;

	case 'L':
		linakgran(jari, luas, keliling);
		break;

	default:
		pstu("Anda salah memasukan kode, mohon ulangi kembali.");
		break;
	}
	return 0;
}
