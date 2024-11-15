

double clcF(double x, double y) {
    return (x*x - y*y) / (x*x + y*y);
}

int main() {
    double x_values[] = {2.0, 4.0, 6.0, 8.0};
    double y_values[] = {6.0, 9.0, 12.0, 15.0, 18.0, 21.0};



    for (int i = 0; i < sizeof(x_values) / sizeof(x_values[0]); ++i) {
        for (int j = 0; j < sizeof(y_values) / sizeof(y_values[0]); ++j) {
            double x = x_values[i];
            double y = y_values[j];
            double result = cclF(x, y);


        }
    }

    return 0;
}

