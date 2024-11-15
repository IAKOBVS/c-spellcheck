


void
bjr_sgkr(float p)
{
	float luas, kel;
	luas = p * p;
	kel = 4 * p;
}

void
psg_pjg(float p, float l)
{
	float kel, luas;
	kel = 2 * (p + l);
	luas = p * l;
	return;
}

void
lngkr(float d, float r)
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
	void bjr_sgkr(float, float &, float &);
	void psg_pjg(float, float, float &, float &);
	void lngkr(float, float, float &, float &);

	switch (pilihan) {
	case 'B':

		float bjr_sgkr(float, float &, float &);
		kel = 4 * p;
		luas = p * p;

		break;

	case 'P':

		void psg_pjg(float, float, float &, float &);
		kel = 2 * (p + l);
		luas = p * l;

		break;
	case 'L':

		void lngkr(float, float, float &, float &);
		kel = phi * d;
		luas = phi * r * r;

		break;

	default:;

		break;
	}
}
