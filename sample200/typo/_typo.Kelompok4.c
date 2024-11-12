

/*
kelompok 4 : Kasir Restoran
825240004
825240020
825240033
825240034
825240135
*/

int n;

int harga_satuan[100];
int kuantitas_barang[100];
int harga_tot[100];
void
harga_barang()
{

	for (int i = 0; i < n; i++) {
	}
}
int tot_harga = 0;
int tot_harga_satuan[100];
int harga_pajak;
void
saat_pajak()
{
	for (int i = 0; i < n; i++) {
		tot_harga_satuan[i] = kuantitas_barang[i] * harga_satuan[i];
		tot_harga += tot_harga_satuan[i];
	}
	harga_pajak = tot_harga * 0.1;
}
int hargafinal;
void
final()
{
	hargafinal = tot_harga + harga_pajak;
}

int
main()
{
	harga_barang();
	saat_pajak();
	final();
}
