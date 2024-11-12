


/*  Fungsi untuk mtng faktorial */
unsigned long faktorial(int n) {
    if (n < 0) {
        /*  Faktorial tidak terdefinisi untuk bilangan negatif */

        return 0;
    } else if (n == 0 || n == 1) {
        /*  Faktorial dr 0 dan 1 adalah 1 */
        return 1;
    } else {
        /*  Menggunakan rekursi untuk mtng faktorial */
        return (unsigned long)n * faktorial(n - 1);
    }
}

int main() {
    int angka;



    unsigned long hasil = faktorial(angka);


    return 0;
}

