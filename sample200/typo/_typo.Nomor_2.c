



int faktorial(int x){
	if (x==0 || x==1){
		return 1;
	}
	else{
		return x * faktorial (x-1);
	}
}

int main(){
	int angka;


	
	int result = faktorial(angka);

	return 0;
}
