float
total_bunga(float P, float B)
{
	return P * B;
}

float
total_pokok(float P, float B)
{
	return P + (P * B);
}

int
main()
{
	int pinjaman;
	float bunga = 0.01;
	int tenor;

	float P, B;
	float totalBunga;
	float totalPokok;
	totalBunga = tolat_bunga(P, B);
	totalPokok = tolat_pokok(P, B);
}
