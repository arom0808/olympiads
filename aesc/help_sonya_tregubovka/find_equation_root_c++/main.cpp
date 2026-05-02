#include <iomanip>
#include <iostream>

using namespace std;

constexpr double eps = 1e-15;

double f(double x) {
    return x * x - 10;
}

double f_derivative(double x) {
    return x * 2;
}

double dichotomy(double a, double b) {
    while (b - a > eps) {
        double c = (a + b) / 2;
        if (f(c) < 0) a = c;
        else b = c;
    }
    return (a + b) / 2;
}

double secant(double a, double b) {
    while (abs(b - a) > eps) {
        double c = b - f(b) * (b - a) / (f(b) - f(a));
        a = b, b = c;
    }
    return (a + b) / 2;
}

double newton(double a, double b) {
    double x1 = b, x2 = x1 - f(x1) / f_derivative(x1), x3 = x2 - f(x2) / f_derivative(x2);
    while (std::abs((x3 - x2) / (1 - (x3 - x2) / (x2 - x1))) >= eps) {
        x1 = x2, x2 = x3, x3 = x2 - f(x2) / f_derivative(x2);
    }
    return x3;
}

int main() {
    cout << fixed << setprecision(15);
    cout << "dichotomy: " << dichotomy(0, 100) << "\n";
    cout << "secant: " << secant(0, 100) << "\n";
    cout << "newton: " << newton(0, 100) << "\n";
    return 0;
}
