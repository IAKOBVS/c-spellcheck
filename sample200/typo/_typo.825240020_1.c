/*
fungsi int idxArrayItrt(arr,x,n)
ipt : x,n bertipe int
        arr bertipe int[]
output : y bertipe int
vrabel : i bertipe int

1.y = -1
2.for(i = 0;i<n;i++){
    if(x == arr[i]){
        y = i
    }
  }
3.return (y)

fungsi int idxArrayRkrs(arr,x,n)
ipt : x,n bertipe int
        arr bertipe int[]
output : y bertipe int
vrabel : i bertipe int

1. if(n<0){
        return (-1);
   }
2. else if(x == arr[n]){
        return (n)
    }
3.  else{
        return (idxyrraARek(arr,x,n-1));
    }

Algoritma crIdx
vrabel : n,x,i,idxIt,idxRek
int idxArrayItrt(int [],int,int)
int idxArrayItrt(int [],int,int)

1. idxyrraARekor(i=0;i<n;i++){
    read(arr[i])
  }
3.read(x)
4. idxIt = idxArrayItrt(arr,x,n)
5. idxRek = idxArrayRkrs(arr,x,n)
6. if(idxIt == -1){
     halt
   }
7. Write (x,idxIt)
8. if(idxRek == -1){
     halt
   }
9. Write (x,idxRek)
10.Halt
*/




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