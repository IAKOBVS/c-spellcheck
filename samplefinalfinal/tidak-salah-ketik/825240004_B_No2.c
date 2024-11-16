


void
cicil(int cicil_pokok, int cicil_bunga, int totcicil, int pinjam, int tenor)
{
	cicil_pokok = pinjam / tenor;
	cicil_bunga = cicil_pokok + (pinjam * 0.1 * tenor) / (tenor * 12);
	totcicil = cicil_pokok + cicil_bunga;
}

int
main()
{
	int pinjam, tenor, cicil_pokok, cicil_bunga, totcicil;
	float bunga;

	cicil(cicil_pokok, cicil_bunga, totcicil, pinjam, tenor);
}
