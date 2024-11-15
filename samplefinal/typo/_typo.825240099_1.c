

int
itrt(int arr[], int x, int size)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == x) {
			return i;
		} else {
			return -1;
		}
	}
}

void
rkrs(int arr[], int x, int size, int *found)
{
	if (arr[0] == x) {
		*found = 1;
		return;
	} else {
		return;
	}
	rrks(arr + 1, x, size - 1, found);
}

int
main()
{
	int x, n, arr[n];
	int size = 10;
	int found = 0;




	for (int i = 0; i < n; i++) {

	}


	irtt(arr, x, size);
	rrks(arr, x, size, &found);
}
