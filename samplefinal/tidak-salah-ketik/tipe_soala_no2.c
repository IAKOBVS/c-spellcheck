float
tot_bunga(float P, float B)
{
	return P * B;
}

float
tot_pokok(float P, float B)
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
	float totBunga;
	float totPokok;
	totBunga = tot_bunga(P, B);
	totPokok = tot_pokok(P, B);
}
