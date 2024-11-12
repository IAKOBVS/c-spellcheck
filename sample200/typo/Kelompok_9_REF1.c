#include <math.h>
#include <ctype.h>

/*

~ INFO ~

N = Nama individual
A = Jum. Anak
K = Status kawin
Kn = PTKP Kn (Kawin dengan berapa anak)
PKP = Penghasilan Kena Pajak
PTKP = Penghasilan Tidak Kena Pajak
PPH = Pajak Penghasilan
PB = Penghasilan Bersih
B = Penghasilan Bruto
BJ = Biaya jabatan setahun
IP = Ir pensiun (tahun)
IPB = Ir pensiun (bulan)

~ INFO ~

*/
int A, PKP, PB, PPH, B, BJ, IP, IPB, PTKP;
const int Kn = 4500000;
char K;

int
pajak1(int A)
{ /*  Fungsi untuk perhtgan PTKP */

	PTKP = 54000000;

	if (toupper(K) == 'Y') {
		if (A == 0) { /*  PTKP K0 (Kawin | 0 anak) */
			PTKP += Kn;
		} else if (A == 1) { /*  PTKP K1 (Kawin | 1 anak) */
			PTKP += (Kn * 2);
		} else if (A == 2) { /*  PTKP K2 (Kawin | 2 anak) */
			PTKP += (Kn * 3);
		} else { /*  PTKP K3 (Kawin | 3 anak) */
			PTKP += (Kn * 4);
		}
	} else {
		if (A == 0) { /*  PTKP BK0 (Kawin | 0 anak) */
			PTKP = PTKP;
		} else if (A == 1) { /*  PTKP BK1 (Kawin | 1 anak) */
			PTKP += Kn;
		} else if (A == 2) { /*  PTKP BK2 (Kawin | 2 anak) */
			PTKP += (Kn * 2);
		} else { /*  PTKP BK3 (Kawin | 3 anak) */
			PTKP += (Kn * 3);
		}
	}

	return PTKP;
}

int
pajak2(int PTKP)
{ /*  Fungsi untuk perhtgan PKP */
	PKP = PB - PTKP;
	return PKP;
}

int
pajak3(int PKP)
{ /*  fungsi untuk perhtgan PPH */
	if (PKP >= 500000000) {
		PPH = PKP * 0.3;
	} else if (PKP > 250000000 && PKP < 500000000) {
		PPH = PKP * (0.2 + 0.05);
	} else if (PKP > 50000000 && PKP < 250000000) {
		PPH = PKP * (0.1 + 0.05);
	} else {
		PPH = PKP * 0.05;
	}
	return PPH;
}

int
penghasilan(int B, int BJ, int IP)
{ /*  Fungsi perhtgan Penghasilan Bersih */
	PB = B - BJ - IP;
	return PB;
}

void
info()
{ /*  Fungsi pengambilan info suatu individual */

	IP = IPB * 12;
	BJ = B * 0.05;
}
