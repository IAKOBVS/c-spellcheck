


double
cicilPokok(double tenor, double SP)
{
	double cicilPerbulan = SP / tenor;
	return (cicilPerbulan);
}

double
besarCicil(double SP, double bunga, double tenor)
{
	double besarPerbulan;
	double cicilPokok1 = cicilPokok(tenor, SP);
	for (int i = bunga; i < (tenor * 0.01); i = i + 0.01) {
		for (int j = 1; i <= 12; j++) {
			bunga = i;
			besarPerbulan = cicilPokok1 + (SP * bunga * 12) / 12;
		}
	}
	return (besarPerbulan);
}

int
main()
{
	double SP, bunga, tenor;

	double cicilPokok8 = cicilPokok(tenor, SP);
	double besarCicil8 = besarCicil(SP, bunga, tenor);

	double cicilTotal = cicilPokok8 + besarCicil8;

	return 0;
}
