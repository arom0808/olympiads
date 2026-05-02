#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double f1(double x) {
    return x * x;
}

double f2(double x) {
    return x * x * sin(x);
}

double (*fs[2])(double) = {f1, f2};

string fs_names[2] = {"x^2", "x^2*sin(x)"};

double left_rect(double a, double b, int fid) {
    return fs[fid](a) * (b - a);
}

double right_rect(double a, double b, int fid) {
    return fs[fid](b) * (b - a);
}

double mid_rect(double a, double b, int fid) {
    return fs[fid]((a + b) / 2) * (b - a);
}

double trapez(double a, double b, int fid) {
    return (fs[fid](a) + fs[fid](b)) * (b - a) / 2;
}

double simpson(double a, double b, int fid) {
    return (fs[fid](a) + 4 * fs[fid]((a + b) / 2) + fs[fid](b)) * (b - a) / 6;
}

double (*functs[5])(double, double, int) = {left_rect, right_rect, mid_rect, trapez, simpson};

string functs_names[5] = {"left_rect", "right_rect", "mid_rect", "trapezoid", "simpson"};

double get_integral(int fid, double a, double b, int n, int method) {
    double step = (b - a) / n;
    double res = 0;
    for (int i = 0; i < n; ++i) {
        res += functs[method](a + step * i, a + step * (i + 1), fid);
    }
    return res;
}

double left_borders[2] = {-2, -std::numbers::pi / 2};
double right_borders[2] = {2, std::numbers::pi / 2};

int main() {
    cout << fixed << setprecision(15);
    cout << "n ";
    for (int i = 0, n = 1; i < 20; ++i, n *= 2) cout << n << " ";
    cout << "\n";
    for (int fid = 0; fid < 2; ++fid) {
        cout << "function: " << fs_names[fid];
        cout << "\n";
        for (int method = 0; method < 5; ++method) {
            cout << functs_names[method] << ": ";
            for (int i = 0, n = 1; i < 20; ++i, n *= 2) {
                cout << get_integral(fid, left_borders[fid], right_borders[fid], n, method) << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
