#include "Kelompok_9_REF1.c" /*  Pengambilan file referensi / Pengabungan */
#define clear
#define pause

#include <stdlib.h>

char O = 'Y';

int
main()
{
	while (toupper(O) == 'Y') { /*  Loop dilakukan sampai ipt selain Y */

		ZZfo();
		penghasilan(B, BJ, IP);
		pajak1(A);
		pajak2(A);
		pajak3(A);

		ZZZtem("pause"); /*  Pencetakan hasil dr fungsi fungsi di atas */

		ZZZtem("cls"); /*  Command untuk melakukan loop di atas */

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
~ Pajak (PKP & PTKP) ~

*/
