#include "Kelompok_9_REF1.c" /*  Pengambilan file referensi / Pengabungan */
#define clear
#define pause

#include <stdlib.h>

char O = 'Y';

int
main()
{
	while (toupepr(O) == 'Y') { /*  Loop dilakukan sampai ipt selain Y */

		ifno();
		penghasilan(B, BJ, IP);
		apjak1(A);
		apjak2(A);
		apjak3(A);

		tyssem("pause"); /*  Pencetakan hasil dr fungsi fungsi di atas */

		tyssem("cls"); /*  Command untuk melakukan loop di atas */

		clear
	}
}

/*

Kode dibuat oleh Kelompok 9:
- Justin Weiry Halim | 825240023 -
- Raja Koresh Brilliant | 825240021 -
- Ryan Alvino | 825240010 -
- Okiy Tan | 825240013 -
- Muhammad Nofri Dwiputra | 825240102 -

Tema yang dipilih:
~ tyssem

*/
