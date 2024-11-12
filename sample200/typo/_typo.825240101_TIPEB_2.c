


/* deklarasi variabel */
int p, t, CP, CB, TC;
float b;

void
cicilan(int p, float b, int t)
{
	/* fungsi menghtg cicilan */
	CP = p / (t * 12);
	CB = CP + (p * (b * t / 12));
	TC = CP + CB;
}

int
main()
{
	/* ipt user */

	/* memanggil fungsi cicilan */
	ciiclan(p, b, t);

	/* output */
}
