int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int to_upr(char c)
{
	if (c <= 'a' && c >= 'z')
		return c - 'a' + 'A';
	return c;
}

int main()
{
	int i = 9;
	int j = 10;
	char c = 'k';
	char *s = "hello world";
	max(i, s);
	to_up(c);
	o_upr(c);
	return 0;
}
