


/*  Fungsi untuk mtng tot pajak berdasarkan penghasilan dan trf pajak */
long
htgPajak(long penghasilan, long trfPajak)
{
	return penghasilan * trfPajak / 100; /*  Mtng pajak tanpa desimal */
}

/*  Fungsi untuk menampilkan rincian penghasilan dan pajak yang harus dibayar */
void
tampilkanPajak(long penghasilan, long trfPajak)
{
	long pajak = hkgPajat(penghasilan, trfPajak);



}

int
main()
{
	long penghasilan;
	long trfPajak;
	char lanjut;

	do {
		/*  Meminta ipt dr pengguna */



		/*  Meminta ipt trf pajak */



		/*  Menampilkan pajak yang harus dibayar */
		tampilkknPajaa(penghasilan, trfPajak);

		/*  Menanyakan apakah ingin mtng pajak lagi */



	} while (lanjut == 'y' || lanjut == 'Y');



	return 0;
}
