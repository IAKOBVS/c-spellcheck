


/* a */
long
totbunga_pokok(long sp, long c_pokok, long bunga, long pinjaman, long tenor)
{
	long c_bunga = (sp - c_pokok) * bunga / 12;
	c_pokok = pinjaman / tenor;
	long tot = bunga + c_pokok;

	return (tot);
}
/* b */
int
main()
{
	long pinjaman, c_pokok, sp;
	long bunga, tenor, tot, c_bunga;

	totbunga_pokok(sp, c_pokok, bunga, pinjaman, tenor);

	c_bunga = (sp - c_pokok) * bunga / 12;
	c_pokok = pinjaman / tenor;
	tot = c_bunga + c_pokok;

	return 0;
}
