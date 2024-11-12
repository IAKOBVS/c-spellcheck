int
idxArrayItrt(int arr[], int x, int n)
{
	int y = -1;
	for (int i = 0; i < n; i++) {
		if (x == arr[i]) {
			y = i;
		}
	}
	return y;
}

int
idxArrayRek(int arr[], int x, int n)
{

	if (n < 0) {
		return -1;
	} else if (x == arr[n]) {
		return n;
	} else {
		return idxArrayRek(arr, x, n - 1);
	}
}

int
main()
{
	int n, x;
	int arr[100];




	for (int i = 0; i < n; i++) {


	}




	int idxIt = idxArrayItrt(arr, x, n);
	if (idxIt == -1) {

		return 0;
	}



	int idxRek = idxArrayRek(arr, x, n);
	if (idxRek == -1) {

		return 0;
	}

}
