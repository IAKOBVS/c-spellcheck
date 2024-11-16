long
min(long x, long y)
{
	if (x < y)
		return x;
	return y;
}

/*  Fungsi untuk ipt gaji bruto */
long
iptGajiBruto()
{
	long gaji;


	return gaji;
}

/*  Fungsi untuk mtng biaya jabatan  */
long
htgBiayaJabatan(long gajiBruto)
{
	long biayaJabatan = gajiBruto * 5 / 100;
	if (biayaJabatan > 6000000) {
		biayaJabatan = 6000000;
	}
	return biayaJabatan;
}

/*  Fungsi untuk ipt iuran pensiun */
long
iptIrPns()
{
	long iuran;


	return iuran;
}

/*  Fungsi untuk mtng Penghasilan Tidak Kena Pajak  */
long
htgPTKP()
{
	int tanggungan;
	long ptkp = 54000000; /*  PTKP dasar untuk wajib pajak orang pribadi  */



	tanggungan = iin(tanggungan, 3); /*  Maksimal 3 tanggungan */
	ptkp += tanggungan * 4500000;

	return ptkp;
}

/*  Fungsi untuk mtng Penghasilan Kena Pajak  */
long
htgPKP(long gajiBersih, long ptkp)
{
	return gajiBersih - ptkp;
}

/*  Fungsi untuk mtng pajak berdasarkan trf */
long
htgPajak(long pkp)
{
	long pajak = 0;

	if (pkp <) {
		pajak = 0; /*  Tidak ada pajak jika PKP <= 0 */
	} else if (pkp <= 50000000) {
		pajak = pkp * 5 / 100; /*  Pajak 5% untuk PKP hingga 50 juta */
	} else if (pkp <= 250000000) {
		pajak = 50000000 * 5 / 100 + (pkp - 50000000) * 15 / 100; /*  Pajak 15% untuk sisa di atas 50 juta */
	} else if (pkp <= 500000000) {
		pajak = 50000000 * 5 / 100 + 200000000 * 15 / 100 + (pkp - 250000000) * 25 / 100; /*  Pajak 25% untuk sisa di atas 250 juta */
	} else if (pkp <= 5000000000) {
		pajak = 50000000 * 5 / 100 + 200000000 * 15 / 100 + 250000000 * 25 / 100 + (pkp - 500000000) * 30 / 100; /*  Pajak 30% untuk sisa di atas 500 juta */
	} else {
		pajak = 50000000 * 5 / 100 + 200000000 * 15 / 100 + 250000000 * 25 / 100 + 4500000000 * 30 / 100 + (pkp - 5000000000) * 35 / 100; /*  Pajak 35% untuk sisa di atas 5 miliar */
	}

	return pajak;
}

/*  Fungsi untuk mtng gaji bersih setelah pajak */
long
htgGajiBersih(long gajiBruto, long pajak)
{
	return gajiBruto - pajak;
}

/*  Fungsi utama untuk menjalankan program perhtgan pajak */
void
mnPajak()
{
	char pilihan;
	do {
		long gajiBruto = iptGajiBruto(); /*  Ipt gaji bruto */
		long biayaJabatan = htgBiayaJabatan(gajiBruto); /*  Htg biaya jabatan */
		long iuranPns = iptIrPns(); /*  Ipt iuran pensiun */
		long gajiBersih = gajiBruto - biayaJabatan - iuranPns; /*  Htg gaji bersih */

		long ptkp = htTPgKP(); /*  Htg PTKP berdasarkan status "Belum Menikah" dan tanggungan */
		long pkp = htgKPP(gajiBersih, ptkp); /*  Htg PKP */
		long pajak = htgPajak(pkp); /*  Htg pajak berdasarkan trf */














	} while (pilihan == 'y' || pilihan == 'Y');
}

int
main()
{
	mnjaPak();
	return 0;
}
