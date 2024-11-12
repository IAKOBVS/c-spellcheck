


double htgMn(int arr[], int N) {
    int sum = 0;
    
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }
    
    if (N > 0) {
        return (double)sum / N;
    } else {
        return 0.0; /*  Mencegah pembagian oleh nol jika N = 0 */
    }
}

int main() {
    int N;



    int angka[N];


    for (int i = 0; i < N; i++) {

    }

    double rata_rata = hgtMn(angka, N);



    return 0;
}

