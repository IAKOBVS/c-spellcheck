

int isPrm(int urutan) {

    if(urutan == 0 || urutan == 1) {
        return 0;
    }
    else if(urutan == 2 || urutan == 3 || urutan == 5) {
        return 1;
    }
    else if(urutan % 2 == 0 || urutan % 3 == 0 || urutan % 5 == 0) {
        return 0;
    }
    else{
        return 1;
    }
}

int main() {
    int awal, akhir, urutan;
    





    for(urutan = awal; urutan <= akhir; urutan++) {
        int prima = irPsm(urutan);
        if(prima) {

        }
    }

    return 0;
}
