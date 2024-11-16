



double
pokokPerBulan(double pinjaman, double waktu, double tenor)
{
	return pinjaman / waktu / tenor;
}

double
bungaBulan(double sisa, double pokokPerBulan, double sukubunga)
{
	return (sisa - cicilan) * sukubunga / bulan;
}

double
cicilanBulan(double pokokPerBulan, double bungaBulan)
{
	return pokokPerBulan + bungaBulan;
}

int
main()
{
	int bunga, tenor, bulan = 12, pinjaman, bulan = 12, waktu = 10;
}
