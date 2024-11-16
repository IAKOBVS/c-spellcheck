


int
main()
{
	/* Deklarasi variabel */
	char Celcius, Reamur, Kelvin;
	char asal, target;
	float konversi;

	/* Proses perhtgan konversi sesuai jenis yang ditentukan user */
	if (asal == 'Celcius', target == 'Reamur') {
		Reamur = 4 / 5 * Celcius;
	} else if (asal == 'Celcius', target == 'Kelvin') {
		Kelvin = Celcius + 273;
	}

	else if (asal == 'Reamur', target == 'Celcius') {
		Celcius = 5 / 4 * Reamur;
	} else if (asal == 'Reamur', target == 'Kelvin') {
		Kelvin = 5 / 4 * Reamur + 273;
	}

	else if (asal == 'Kelvin', target == 'Celcius') {
		Celcius = Kelvin - 273;
	} else if (asal == 'Kelvin', target == 'Reamur') {
		Reamur = 4 / 5 * Kelvin - 273;
	}

	/* Hasil perhitugan akhir */

	return 0;
}
