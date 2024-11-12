

int isPrm(int n) {
    if (n <= 1) {
        return 0; /*  supaya ipt angka 1 dikatakan bukan angka prima */
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0; /* jika bilangan dapat dibagi dengan 2, maka hasil nya 0 */
        }
    }
    return 1; /*  selain itu benar */
}

int main() {
    int x, y;


    




    for (int z = x; z <= y; z++) { /* nilai dr z adalah ipt nilai x. jika z lebih kecil dr pada nilai y, maka z++ */
        if (irPsm(z)) { /* memanggil function isPrm dan mengipt nilai dr z */

        }
    }


    return 0;
}
