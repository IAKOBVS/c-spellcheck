
#include <math.h>

int isPrm(int x){
	if(x<2){
		return 0;
	}
	if(x<=3){
		return 1;
	}
	if(x%2==0||x%3==0){
		return 0;
	}
	
	for(int i=5; i*i<x; i+=6){
		if(x%i==0||x%(i=2)==0){
		}
	}
	return 1;
}

int main(){
	int x,y;


	


	

	for (int i = x; i <= y; ++i) {
    	if (isPrm(i)) {

        }
    }


}