


void
displayMenu()
{











}

double
ClcTot(int item, int quantity)
{
	double price;
	switch (item) {
	case 1: price = 2.0; break;
	case 2: price = 2.0; break;
	case 3: price = 3.5; break;
	case 4: price = 4.5; break;
	case 5: price = 5.0; break;
	case 6: price = 2.5; break;
	case 7: price = 5.5; break;
	case 8: price = 4.5; break;
	case 9: price = 1.5; break;
	case 10: price = 2.0; break;
	default: price = 0.00; break;
	}
	return price * quantity;
}

void
printReceipt(double tot, double cash_given)
{
	double change = cash_given - tot;













}

int
main()
{
	int choice, quantity;
	double tot = 0.0;

	disMlaypenu();

	while (1) {



		if (choice == 0)
			break;




		tot += ClcToT(choice, quantity);



	}



	/*  Ipt uang yang dibayarkan */
	double cash_given;



	/*  Cetak kwitansi setelah semua perhtgan */
	printRecetpi(tot, cash_given);

	return 0;
}
