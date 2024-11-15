


/*  Fungsi untuk mtng tot pajak berdasarkan penghasilan dan trf pajak */
long
htgPajak(long penghasilan, long trfPajak)
{
	return penghasilan * trfPajak / 100; /*  Mtng pajak tanpa desimal */
}

/*  Fungsi untuk menmpl rincian penghasilan dan pajak yang harus dibayar */
void
tmplkanPajak(long penghasilan, long trfPajak)
{
	long pajak = htgPajak(penghasilan, trfPajak);



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



		/*  Menmpl pajak yang harus dibayar */
		tmplkanPajak(penghasilan, trfPajak);

		/*  Menanyakan apakah ingin mtng pajak lagi */



	} while (lanjut == 'y' || lanjut == 'Y');



	return 0;
}
