/* Fungsi Itrt
int crItrt(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (A[i] == x) {
            return i
        }
    }
    return -1
}

Fungsi Rkrs
int crRkrs(int arr[], int ukuran, int target, int index ) {
    if (index >= ukuran) {
        return -1
    }
    if (A[index] == target) {
        return index
    }
    return crRekur(arr, n, x, index + 1)
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x

    Write("Masukkan bilangan yang ingin dicr: ")

    int hasilIte = crIte(arr[], ukuran, target)
    if (hasilIte != -1) {
        Write("Itrt, Bilangan ", target  " ditemukan pada idx pada : " << hasilIte)
    } else {
        Write("Itrt, Bilangan ", target " tidak ditemukan.")
    }

    int hasilRekur = crRekur(arr[], ukuran, target)
    if (hasilRekur != -1) {
        Write("Rkrs, Bilangan ", target " ditemukan pada idx pada : ", hasilRekur)
    } else {
        Write("Rkrs, Bilangan ", target " tidak ditemukan.")
    }
    }
*/

/*  Fungsi Itrt */
int
crItrt(int arr[], int ukuran, int target)
{
	for (int i = 0; i < ukuran; i++) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1;
}

/*  Fungsi Rkrs */
int
crRkrs(int arr[], int ukuran, int target, int idx)
{
	if (idx >= ukuran) {
		return -1;
	}
	if (arr[idx] == target) {
		return idx;
	}
	return crRkrs(arr, ukuran, target, idx + 1);
}

int
main()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	int ukuran = sizeof(arr) / sizeof(arr[0]);
	int target;

	int hasilItrt = crItrt(arr, ukuran, target);
	if (hasilItrt != -1) {

	} else {
	}

	int hasilRkrs = crRkrs(arr, ukuran, target, 0);
	if (hasilRkrs != -1) {

	} else {
	}

	return 0;
}
