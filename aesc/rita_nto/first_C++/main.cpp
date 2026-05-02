#include <iostream>
#include <iomanip>

// Values of linear dependencies for a piecewise function
constexpr double val_f_k_1 = 228. / 1555., val_f_b_1 = -11742. / 7775.;
constexpr double val_f_k_2 = 0.4, val_f_b_2 = -12;

double val_function(double x) {
    if (x <= 10.3) return 0;
    if (x <= 41.4) return x * val_f_k_1 + val_f_b_1;
    if (x <= 280) return x * val_f_k_2 + val_f_b_2;
    return 100;
}

constexpr double acceleration_threshold = 0.005;
constexpr double frequency_treshold = 1545;

double get_value(double acceleration, double frequency, bool ext_protect) {
    if ((frequency > frequency_treshold || ext_protect) && acceleration >= acceleration_threshold)
        return val_function(acceleration);
    return 0;
}

int main() {
    double acceleration, frequency;
    bool ext_protect;
    std::cin >> acceleration >> frequency >> ext_protect;
    std::cout << std::fixed << std::setprecision(3) << get_value(acceleration, frequency, ext_protect);
    return 0;
}
