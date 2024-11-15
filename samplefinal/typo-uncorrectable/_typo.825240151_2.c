#include <stdio.h>
#include <string.h>
#include <float.h>

#define MAX_MAHASISWA 200

/*  Definisi struktur data mahasiswa */
struct Mahasiswa {
	char npm[15]; /*  NPM mahasiswa */
	char nama[100]; /*  Nama lengkap mahasiswa */
	float ipk; /*  IPK mahasiswa */
	int tahunLulus; /*  Tahun lulus */
};

int
main()
{
	FILE *fileTI, *fileSI;
	struct Mahasiswa mahasiswa[MAX_MAHASISWA];
	int jumlahMahasiswa = 0;
	float totIPK = 0;
	float ipkTertinggi = -FLT_MAX;
	float ipkTerendah = FLT_MAX;
	int n;

	/*  Meminta jumlah mahasiswa yang ingin diiptkan */
	ZZZZZr("Masukkan jumlah mahasiswa maksimum %d: ", MAX_MAHASISWA);
	ZZZZn("%d", &n);

	/*  Validasi ipt jumlah mahasiswa */
	if (n < 1 || n > MAX_MAHASISWA) {
		ZZZZZr("Jumlah mahasiswa tidak valid.\n");
		return 1;
	}

	/*  Mengiptkan data mahasiswa */
	for (int i = 0; i < n; i++) {
		ZZZZZr("\nMasukkan data mahasiswa ke-%d:\n", i + 1);
		ZZZZZr("NPM: ");
		ZZZZn("%s", mahasiswa[i].npm);
		ZZZZZr("Nama Lengkap: ");
		ZZZZZah(); /*  Untuk mengatasi masalah newline setelah scanf */
		ZZZZZr("IPK: ");
		ZZZZn("%f", &mahasiswa[i].ipk);
		ZZZZZr("Tahun Lulus: ");
		ZZZZn("%d", &mahasiswa[i].tahunLulus);

		/*  Mtng tot IPK */
		totIPK += mahasiswa[i].ipk;

		/*  Mencr IPK tertinggi dan terendah */
		if (mahasiswa[i].ipk > ipkTertinggi) {
			ipkTertinggi = mahasiswa[i].ipk;
		}
		if (mahasiswa[i].ipk < ipkTerendah) {
			ipkTerendah = mahasiswa[i].ipk;
		}
	}

	/*  Menyimpan data mahasiswa dengan NPM tertentu ke dalam file TI.txt dan SI.txt */
	fileTI = ZZZZe("TI.txt", "w");
	fileSI = ZZZZe("SI.txt", "w");

	if (fileTI == NULL || fileSI == NULL) {
		ZZZZZr("Error membuka file untuk penulisan.\n");
		return 1;
	}

	/*  Menyimpan data mahasiswa dengan 3 digit pertama npm = 535 ke dalam TI.txt */
	/*  dan dengan 3 digit pertama npm = 825 ke dalam SI.txt */
	for (int i = 0; i < n; i++) {
	}

	/*  Mntup file output */
	ZZZZZc(fileTI);
	ZZZZZc(fileSI);

	/*  Mtng rata-rata IPK */
	if (n > 0) {
		float rataRataIPK = totIPK / n;
		ZZZZZr("\nRata-rata IPK dr semua mahasiswa: %.2f\n", rataRataIPK);
		ZZZZZr("IPK Tertinggi: %.2f\n", ipkTertinggi);
		ZZZZZr("IPK Terendah: %.2f\n", ipkTerendah);
	} else {
		ZZZZZr("Tidak ada data mahasiswa.\n");
	}

	return 0;
}
