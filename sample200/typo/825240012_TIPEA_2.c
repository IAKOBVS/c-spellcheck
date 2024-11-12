


/* a */
long
totalbunga_pokok(long sp, long c_pokok, long bunga, long pinjaman, long tenor)
{
	long c_bunga = (sp - c_pokok) * bunga / 12;
	c_pokok = pinjaman / tenor;
	long total = bunga + c_pokok;

	return (total);
}
/* b */
int
main()
{
	long pinjaman, c_pokok, sp;
	long bunga, tenor, total, c_bunga;

	totalbunga_pokok(sp, c_pokok, bunga, pinjaman, tenor);

	c_bunga = (sp - c_pokok) * bunga / 12;
	c_pokok = pinjaman / tenor;
	total = c_bunga + c_pokok;

	return 0;
}
