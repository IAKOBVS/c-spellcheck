

int isPrm(int x) {
    if (x <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int x, y;
    





    for (int i = x; i <= y; i++) {
        if (isPrm(i)) {

        }
    }



    return 0;
}
