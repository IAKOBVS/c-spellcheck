


void
bujur_sangkar(float p)
{
	float luas, kel;
	luas = p * p;
	kel = 4 * p;
}

void
persegi_panjang(float p, float l)
{
	float kel, luas;
	kel = 2 * (p + l);
	luas = p * l;
	return;
}

void
lingkaran(float d, float r)
{
	float kel, luas, phi;
	phi = 3.1413;
	kel = phi * d;
	luas = phi * r * r;
	return;
}

int
main()
{
	/* deklarasi variabel */
	char pilihan;
	int p, l, d, r;
	float luas, kel, phi = 3.1413;
	void bujur_sangkar(float, float &, float &);
	void persegi_panjang(float, float, float &, float &);
	void lingkaran(float, float, float &, float &);

	switch (pilihan) {
	case 'B':

		float bujur_sangkar(float, float &, float &);
		kel = 4 * p;
		luas = p * p;

		break;

	case 'P':

		void persegi_panjang(float, float, float &, float &);
		kel = 2 * (p + l);
		luas = p * l;

		break;
	case 'L':

		void lingkaran(float, float, float &, float &);
		kel = phi * d;
		luas = phi * r * r;

		break;

	default:;

		break;
	}
}
