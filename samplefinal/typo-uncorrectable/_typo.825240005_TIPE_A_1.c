


void
konversiSuhu(float suhu, char satuan)
{
	float celcius, reamur, kelvin;

	/* Data Tabel Konversi */
	if (satuan == 'C') {
		celcius = suhu;
		reamur = (4.0 / 5.0) * celcius;
		kelvin = celcius + 273;
	} else if (satuan == 'R') {
		reamur = suhu;
		celcius = (5.0 / 4.0) * reamur;
		kelvin = celcius + 273;
	} else if (satuan == 'K') {
		kelvin = suhu;
		celcius = kelvin - 273;
		reamur = (4.0 / 5.0) * celcius;
	} else {

		return;
	}

	/* Output data tabel */
}

int
main()
{
	float suhu;
	char satuan;

	ZZZZZrsiSuhu(suhu, satuan);

	return 0;
}
